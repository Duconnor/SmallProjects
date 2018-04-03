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
	Goods* searchForGoods(List<Goods> &list); // ��list��������Ʒ
	void addToShoppingCart(Goods &goods); // ���һ��������Ʒ�����ﳵ
	void deleteGoodsInShoppingCart(); // �ڹ��ﳵ��ɾ����Ʒ
	void showShoppingCart(); // չʾ���ﳵ�е���Ʒ
	void pay(); // ֧��
	void logOut();
};

#endif // !SMS_PURCHASE_H
