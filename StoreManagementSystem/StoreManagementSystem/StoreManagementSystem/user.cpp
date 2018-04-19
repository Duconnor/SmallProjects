#include "user.h"
#include "md5.h"
#include <stdio.h>
#include <string>

bool User::doseExist(char * userName, char *fileName)
{
	FILE * file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		std::cout << "open file error!" << std::endl;
		fclose(file);
		return false;
	}
	char name[MAXSIZE], password[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", name, MAXSIZE);
		fscanf_s(file, "%s", password, MAXSIZE);
		if (feof(file))
		{
			fclose(file);
			return false;
		}
		if (strcmp(name, userName) == 0)
		{
			fclose(file);
			return true;
		}
	}
	return false;
}

bool User::logIn(char * fileName)
{
	bool flag = false;
	FILE *file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("open file error\n");
		fclose(file);
		return false;
	}
	char stdName[MAXSIZE], stdPassword[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", stdName, MAXSIZE);
		fscanf_s(file, "%s", stdPassword, MAXSIZE);
		if (feof(file))
		{
			fclose(file);
			return false; // 该用户不存在
		}
		if (strcmp(userName, stdName) == 0)
		{
			// 找到了匹配的用户名
			MD5 md5(stdPassword);
			string temp = md5.toStr();
			if (strcmp(password, stdPassword) == 0 || strcmp(password, temp.c_str()) == 0)
			{
				flag = true;
				break;
			}
			else
			{
				fclose(file);
				return false; // 密码不匹配
			}
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
		fclose(file);
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
	if (doseExist(userName, fileName))
	{
		std::cout << "用户名被占用！" << std::endl;
		return false;
	}
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "a") != 0)
	{
		printf("open file error\n");
		fclose(file);
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
		fclose(file);
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

bool User::revisePassword(const char * newPassword, char * fileName)
{
	bool flag = false;
	strcpy_s(password, strlen(newPassword) + 1, newPassword);
	FILE *file, *fileTemp;
	errno_t err = fopen_s(&file, fileName, "r");
	errno_t errTemp = fopen_s(&fileTemp, "temp.txt", "w");
	if (err != 0 || errTemp != 0)
	{
		printf("open file error\n");
		fclose(file);
		return false;
	}
	char stdName[MAXSIZE], stdPassword[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", stdName, MAXSIZE);
		fscanf_s(file, "%s", stdPassword, MAXSIZE);
		if (feof(file))
			break;
		fprintf(fileTemp, "%s\t", stdName);
		if (strcmp(userName, stdName) == 0)
		{
			// 找到了匹配的用户名
			fprintf(fileTemp, "%s\n", newPassword);
			flag = true;
		}
		else
			fprintf(fileTemp, "%s\n", stdPassword);
	}
	fclose(fileTemp);
	fclose(file);
	remove(fileName);
	rename("temp.txt", "用户.txt");
	return flag;
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