#pragma once

#ifndef SMS_PURCHASE_H
#define SMS_PURCHASE_H

#include "user.h"

class Purchase
{
private:
	WareHouse wares;
	User& user;
public:
	Purchase(char *fileNameGoods, char *fileNameCart, User& u);
	void showGoodsList();
	Goods* searchForGoods(List<Goods> &list); // 在list中搜索商品
	void addToShoppingCart(Goods &goods); // 添加一个或多个商品进购物车
	void deleteGoodsInShoppingCart(); // 在购物车中删除商品
	void showShoppingCart(); // 展示购物车中的商品
	void pay(); // 支付
	void logOut();
};

#endif // !SMS_PURCHASE_H
