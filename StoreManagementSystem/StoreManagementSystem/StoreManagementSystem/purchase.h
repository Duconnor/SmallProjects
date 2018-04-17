#pragma once

#ifndef SMS_PURCHASE_H
#define SMS_PURCHASE_H

#include "user.h"
#include <stack>

enum TYPE { removal, add, numberLess, numberPlus };

class undoObejct : public Goods
{
private:
	TYPE type;
	int index; // 添加或者删除的物品原本的位置
public:
	undoObejct() {};
	undoObejct(Goods * goods)
	{
		this->setID(goods->getID());
		this->setName(goods->getName());
		this->setBrand(goods->getBrand());
		this->setNumber(goods->getNumber());
		this->setPrice(goods->getPrice());
		index = -1;
	}
	int getType() { return type; };
	int getIndex() { return index; };
	void setType(int type) 
	{ 
		switch (type)
		{
		case 0: this->type = removal; break;
		case 1:this->type = add; break;
		case 2:this->type = numberLess; break;
		case 3:this->type = numberPlus; break;
		default:break;
		}
	};
	void setIndex(int index) { this->index = index; };
};

class Purchase
{
private:
	WareHouse* wares;
	User * user;
	char * fileNameForGoods;
	char * fileNameForSoldGoods;
	char * fileNameForCart;
	std::stack<undoObejct*> undoStack;
public:
	Purchase(char *fileNameGoods,char * fileNameSoldGoods, char *fileNameCart, User * u);
	~Purchase();
	void showGoodsList();
	Goods* searchForGoods(bool flag); // 在list中搜索商品
	void addToShoppingCart(); // 添加一个或多个商品进购物车
	void deleteGoodsInShoppingCart(); // 在购物车中删除商品
	void showShoppingCart(); // 展示购物车中的商品
	void pay(); // 支付
	void logOut();
	void revisePassword();
	void undo(); // 新增功能：用户添加商品进购物车、删除购物车中商品可撤销
};

#endif // !SMS_PURCHASE_H
