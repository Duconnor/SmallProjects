#pragma once

#ifndef SMS_PURCHASE_H
#define SMS_PURCHASE_H

#include "user.h"

class Purchase
{
private:
	WareHouse* wares;
	User * user;
public:
	Purchase(char *fileNameGoods,char * fileNameSoldGoods, char *fileNameCart, User * u);
	void showGoodsList();
	Goods* searchForGoods(); // ��list��������Ʒ
	void addToShoppingCart(); // ���һ��������Ʒ�����ﳵ
	void deleteGoodsInShoppingCart(); // �ڹ��ﳵ��ɾ����Ʒ
	void showShoppingCart(); // չʾ���ﳵ�е���Ʒ
	void pay(); // ֧��
	void logOut();
};

#endif // !SMS_PURCHASE_H
