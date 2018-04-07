#pragma once

#ifndef SMS_WAREHOUSE_H
#define SMS_WAREHOUSE_H

#include "list.h"
#include <string.h>
#include <iostream>
#include <iomanip>

const int MAXIDSIZE = 10;
const int MAXSIZE = 50;

class Goods
{
private:
	char ID[MAXIDSIZE];
	char name[MAXSIZE];
	char brand[MAXSIZE];
	double price;
	int number; // ��Ʒ������
public:
	Goods() {};
	Goods(char *fileID, char *fileName, char *fileBrand, double filePrice, int fileNumber) :price(filePrice), number(fileNumber)
	{
		strcpy_s(ID, strlen(fileID) + 1, fileID);
		strcpy_s(name, strlen(fileName) + 1, fileName);
		strcpy_s(brand, strlen(fileBrand) + 1, fileBrand);
	}
	Goods(Goods * goods)
	{
		price = goods->getPrice();
		number = goods->getNumber();
		strcpy_s(ID, strlen(goods->getID()) + 1, goods->getID());
		strcpy_s(name, strlen(goods->getName()) + 1, goods->getName());
		strcpy_s(brand, strlen(goods->getBrand()) + 1, goods->getBrand());
	}
	inline char* getID() { return ID; };
	inline char* getName() { return name; };
	inline char* getBrand() { return brand; };
	inline double getPrice() { return price; };
	inline int getNumber() { return number; };
	inline void setID(char *inputID) { strcpy_s(ID, strlen(inputID) + 1, inputID); }
	inline void setName(char *inputName) { strcpy_s(name, strlen(inputName) + 1, inputName); }
	inline void setBrand(char *inputBrand) { strcpy_s(brand, strlen(inputBrand) + 1, inputBrand); }
	inline void setPrice(double inputPrice) { price = inputPrice; }
	inline void setNumber(int n) { number = n; }
	void display()
	{
		std::cout << std::setw(16) << ID << std::setw(16) << name << std::setw(16)<< brand << std::setw(16) 
			<< std::setiosflags(std::ios::fixed) << std::setprecision(1) << price << std::setw(16) << number << std::endl;
	}
	inline bool operator ==(Goods& goods)
	{
		if (strcmp(ID, goods.getID()) == 0)
			return true;
		return false;
	}
};

class SoldGoods :public Goods
{
private:
	char buyerName[MAXSIZE];
public:
	SoldGoods() {};
	SoldGoods(char *fileID, char *fileName, char *fileBrand, double filePrice, int fileNumber, char *buyerName)
		:Goods(fileID, fileName, fileBrand, filePrice, fileNumber)
	{
		strcpy_s(this->buyerName, strlen(buyerName) + 1, buyerName);
	}
	inline char* getBuyerName() { return buyerName; }
	inline void setBuyerName(char *name) { strcpy_s(buyerName, strlen(name) + 1, name); }
};


class WareHouse
{
private:
	List<Goods*> goodsList;
	List<SoldGoods*> soldGoodsList;
public:
	WareHouse(char *fileName,char *fileName2); // �ӿ���嵥�ļ��ж�ȡ�����Ϣ
	~WareHouse();
	void writeGoodsList(char *fileName); // ������嵥��Ϣ��д���ļ�
	void writeSoldGoodsList(char *fileName); // ���ۻ��嵥��Ϣ��д���ļ�
	Goods* searchByID(char *ID); // ͨ��ID�Ų�ѯ��Ʒ
	List<Goods*>* searchByName(char *name); // ͨ�����Ʋ�ѯ��Ʒ
	List<Goods*>* searchByBrand(char *brand); // ͨ��Ʒ�Ʋ�ѯ��Ʒ
	Goods* administrationSearch(Goods &goods); // ��������Ʒ����Ϊ-1Ҳ����ʾ�����Ĺ���Ա�߼�����
	bool doesExist(char *name, char *brand); // �����Ʒ�Ƿ����
	void addNewGoods(Goods * newGoods); // �����µ���Ʒ
	void deleteGoods(Goods * goods); // ɾ����Ʒ
	void soldGoods(List<Goods*> shoppingCart, char * buyerName); // ֧�����ﳵ�ڵ���Ʒ
	void modifyGoodsPrice(Goods * goods, double newPrice); // �޸�һ����Ʒ�ļ۸�
	void modifyGoodsNumber(Goods * goods, int newNumber); // �޸�һ����Ʒ������
	void getSoldGoodsList(); // ��ȡ�ۻ��嵥
	void getGoodsList(); //��ȡ��Ʒ�嵥
};

#endif // !SMS_WAREHOUSE_H
