#pragma once

#ifndef  SMS_BASEUSER_H
#define SMS_BASEUSER_H

class BaseUser
{
	virtual bool logIn(char *fileName) = 0; // ��¼
	virtual void logOut() = 0; // �ǳ�
};

#endif // ! SMS_BASEUSER_H
