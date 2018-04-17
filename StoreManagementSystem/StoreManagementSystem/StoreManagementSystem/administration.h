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
	Goods* searchForGoods(); // ��ѯ�ض�����Ʒ��������Ʒ��������ȷ�������ѡ����ID���߽�һ���������ӣ�
	void addNewGoods();
	void deleteGoods();
	void modifyGoodsInformation();
	void showSoldList();
	void showGoodList();
	void logOut();
	void showAllUser(); // �������ܣ�����Ա���Կ�����ע����û���Ϣ
	void setPasswordToDefault(); // �������ܣ�����Ա���԰����û���������
	void undo(); // �������ܣ�����Ա�����Ʒ��ɾ����Ʒ���޸���Ʒ��Ϣ�Ĳ������Գ���
};

#endif // !SMS_ADMINISTRATION_H
