#include "warehouse.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

WareHouse::WareHouse(char * fileName, char *fileName2)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	char fileID[5];
	char inputName[30];
	char fileBrand[30];
	double filePrice;
	int fileNumber;
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	while (true)
	{
		fscanf_s(file, "%s", fileID, 5);
		if (feof(file))
			break;
		fscanf_s(file, "%s", inputName, 30);
		fscanf_s(file, "%s", fileBrand, 30);
		fscanf_s(file, "%lf", &filePrice);
		fscanf_s(file, "%d", &fileNumber);
		Goods *goods = new Goods(fileID, U2G(inputName), U2G(fileBrand), filePrice, fileNumber);
		goodsList.insert(goods);
	}
	fclose(file);
	if (errno_t err = fopen_s(&file, fileName2, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	char fileBuyerName[30];
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	fscanf_s(file, "%s", inputName, 30);
	while (true)
	{
		fscanf_s(file, "%s", fileID, 5);
		if (feof(file))
			break;
		fscanf_s(file, "%s", inputName, 30);
		fscanf_s(file, "%s", fileBrand, 30);
		fscanf_s(file, "%lf", &filePrice);
		fscanf_s(file, "%d", &fileNumber);
		fscanf_s(file, "%s", fileBuyerName, 30);
		SoldGoods *goods = new SoldGoods(U2G(fileID), U2G(inputName), U2G(fileBrand), filePrice, fileNumber, U2G(fileBuyerName));
		soldGoodsList.insert(goods);
	}
	fclose(file);
}

WareHouse::~WareHouse()
{
	for (Goods* goods : goodsList)
		delete goods;
	for (SoldGoods* goods : soldGoodsList)
		delete goods;
}

void WareHouse::writeGoodsList(char * fileName)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "w") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量");
	for (Goods* goods : goodsList)
	{
		fprintf(file, "%s\t", goods->getID());
		fprintf(file, "%s\t", goods->getName());
		fprintf(file, "%s\t", goods->getBrand());
		fprintf(file, "%0.1lf\t", goods->getPrice());
		fprintf(file, "%d", goods->getNumber());
	}
	fclose(file);
}

void WareHouse::writeSoldGoodsList(char * fileName)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "w") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量\t");
	fprintf(file, "用户名");
	for (SoldGoods* goods : soldGoodsList)
	{
		fprintf(file, "%s\t", goods->getID());
		fprintf(file, "%s\t", goods->getName());
		fprintf(file, "%s\t", goods->getBrand());
		fprintf(file, "%0.1lf\t", goods->getPrice());
		fprintf(file, "%d\t", goods->getNumber());
		fprintf(file, "%s", goods->getBuyerName());
	}
	fclose(file);
}

Goods * WareHouse::searchByID(char * ID)
{
	for (Goods* goods : goodsList)
		if (strcmp(goods->getID(), ID) == 0)
			return goods;
	return nullptr;
}

List<Goods*> WareHouse::searchByName(char * name)
{
	List<Goods*> result;
	for (Goods* goods : goodsList)
		if (strcmp(goods->getName(), name) == 0)
			result.insert(goods);
	return result;
}

List<Goods*> WareHouse::searchByBrand(char * brand)
{
	List<Goods*> result;
	for (Goods* goods : goodsList)
		if (strcmp(goods->getBrand(), brand) == 0)
			result.insert(goods);
	return result;
}

void WareHouse::addNewGoods(Goods * newGoods)
{
	goodsList.insert(newGoods);
}

void WareHouse::deleteGoods(Goods * goods)
{
	goods->setNumber(-1);
}

void WareHouse::soldGoods(List<Goods> shoppingCart)
{
	for (Goods goods : shoppingCart)
	{
		Goods *temp = searchByID(goods.getID());
		temp->setNumber(temp->getNumber() - goods.getNumber());
		Goods *del = &goods;
		delete del;
	}
}

void WareHouse::modifyGoodsPrice(Goods * goods, double newPrice)
{
	goods->setPrice((double)((int)newPrice * 10 + 0.5) / 10.0);
}

void WareHouse::modifyGoodsNumber(Goods * goods, int newNumber)
{
	goods->setNumber(newNumber);
}

void WareHouse::getSoldGoodsList()
{
	printf("ID\t\t名称\t\t品牌\t\t价格\t\t数量\n");
	for (SoldGoods* goods : soldGoodsList)
		printf("%s\t\t%s\t\t%s\t\t%0.1lf\t\t%d\n", goods->getID(), goods->getName(), goods->getBrand(), goods->getPrice(), goods->getNumber());
}

void WareHouse::getGoodsList()
{
	printf("ID\t\t名称\t\t品牌\t\t价格\t\t数量\n");
	for (Goods* goods : goodsList)
		printf("%s\t\t%s\t\t%s\t\t%0.1lf\t\t%d\n", goods->getID(), goods->getName(), goods->getBrand(), goods->getPrice(), goods->getNumber());
}


#define TEST 1
#if TEST == 1

int main()
{
	WareHouse warehouse("库存.txt", "已售清单.txt");
	warehouse.getSoldGoodsList();
	warehouse.getGoodsList();
	system("pause");
	return 0;
}

#endif