#pragma once

#ifndef SMS_PURCHASE_H
#define SMS_PURCHASE_H

#include "user.h"
#include <stack>

class Purchase
{
private:
	WareHouse* wares;
	User * user;
	char * fileNameForGoods;
	char * fileNameForSoldGoods;
	char * fileNameForCart;
	std::stack<undoObject*> undoStack;
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
	void getSumSpent(); // 新增功能：查看历史总花费
};

#endif // !SMS_PURCHASE_H
