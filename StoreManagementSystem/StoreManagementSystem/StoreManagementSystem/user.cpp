#include "user.h"
#include <stdio.h>

bool User::logIn(char * fileName)
{
	FILE *file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("open file error\n");
		return false;
	}
	char stdName[30], stdPassword[30];
	while (true)
	{
		fscanf_s(file, "%s", stdName, 30);
		fscanf_s(file, "%s", stdPassword, 30);
		if (feof(file))
			return false; // 该用户不存在
		if (strcmp(userName, stdName) == 0)
		{
			// 找到了匹配的用户名
			if (strcmp(password, stdPassword) == 0)
				return true;
			else
				return false; // 密码不匹配
		}
	}
	fclose(file);
}

void User::logOut()
{

}

bool User::signIn(char * fileName)
{
	char newUserName[30], newPassword[30];
	scanf_s("%s", newUserName, 30);
	scanf_s("%s", newPassword, 30);
	strcpy_s(userName, strlen(newUserName) + 1, newUserName);
	strcpy_s(password, strlen(newPassword) + 1, newPassword);
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "a") != 0)
	{
		printf("open file error\n");
		return false;
	}
	fprintf(file, "\n");
	fprintf(file, "%s\t", userName);
	fprintf(file, "%s", password);
	return true;
}


#define TEST 0

#if TEST == 1

int main()
{
	char name[30], password[30];
	scanf_s("%s", name, 30);
	scanf_s("%s", password, 30);
	User user(name, password);
	if (user.signIn("用户.txt"))
		printf("true\n");
	else
		printf("false\n");
	system("pause");
	return 0;
}

#endif