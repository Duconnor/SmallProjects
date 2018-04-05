#include "admin.h"
#include <stdio.h>

bool Admin::logIn(char * fileName)
{
	return (strcmp(userName, initialName) == 0) && (strcmp(password, initialPassword) == 0);
}

void Admin::logOut()
{
	return;
}


#define TEST 0
#if TEST == 1

int main()
{
	char name[30], password[30];
	scanf_s("%s", name, 30);
	scanf_s("%s", password, 30);
	Admin admin(name, password);
	if (admin.logIn(nullptr))
		printf("true\n");
	else
		printf("false\n");
	system("pause");
}

#endif