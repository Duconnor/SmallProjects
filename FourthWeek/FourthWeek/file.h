#pragma once

#ifndef  FILE_H
#define FILE_H
#endif // ! FILE_H


#include "route.h"

class Route;

// File类用于读取文件


class File
{

public:
	City* readTextFile(char fileName[], int &cityNumber);
	bool writeToBinaryFile(char fileName[], City ** list, int flag, int number); // 将route写入二进制文件中
	bool readBinaryFile(char fileName[], City ** &list, int &number);
};