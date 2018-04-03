#pragma once
#include <string.h>

#ifndef STRUCTANDCONST_H
#define STRUCTANDCONST_H
#endif // !STRUCTANDCONST_H


#define TEST 0

const int MAXSIZE = 1000;

class City
{
private:
	int index;
	char name[MAXSIZE];
	int price;

public:
	City()
	{
		index = -1;
		price = -1;
	}

	int getIndex()
	{
		return index;
	}

	char* getName()
	{
		return name;
	}

	int getPrice()
	{
		return price;
	}

	void setIndex(int i)
	{
		index = i;
	}

	void setName(char *n)
	{
		strcpy_s(name, strlen(n) + 1, n);
	}

	void setPrice(int p)
	{
		price = p;
	}
};
