#pragma once

#ifndef SMS_PURCHASE_H
#define SMS_PURCHASE_H

#include "user.h"

class Purchase
{
private:
	WareHouse* wares;
	User * user;
	char * fileNameForGoods;
	char * fileNameForSoldGoods;
	char * fileNameForCart;
public:
	Purchase(char *fileNameGoods,char * fileNameSoldGoods, char *fileNameCart, User * u);
	~Purchase();
	void showGoodsList();
	Goods* searchForGoods(bool flag); // ��list��������Ʒ
	void addToShoppingCart(); // ���һ��������Ʒ�����ﳵ
	void deleteGoodsInShoppingCart(); // �ڹ��ﳵ��ɾ����Ʒ
	void showShoppingCart(); // չʾ���ﳵ�е���Ʒ
	void pay(); // ֧��
	void logOut();
	void revisePassword();
};

#endif // !SMS_PURCHASE_H
