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
	bool vip;
	bool doseExist(char *userName, char *fileName);
public:
	List<Goods*> shoppingCart;
public:
	User(const char *inputUserName,const char *inputPassword)
	{
		strcpy_s(userName, strlen(inputUserName) + 1, inputUserName);
		strcpy_s(password, strlen(inputPassword) + 1, inputPassword);
		vip = false;
	}
	inline char* getUserName() { return userName; }
	bool logIn(char *fileName); // 登录成功的同时从文件中读取购物车信息
	void logOut();
	bool signIn(char *fileName); // 新增功能：注册时检测用户是否已经存在
	bool revisePassword(const char * newPassword, char * fileName); // 新增功能：用户可以修改自己的密码
	void setVIP() { vip = true; }; // 新增功能：VIP用户
	bool isVIP() { return vip; };
};

#endif // !SMS_USER_H
