#pragma once

#ifndef SMS_USER_H
#define SMS_USER_H

#include "baseuser.h"
#include "warehouse.h"

class User :public BaseUser
{
private:
	char userName[MAXSIZE];
	char password[MAXSIZE];
	List<Goods> shoppingCart;
public:
	User(char *inputUserName, char *inputPassword)
	{
		strcpy_s(userName, strlen(inputUserName) + 1, inputUserName);
		strcpy_s(password, strlen(inputPassword) + 1, inputPassword);
	}
	inline char* getUserName() { return userName; }
	bool logIn(char *fileName); // 登录成功的同时从文件中读取购物车信息
	void logOut();
	bool signIn(char *fileName);
};

#endif // !SMS_USER_H
