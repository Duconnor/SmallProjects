#include "file.h"
#include <cstdlib>
#include <stdio.h>

City * File::readTextFile(char fileName[], int &cityNumber)
{
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("error opening the file\n");
		exit(-1);
	}
	int index = 0, price = 0, count = 0;
	char *name = new char[MAXSIZE];
	City *list = new City[MAXSIZE];
	while(true)
	{
		fscanf_s(file, "%d", &index);
		if (feof(file))
			break;
		fscanf_s(file, "%s", name, MAXSIZE);
		fscanf_s(file, "%d", &price);
		list[count].setIndex(index);
		list[count].setName(name);
		list[count].setPrice(price);
		count++;
	}
	fclose(file);
	cityNumber = count;
	return list;
}

bool File::writeToBinaryFile(char fileName[], City ** list, int flag, int number)
{
	FILE *file;
	errno_t err = fopen_s(&file, fileName, "wb");
	if (err != 0)
	{
		printf("error opening the file\n");
		return false;
	}
	fwrite(&flag, sizeof(flag), 1, file);
	for (int i = 0; i < number; i++)
		fwrite(list[i], sizeof(City), 1, file);
	fclose(file);
	return true;
}

bool File::readBinaryFile(char fileName[],City ** &list,int &number)
{
	FILE *file;
	errno_t err = fopen_s(&file, fileName, "rb");
	if (err != 0)
	{
		printf("error opening the file\n");
		exit(-1);
	}
	int flag;
	fread(&flag, sizeof(int), 1, file);
	list = new City *[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
		list[i] = new City;
	int count = 0;
	while (true)
	{
		fread(list[count], sizeof(City), 1, file);
		if (feof(file))
			break;
		count++;
	}
	number = count;
	fclose(file);
	return flag;
}


