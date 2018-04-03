#pragma once

#ifndef ROUTE_H
#define ROUTE_H

#endif // !ROUTE_H


#include "cityList.h"

class Route
{
protected:
	class Node
	{
	public:
		City* city;
		Node* next;
		Node(City* c) :city(c), next(nullptr) {}
	}*head;

public:
	Route()
	{
		head = nullptr;
	}
	bool createRoute(City** list, int number); // 利用城市列表初始化路线
	bool printRoute();
	bool replaceCity(char *oldCityName, City *newCity);
	bool removeCity(char *cityName);
	bool insertCity(char *cityPre, char *cityPost, City *newCity);
	City** getRoute(int &number, int &flag);
	void clear(); // 将路线清零
	bool isEmpty(); // 检测是否已经有路线了
};