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
	bool logIn(char *fileName); // ��¼�ɹ���ͬʱ���ļ��ж�ȡ���ﳵ��Ϣ
	void logOut();
	bool signIn(char *fileName); // �������ܣ�ע��ʱ����û��Ƿ��Ѿ�����
	bool revisePassword(const char * newPassword, char * fileName); // �������ܣ��û������޸��Լ�������
	void setVIP() { vip = true; }; // �������ܣ�VIP�û�
	bool isVIP() { return vip; };
};

#endif // !SMS_USER_H
