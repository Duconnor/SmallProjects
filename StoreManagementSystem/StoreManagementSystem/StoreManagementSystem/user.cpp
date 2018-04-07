#include "user.h"
#include <stdio.h>

bool User::logIn(char * fileName)
{
	bool flag = false;
	FILE *file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("open file error\n");
		return false;
	}
	char stdName[MAXSIZE], stdPassword[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", stdName, MAXSIZE);
		fscanf_s(file, "%s", stdPassword, MAXSIZE);
		if (feof(file))
			return false; // 该用户不存在
		if (strcmp(userName, stdName) == 0)
		{
			// 找到了匹配的用户名
			if (strcmp(password, stdPassword) == 0)
			{
				flag = true;
				break;
			}
			else
				return false; // 密码不匹配
		}
	}
	fclose(file);

	char cartFileName[MAXSIZE];
	strcpy_s(cartFileName, strlen(userName) + 1, userName);
	strcat_s(cartFileName, sizeof(cartFileName), ".txt");
	err = fopen_s(&file, cartFileName, "r");
	if (err != 0)
	{
		printf("open file error\n");
		return false;
	}
	char fileID[MAXIDSIZE];
	char inputName[MAXSIZE];
	char fileBrand[MAXSIZE];
	double filePrice;
	int fileNumber;
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	while (true)
	{
		fscanf_s(file, "%s", fileID, MAXIDSIZE);
		if (feof(file))
			break;
		fscanf_s(file, "%s", inputName, MAXSIZE);
		fscanf_s(file, "%s", fileBrand, MAXSIZE);
		fscanf_s(file, "%lf", &filePrice);
		fscanf_s(file, "%d", &fileNumber);
		Goods *goods = new Goods(fileID, inputName, fileBrand, filePrice, fileNumber);
		shoppingCart.insert(goods);
	}
	fclose(file);
	return flag;
}

void User::logOut()
{
	return;
}

bool User::signIn(char * fileName)
{
	char newUserName[MAXSIZE], newPassword[MAXSIZE];
	scanf_s("%s", newUserName, MAXSIZE);
	scanf_s("%s", newPassword, MAXSIZE);
	strcpy_s(userName, strlen(newUserName) + 1, newUserName);
	strcpy_s(password, strlen(newPassword) + 1, newPassword);
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "a") != 0)
	{
		printf("open file error\n");
		return false;
	}
	fprintf(file, "%s\t", userName);
	fprintf(file, "%s\n", password);
	fclose(file);

	// 为该用户创建购物车文本
	char newFileName[MAXSIZE];
	strcpy_s(newFileName, strlen(userName) + 1, userName);
	strcat_s(newFileName, sizeof(newFileName), ".txt");
	if (errno_t err = fopen_s(&file, newFileName, "w") != 0)
	{
		printf("open file error\n");
		return false;
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量\n");
	fclose(file);
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