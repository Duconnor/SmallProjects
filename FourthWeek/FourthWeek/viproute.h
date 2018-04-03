#pragma once

#include "route.h"

class VIPRoute :public Route
{
public:
	bool printRoute();
	City ** getRoute(int &number, int &flag);
};