#pragma once

#ifndef SMS_ADMINISTRATION_H
#define SMS_ADMINISTRATION_H

#include "warehouse.h"

class Administration
{
private:
	WareHouse wares;
public:
	Administration(char *fileName);
	Goods* searchForGoods(List<Goods> &list); // ��ѯ�ض�����Ʒ��������Ʒ��������ȷ�������ѡ����ID���߽�һ���������ӣ�
	void addNewGoods();
	void deleteGoods();
	void modifyGoodsInformation();
	void showSoldList();
};

#endif // !SMS_ADMINISTRATION_H
