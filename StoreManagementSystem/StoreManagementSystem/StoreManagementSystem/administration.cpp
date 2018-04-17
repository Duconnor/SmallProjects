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
	// 查询特定的商品（先用商品名，不能确定则可以选择用ID或者进一步利用牌子）
	std::cout << "请输入商品名" << std::endl;
	char name[MAXSIZE];
	std::cin >> name;
	List<Goods*> *searchList = wares->searchByName(name);
	if ((*searchList).size() == 0)
	{
		std::cout << "没有找到相应商品" << std::endl;
		return nullptr;
	}
	else if ((*searchList).size() == 1)
	{
		std::cout << "成功！" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			goods->display();
		std::cout << delim << std::endl;
		return (searchList->get(0));
	}
	else
	{
		std::cout << "有超过一种的商品符合查询条件，如下所示" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			goods->display();
		std::cout << delim << std::endl;
		std::cout << "请输入ID进行进一步的查询" << std::endl;
		std::cin >> name;
		Goods * searchGoods = wares->searchByID(name);
		if (searchGoods == nullptr)
		{
			std::cout << "没有找到相应商品" << std::endl;
			return nullptr;
		}
		else
		{
			std::cout << "成功！" << std::endl;
			std::cout << delim << std::endl;
			searchGoods->display();
			std::cout << delim << std::endl;
			return searchGoods;
		}
	}
}

void Administration::addNewGoods()
{
	std::cout << "请先输入新产品的名称和品牌，系统会进行检查，请以空格分隔，回车结束" << std::endl;
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
	std::cout << "检查进行中......" << std::endl;
	if (wares->doesExist(name, brand))
	{
		std::cout << "添加失败，该商品已存在" << std::endl;
		return;
	}
	std::cout << "检查完毕，该商品之前不存在，可以添加" << std::endl;
	std::cout << "请输入新产品的价格和数量，以空格分隔，回车结束" << std::endl;
	double price;
	int number;
	std::cin >> price >> number;
	price = (double)((int)((price * 10) + 0.5)) / 10.0;
	Goods * newGoods = new Goods("", name, brand, price, number);
	wares->addNewGoods(newGoods);
	std::cout << "添加成功" << std::endl;
}

void Administration::deleteGoods()
{
	Goods * deleteGoods = searchForGoods();
	wares->deleteGoods(deleteGoods);
	std::cout << "删除成功" << std::endl;
}

void Administration::modifyGoodsInformation()
{
	Goods * goods = searchForGoods();
	std::cout << "请输入需要修改的信息类型，1代表修改价格，2代表修改数量" << std::endl;
	int order = 0;
	std::cin >> order;
	if (order == 1)
	{
		std::cout << "请输入修改后的价格" << std::endl;
		double price = 0.0;
		std::cin >> price;
		wares->modifyGoodsPrice(goods, price);
		std::cout << "修改成功！" << std::endl;
	}
	else
	{
		std::cout << "请输入修改后的数量" << std::endl;
		int number = 0;
		std::cin >> number;
		if (number < 0)
		{
			std::cout << "修改失败，数量不能为负" << std::endl;
			return;
		}
		wares->modifyGoodsNumber(goods, number);
		std::cout << "修改成功！" << std::endl;
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
	std::cout << "已注册用户如下" << std::endl;
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
	std::cout << "请输入要修改的用户的用户名" << std::endl;
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
			std::cout << "没有此用户！" << std::endl;
			return; // 该用户不存在
		}
		if (strcmp(userName, stdName) == 0)
		{
			// 找到了匹配的用户名
			fseek(file, -(int)strlen(stdPassword), SEEK_CUR);
			fprintf(file, "666666\n");
			std::cout << "成功！" << std::endl;
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
	Administration admin("库存.txt", "已售清单.txt");
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