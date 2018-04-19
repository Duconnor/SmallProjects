#include "encrypt.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

#define F(b,c,d) (b&c)|((~c)&d)
#define G(b,c,d) (b&d)|(c&(~d))
#define H(b,c,d) (b^c^d)
#define I(b,c,d) (c^(b|(~d)))
// move将X循环左移n位
#define MOVE(X,n) ((X<<n)|(X>>(32-n)))

void intToBit(unsigned int length, char * output)
{
	// 将4byte的int转为4个1byte的char
	output[0] = length & 0xFF;
	output[1] = (length >> 8) & 0xFF;
	output[2] = (length >> 16) & 0xFF;
	output[3] = (length >> 24) & 0xFF;
}

void initial(char * input,unsigned int length, char * buffer)
{

	MD5Result[0] = { 0x67452301};
	MD5Result[1] = { 0xEFCDAB89};
	MD5Result[2] = {0x98BADCFE};
	MD5Result[3] = { 0x10325476 };
	// input最多为20个字符，即20个字节
	// buffer为缓冲区
	strcpy_s(buffer, strlen(input)+1, input);
	// 填充
	buffer[strlen(input)] = (char)0x128;
	for (int i = strlen(input) + 1; i < 60; i++)
		buffer[i] = 0x0;
	char output[4];
	intToBit(length, output);
	buffer[60] = output[0];
	buffer[61] = output[1];
	buffer[62] = output[2];
	buffer[63] = output[3];
}

void calculateMD5(char * buffer)
{
	unsigned int MD5Temp[4];
	unsigned int unBuffer[16];
	for (int i = 0; i < 4; i++)
	{
		memcpy_s(MD5Temp, 4, MD5Result, 4);
		memcpy_s(unBuffer, 16, &buffer[i * 16], 16);
		for (int j = 0; j <= 15; j++)
		{
			unsigned int ln = 0, k = j;
			unsigned int temp = MD5Temp[0] + F(MD5Temp[1], MD5Temp[2], MD5Temp[3]) + unBuffer[k] + MD5Table[ln][k];
			temp = MOVE(temp, MD5Move[ln][j]);
			MD5Temp[0] = MD5Temp[1] + temp;
			// 循环右移1位
			temp = MD5Temp[3];
			MD5Temp[3] = MD5Temp[2];
			MD5Temp[2] = MD5Temp[1];
			MD5Temp[1] = MD5Temp[0];
			MD5Temp[0] = temp;
		}
		for (int j = 0; j <= 15; j++)
		{
			unsigned int ln = 1, k = (1 + 5 * j) % 16;
			unsigned int temp = MD5Temp[0] + G(MD5Temp[1], MD5Temp[2], MD5Temp[3]) + unBuffer[k] + MD5Table[ln][k];
			temp = MOVE(temp, MD5Move[ln][j]);
			MD5Temp[0] = MD5Temp[1] + temp;
			// 循环右移1位
			temp = MD5Temp[3];
			MD5Temp[3] = MD5Temp[2];
			MD5Temp[2] = MD5Temp[1];
			MD5Temp[1] = MD5Temp[0];
			MD5Temp[0] = temp;
		}
		for (int j = 0; j <= 15; j++)
		{
			unsigned int ln = 2, k = (5 + 3 * j) % 16;
			unsigned int temp = MD5Temp[0] + H(MD5Temp[1], MD5Temp[2], MD5Temp[3]) + unBuffer[k] + MD5Table[ln][k];
			temp = MOVE(temp, MD5Move[ln][j]);
			MD5Temp[0] = MD5Temp[1] + temp;
			// 循环右移1位
			temp = MD5Temp[3];
			MD5Temp[3] = MD5Temp[2];
			MD5Temp[2] = MD5Temp[1];
			MD5Temp[1] = MD5Temp[0];
			MD5Temp[0] = temp;
		}
		for (int j = 0; j <= 15; j++)
		{
			unsigned int ln = 3, k = (7 * j) % 16;
			unsigned int temp = MD5Temp[0] + I(MD5Temp[1], MD5Temp[2], MD5Temp[3]) + unBuffer[k] + MD5Table[ln][k];
			temp = MOVE(temp, MD5Move[ln][j]);
			MD5Temp[0] = MD5Temp[1] + temp;
			// 循环右移1位
			temp = MD5Temp[3];
			MD5Temp[3] = MD5Temp[2];
			MD5Temp[2] = MD5Temp[1];
			MD5Temp[1] = MD5Temp[0];
			MD5Temp[0] = temp;
		}
		MD5Result[0] += MD5Temp[0];
		MD5Result[1] += MD5Temp[1];
		MD5Result[2] += MD5Temp[2];
		MD5Result[3] += MD5Temp[3];
	}
}

void encrypt(char * password)
{
	char buffer[64];
	initial(password, strlen(password), buffer);
	calculateMD5(buffer);
}


int main()
{
	char input[30];
	std::cin >> input;
	encrypt(input);

}