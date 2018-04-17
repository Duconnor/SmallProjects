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
	int index; // ��ӻ���ɾ������Ʒԭ����λ��
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
	Goods* searchForGoods(bool flag); // ��list��������Ʒ
	void addToShoppingCart(); // ���һ��������Ʒ�����ﳵ
	void deleteGoodsInShoppingCart(); // �ڹ��ﳵ��ɾ����Ʒ
	void showShoppingCart(); // չʾ���ﳵ�е���Ʒ
	void pay(); // ֧��
	void logOut();
	void revisePassword();
	void undo(); // �������ܣ��û������Ʒ�����ﳵ��ɾ�����ﳵ����Ʒ�ɳ���
};

#endif // !SMS_PURCHASE_H
