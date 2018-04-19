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
	Goods* searchForGoods(bool flag); // ��list��������Ʒ
	void addToShoppingCart(); // ���һ��������Ʒ�����ﳵ
	void deleteGoodsInShoppingCart(); // �ڹ��ﳵ��ɾ����Ʒ
	void showShoppingCart(); // չʾ���ﳵ�е���Ʒ
	void pay(); // ֧��
	void logOut();
	void revisePassword();
	void undo(); // �������ܣ��û������Ʒ�����ﳵ��ɾ�����ﳵ����Ʒ�ɳ���
	void getSumSpent(); // �������ܣ��鿴��ʷ�ܻ���
};

#endif // !SMS_PURCHASE_H
