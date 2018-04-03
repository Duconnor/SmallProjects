#pragma once

#ifndef SMS_ADMIN_H
#define SMS_ADMIN_H

#include "baseuser.h"
#include <string.h>

class Admin :public BaseUser
{
private:
	char userName[30];
	char password[30];
	const char initialName[30];
	const char initialPassword[30];
public:
	Admin(char *inputUserName, char *inputPassword) :initialName("adminyep"), initialPassword("oyeadmin")
	{
		strcpy_s(userName, strlen(inputUserName) + 1, inputUserName);
		strcpy_s(password, strlen(inputPassword) + 1, inputPassword);
	}
	bool logIn(char *fileName);
	void logOut();
};

#endif // SMS_ADMIN_H
