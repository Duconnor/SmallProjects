#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// is this char a letter?
bool isLetter(char c)
{
	return (c<'z'&&c>'a');
}

// does this word exist in the given string?
// brutal force
bool doesExist(char thisWord[],char givenString[])
{
	int lengthThis = strlen(thisWord), lengthGiven = strlen(givenString);
	for (int i = 0; i < lengthThis; i++)
		thisWord[i] = tolower(thisWord[i]);
	for (int i = 0; i < lengthGiven; i++)
		givenString[i] = tolower(givenString[i]);
	char *temp = new char[lengthThis + 1];
	for (int i = 0; i < lengthGiven - lengthThis; i++)
	{
		bool flag = true;
		for (int j = 0; j < lengthThis; j++)
			if (thisWord[j] != givenString[j + i])
			{
				flag = false;
				break;
			}
		if (i == 0&&flag)
		{
			if (i + lengthThis == lengthGiven)
				return true;
			else
				if (!isLetter(givenString[i + lengthThis]))
					return true;
		}
		if (i == lengthGiven - lengthThis&&flag)
		{
			if (i == 0)
				return true;
			else
				if (!isLetter(givenString[i - 1]))
					return true;
		}
		if (i != 0 && i != lengthGiven - lengthThis&&flag && 
			!isLetter(givenString[i - 1]) && !isLetter(givenString[i + lengthThis]))
			return true;
	}
	return false;
}

// read from file, one line per time, test if this word is in that text file
bool isThere(char thisWord[],char fileName[])
{
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}
	const int MAXSIZE = 100000;

	char *givenString = new char[MAXSIZE];
	while (!feof(file))
	{
		fgets(givenString, MAXSIZE, file);
		if (doesExist(thisWord, givenString))
			return true;
	}
	return false;

	fclose(file);
}


// main
int main()
{
	const int MAXINPUTSIZE = 100000;
	char *input = new char[MAXINPUTSIZE];
	while (true)
	{
		scanf_s("%s", input, MAXINPUTSIZE);
		if (isThere(input, "sample.txt"))
			printf("true\n");
		else
			printf("false\n");
	}
	system("pause");
	return 0;
}