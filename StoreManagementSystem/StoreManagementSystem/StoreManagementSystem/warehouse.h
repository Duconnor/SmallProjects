#pragma once

#ifndef SMS_WAREHOUSE_H
#define SMS_WAREHOUSE_H

#include "list.h"
#include <string.h>

class Goods
{
private:
	char ID[5];
	char name[30];
	char brand[30];
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
};

class SoldGoods :public Goods
{
private:
	char buyerName[30];
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
	List<Goods*> searchByName(char *name); // ͨ�����Ʋ�ѯ��Ʒ
	List<Goods*> searchByBrand(char *brand); // ͨ��Ʒ�Ʋ�ѯ��Ʒ
	void addNewGoods(Goods * newGoods); // �����µ���Ʒ
	void deleteGoods(Goods * goods); // ɾ����Ʒ
	void soldGoods(List<Goods> shoppingCart); // ֧�����ﳵ�ڵ���Ʒ
	void modifyGoodsPrice(Goods * goods, double newPrice); // �޸�һ����Ʒ�ļ۸�
	void modifyGoodsNumber(Goods * goods, int newNumber); // �޸�һ����Ʒ������
	void getSoldGoodsList(); // ��ȡ�ۻ��嵥
	void getGoodsList(); //��ȡ��Ʒ�嵥
};

#endif // !SMS_WAREHOUSE_H
