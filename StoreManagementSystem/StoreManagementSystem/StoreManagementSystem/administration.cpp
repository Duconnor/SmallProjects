#include "administration.h"

Administration::Administration(char * fileName, char *fileName2,char *fileName3)
{
	wares = new WareHouse(fileName, fileName2);
	fileNameForGoods = new char[MAXSIZE];
	fileNameForSoldGoods = new char[MAXSIZE];
	fileNameForUser = new char[MAXSIZE];
	strcpy_s(fileNameForGoods, strlen(fileName) + 1, fileName);
	strcpy_s(fileNameForSoldGoods, strlen(fileName2) + 1, fileName2);
	strcpy_s(fileNameForUser, strlen(fileName3) + 1, fileName3);
}

Administration::~Administration()
{
	delete fileNameForGoods;
	delete fileNameForSoldGoods;
	delete wares;
}

Goods * Administration::searchForGoods()
{
	// ��ѯ�ض�����Ʒ��������Ʒ��������ȷ�������ѡ����ID���߽�һ���������ӣ�
	std::cout << "��������Ʒ��" << std::endl;
	char name[MAXSIZE];
	std::cin >> name;
	List<Goods*> *searchList = wares->searchByName(name);
	if ((*searchList).size() == 0)
	{
		std::cout << "û���ҵ���Ӧ��Ʒ" << std::endl;
		return nullptr;
	}
	else if ((*searchList).size() == 1)
	{
		std::cout << "�ɹ���" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			goods->display();
		std::cout << delim << std::endl;
		return (searchList->get(0));
	}
	else
	{
		std::cout << "�г���һ�ֵ���Ʒ���ϲ�ѯ������������ʾ" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			goods->display();
		std::cout << delim << std::endl;
		std::cout << "������ID���н�һ���Ĳ�ѯ" << std::endl;
		std::cin >> name;
		Goods * searchGoods = wares->searchByID(name);
		if (searchGoods == nullptr)
		{
			std::cout << "û���ҵ���Ӧ��Ʒ" << std::endl;
			return nullptr;
		}
		else
		{
			std::cout << "�ɹ���" << std::endl;
			std::cout << delim << std::endl;
			searchGoods->display();
			std::cout << delim << std::endl;
			return searchGoods;
		}
	}
}

void Administration::addNewGoods()
{
	std::cout << "���������²�Ʒ�����ƺ�Ʒ�ƣ�ϵͳ����м�飬���Կո�ָ����س�����" << std::endl;
	char * inputBuffer = new char[1000];
	std::cin.clear();
	std::cin.ignore(1024, '\n');
	std::cin.getline(inputBuffer, 1000);
	char *s = nullptr, *next = nullptr;
	s = strtok_s(inputBuffer, " ", &next);
	char name[MAXSIZE], brand[MAXSIZE];
	strcpy_s(name, strlen(s) + 1, s);
	s = strtok_s(nullptr, " ", &next);
	strcpy_s(brand, strlen(s) + 1, s);
	std::cout << "��������......" << std::endl;
	if (wares->doesExist(name, brand))
	{
		std::cout << "���ʧ�ܣ�����Ʒ�Ѵ���" << std::endl;
		return;
	}
	std::cout << "�����ϣ�����Ʒ֮ǰ�����ڣ��������" << std::endl;
	std::cout << "�������²�Ʒ�ļ۸���������Կո�ָ����س�����" << std::endl;
	double price;
	int number;
	std::cin >> price >> number;
	price = (double)((int)((price * 10) + 0.5)) / 10.0;
	Goods * newGoods = new Goods("", name, brand, price, number);
	wares->addNewGoods(newGoods);
	std::cout << "��ӳɹ�" << std::endl;
}

void Administration::deleteGoods()
{
	Goods * deleteGoods = searchForGoods();
	wares->deleteGoods(deleteGoods);
	std::cout << "ɾ���ɹ�" << std::endl;
}

void Administration::modifyGoodsInformation()
{
	Goods * goods = searchForGoods();
	std::cout << "��������Ҫ�޸ĵ���Ϣ���ͣ�1�����޸ļ۸�2�����޸�����" << std::endl;
	int order = 0;
	std::cin >> order;
	if (order == 1)
	{
		std::cout << "�������޸ĺ�ļ۸�" << std::endl;
		double price = 0.0;
		std::cin >> price;
		wares->modifyGoodsPrice(goods, price);
		std::cout << "�޸ĳɹ���" << std::endl;
	}
	else
	{
		std::cout << "�������޸ĺ������" << std::endl;
		int number = 0;
		std::cin >> number;
		if (number < 0)
		{
			std::cout << "�޸�ʧ�ܣ���������Ϊ��" << std::endl;
			return;
		}
		wares->modifyGoodsNumber(goods, number);
		std::cout << "�޸ĳɹ���" << std::endl;
	}
}

void Administration::showSoldList()
{
	wares->getSoldGoodsList();
}

void Administration::showGoodList()
{
	wares->getGoodsList();
}

void Administration::logOut()
{
	wares->writeGoodsList(fileNameForGoods);
	wares->writeSoldGoodsList(fileNameForSoldGoods);
}

void Administration::showAllUser()
{
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	std::cout << "��ע���û�����" << std::endl;
	FILE * file;
	errno_t err = fopen_s(&file, fileNameForUser, "r");
	if (err != 0)
	{
		std::cout << "open file error!" << std::endl;
		fclose(file);
		return;
	}
	char userName[MAXSIZE], userPassword[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", userName, MAXSIZE);
		fscanf_s(file, "%s", userPassword, MAXSIZE);
		if (feof(file))
			break;
		std::cout << userName << std::endl;
	}
	std::cout << delim << std::endl;
	fclose(file);
}

void Administration::setPasswordToDefault()
{
	char userName[MAXSIZE];
	std::cout << "������Ҫ�޸ĵ��û����û���" << std::endl;
	std::cin >> userName;
	FILE *file;
	errno_t err = fopen_s(&file, fileNameForUser, "r+");
	if (err != 0)
	{
		printf("open file error\n");
		fclose(file);
		return;
	}
	char stdName[MAXSIZE], stdPassword[MAXSIZE];
	while (true)
	{
		fscanf_s(file, "%s", stdName, MAXSIZE);
		fscanf_s(file, "%s", stdPassword, MAXSIZE);
		if (feof(file))
		{
			fclose(file);
			std::cout << "û�д��û���" << std::endl;
			return; // ���û�������
		}
		if (strcmp(userName, stdName) == 0)
		{
			// �ҵ���ƥ����û���
			fseek(file, -(int)strlen(stdPassword), SEEK_CUR);
			fprintf(file, "666666\n");
			std::cout << "�ɹ���" << std::endl;
			break;
	}
}
	fclose(file);
	return;
}


#define TEST 0
#if TEST == 1

int main()
{
	Administration admin("���.txt", "�����嵥.txt");
	admin.showSoldList();
	admin.showGoodList();
	//admin.searchForGoods();
	//admin.showGoodList();
	admin.addNewGoods();
	admin.showGoodList();
	admin.deleteGoods();
	system("pause");
	return 0;
}

#endif