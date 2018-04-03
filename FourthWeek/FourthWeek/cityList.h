#pragma once

#ifndef CITYLIST_H
#define CITYLIST_H
#endif // !CITYLIST_H


#include "STRUCTANDCONST.h"
#include "file.h"

class CityList
{
private:
	City* list;
	int cityNumber;

public:
	CityList()
	{
		list = nullptr;
		cityNumber = -1;
	}
	void initialize(char *fileName); // 初始化，从文件中读入价格表
	void printList();
	void adjustPrice(char *cityName, int newPrice);
	int getPrice(char *cityName);
	City** seekForAddress(City ** list,int number);
	City * seekForAddress(char *cityName);
	City* find(char *cityName);
};