#pragma once

#ifndef SMS_ADMINISTRATION_H
#define SMS_ADMINISTRATION_H

#include "warehouse.h"

class Administration
{
private:
	WareHouse *wares;
	char * fileNameForGoods;
	char * fileNameForSoldGoods;
public:
	Administration(char *fileName, char *fileName2);
	~Administration();
	Goods* searchForGoods(); // ��ѯ�ض�����Ʒ��������Ʒ��������ȷ�������ѡ����ID���߽�һ���������ӣ�
	void addNewGoods();
	void deleteGoods();
	void modifyGoodsInformation();
	void showSoldList();
	void showGoodList();
	void logOut();
};

#endif // !SMS_ADMINISTRATION_H
