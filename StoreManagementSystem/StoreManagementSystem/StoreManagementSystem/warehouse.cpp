#include "warehouse.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

WareHouse::WareHouse(char * fileName, char *fileName2)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
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
		goodsList.insert(goods);
	}
	fclose(file);
	if (errno_t err = fopen_s(&file, fileName2, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	char fileBuyerName[MAXSIZE];
	fscanf_s(file, "%s", inputName, MAXSIZE);
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
		fscanf_s(file, "%s", fileBuyerName, MAXSIZE);
		SoldGoods *goods = new SoldGoods(fileID, inputName, fileBrand, filePrice, fileNumber, fileBuyerName);
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
	Goods * result = nullptr;
	for (auto goods : goodsList)
		if (strcmp(goods->getID(), ID) == 0)
		{
			result = goods;
			break;
		}
	return result;
}

List<Goods*>* WareHouse::searchByName(char * name)
{
	List<Goods*> *result = new List<Goods*>;
	for (auto goods : goodsList)
		if (strcmp(goods->getName(), name) == 0)
			(*result).insert(goods);
	return result;
}

List<Goods*>* WareHouse::searchByBrand(char * brand)
{
	List<Goods*>* result = new List<Goods*>;
	for (auto goods : goodsList)
		if (strcmp(goods->getBrand(), brand) == 0)
			(*result).insert(goods);
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
	for (auto goods : shoppingCart)
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
	std::cout << std::left << std::setw(16) << "ID" << std::setw(16) << "名称" << std::setw(16) << "品牌" << std::setw(16) << "价格" << std::setw(16) << "数量" << std::endl;
	for (SoldGoods *goods : soldGoodsList)
		std::cout << std::setw(16) << goods->getID() << std::setw(16) << goods->getName() << std::setw(16)
		<< goods->getBrand() << std::setw(16) << std::setprecision(1) << goods->getPrice() << std::setw(16) << goods->getNumber() << std::endl;
}

void WareHouse::getGoodsList()
{
	std::cout << std::left << std::setw(16) << "ID" << std::setw(16) << "名称" << std::setw(16) << "品牌" << std::setw(16) << "价格" << std::setw(16) << "数量" << std::endl;
	for (Goods *goods : goodsList)
		std::cout << std::setw(16) << goods->getID() << std::setw(16) << goods->getName() << std::setw(16)
		<< goods->getBrand() << std::setw(16) << std::setprecision(1) << goods->getPrice() << std::setw(16) << goods->getNumber() << std::endl;
}


#define TEST 0
#if TEST == 1

int main()
{
	WareHouse warehouse("库存.txt", "已售清单.txt");
//	warehouse.getSoldGoodsList();
	warehouse.getGoodsList();
	//Goods * goods = warehouse.searchByID("F0002");
	//std::cout << goods->getName() << std::endl;
	system("pause");
	return 0;
}

#endif