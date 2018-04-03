#include "cityList.h"
#include <iostream>
using namespace std;

void CityList::initialize(char *fileName)
{
	File inputFile;
	list = inputFile.readTextFile(fileName, cityNumber);
}

void CityList::printList()
{
	for (int i = 0; i < cityNumber; i++)
		cout << list[i].getIndex() << "\t" << list[i].getName() << "\t" << list[i].getPrice() << endl;
}

void CityList::adjustPrice(char * cityName, int newPrice)
{
	for (int i = 0; i < cityNumber; i++)
		if (strcmp(list[i].getName(), cityName) == 0)
		{
			list[i].setPrice(newPrice);
			return;
		}
}

int CityList::getPrice(char * cityName)
{
	for (int i = 0; i < cityNumber; i++)
		if (strcmp(list[i].getName(), cityName) == 0)
			return list[i].getPrice();
	return -1;
}

City ** CityList::seekForAddress(City ** inputList, int number)
{
	City ** outputList = new City*[number];
	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < cityNumber; j++)
			if (strcmp(list[j].getName(), inputList[i]->getName()) == 0)
				outputList[i] = &list[j];
	}
	for (int i = 0; i < MAXSIZE; i++)
		delete[] inputList[i];
	delete[] inputList;
	return outputList;
}

City * CityList::seekForAddress(char * cityName)
{
	for (int j = 0; j < cityNumber; j++)
		if (strcmp(list[j].getName(), cityName) == 0)
			return &list[j];
	return nullptr;
}

City * CityList::find(char * cityName)
{
	for (int i = 0; i < cityNumber; i++)
		if (strcmp(list[i].getName(), cityName) == 0)
			return &list[i];
	return nullptr;
}

#if TEST == 1
// µ¥Ôª²âÊÔ
int main()
{
	CityList list;
	list.initialize("pricelist.txt");
	list.printList();
	system("pause");
	return 0;
}
#endif