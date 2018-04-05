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
	Goods* searchForGoods(); // 查询特定的商品（先用商品名，不能确定则可以选择用ID或者进一步利用牌子）
	void addNewGoods();
	void deleteGoods();
	void modifyGoodsInformation();
	void showSoldList();
	void showGoodList();
	void logOut();
};

#endif // !SMS_ADMINISTRATION_H
