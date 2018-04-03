#include <stdio.h>
#include <stdlib.h>

// find the asked position and use the input string to override the string there
void findAndOverride(int offset, char input[], char fileName[])
{
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "r+");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}

	fseek(file, offset-1, SEEK_SET);
	fprintf(file, "%s", input);

	fclose(file);
}

// main
int main()
{
	int offset;
	char input[1000];
	scanf_s("%d", &offset);
	getchar();
	gets_s(input, 1000);
	findAndOverride(offset, input, "sample.txt");
	system("pause");
	return 0;
}