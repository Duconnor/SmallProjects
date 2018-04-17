#pragma once

#ifndef SMS_ADMINISTRATION_H
#define SMS_ADMINISTRATION_H

#include "warehouse.h"
#include <stack>

class Administration
{
private:
	WareHouse *wares;
	char * fileNameForGoods;
	char * fileNameForSoldGoods;
	char * fileNameForUser;
	std::stack<undoObject*> undoStack;
public:
	Administration(char *fileName, char *fileName2,char *fileName3);
	~Administration();
	Goods* searchForGoods(); // 查询特定的商品（先用商品名，不能确定则可以选择用ID或者进一步利用牌子）
	void addNewGoods();
	void deleteGoods();
	void modifyGoodsInformation();
	void showSoldList();
	void showGoodList();
	void logOut();
	void showAllUser(); // 新增功能：管理员可以看到已注册的用户信息
	void setPasswordToDefault(); // 新增功能：管理员可以帮助用户重置密码
	void undo(); // 新增功能：管理员添加商品、删除商品，修改商品信息的操作可以撤销
};

#endif // !SMS_ADMINISTRATION_H
