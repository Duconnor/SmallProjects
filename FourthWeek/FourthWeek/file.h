#pragma once

#ifndef  FILE_H
#define FILE_H
#endif // ! FILE_H


#include "route.h"

class Route;

// File�����ڶ�ȡ�ļ�


class File
{

public:
	City* readTextFile(char fileName[], int &cityNumber);
	bool writeToBinaryFile(char fileName[], City ** list, int flag, int number); // ��routeд��������ļ���
	bool readBinaryFile(char fileName[], City ** &list, int &number);
};