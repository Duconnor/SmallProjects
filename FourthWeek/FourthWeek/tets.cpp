#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class City
{
private:
	int index;
	char *name;
	int price;

public:
	City()
	{
		index = -1;
		name = new char[1000];
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

int main()
{
	FILE *file;
	errno_t err = fopen_s(&file, "route.txt", "rb");
	if (err != 0)
		exit(-1);
	int flag = -1;
	fread(&flag, sizeof(flag), 1, file);
	printf("%d\n", flag);
	City city;
	fread(&city, sizeof(City), 1, file);
	printf("%s", city.getName());
	fclose(file);
	system("pause");
	return 0;
}