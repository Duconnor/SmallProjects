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
	int number; // 商品的数量
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
	WareHouse(char *fileName,char *fileName2); // 从库存清单文件中读取库存信息
	~WareHouse();
	void writeGoodsList(char *fileName); // 将库存清单信息回写回文件
	void writeSoldGoodsList(char *fileName); // 将售货清单信息回写回文件
	Goods* searchByID(char *ID); // 通过ID号查询商品
	List<Goods*>* searchByName(char *name); // 通过名称查询商品
	List<Goods*>* searchByBrand(char *brand); // 通过品牌查询商品
	Goods* administrationSearch(Goods &goods); // 就算是商品数量为-1也会显示出来的管理员高级搜索
	bool doesExist(char *name, char *brand); // 检查商品是否存在
	void addNewGoods(Goods * newGoods); // 增加新的商品
	void deleteGoods(Goods * goods); // 删除商品
	void soldGoods(List<Goods*> shoppingCart, char * buyerName); // 支付购物车内的商品
	void modifyGoodsPrice(Goods * goods, double newPrice); // 修改一种商品的价格
	void modifyGoodsNumber(Goods * goods, int newNumber); // 修改一种商品的数量
	void getSoldGoodsList(); // 获取售货清单
	void getGoodsList(); //获取商品清单
};

#endif // !SMS_WAREHOUSE_H
