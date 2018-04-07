#include "purchase.h"
#include <algorithm>

Purchase::Purchase(char * fileNameGoods, char * fileNameSoldGoods,char * fileNameCart, User * u)
{
	wares = new WareHouse(fileNameGoods, fileNameSoldGoods);
	user = u;
	std::cout << "更新购物车..." << std::endl;
	for (int i = 0; i < user->shoppingCart.size(); i++)
	{
		Goods * goods = user->shoppingCart[i];
		Goods * temp = wares->searchByID(goods->getID());
		if (temp == nullptr || temp->getNumber() < goods->getNumber())
		{
			// 该商品已被删除或数量小于购物车中的数量
			std::cout << "商品" << goods->getName() << " " << goods->getBrand() << " 已下架或库存不足，已从购物车中为您删除" << std::endl;
			user->shoppingCart.remove(i);
		}
	}
	std::cout << "购物车更新完毕" << std::endl;
	fileNameForGoods = new char[MAXSIZE];
	fileNameForCart = new char[MAXSIZE];
	fileNameForSoldGoods = new char[MAXSIZE];
	strcpy_s(fileNameForGoods, strlen(fileNameGoods) + 1, fileNameGoods);
	strcpy_s(fileNameForCart, strlen(fileNameCart) + 1, fileNameCart);
	strcpy_s(fileNameForSoldGoods, strlen(fileNameSoldGoods) + 1, fileNameSoldGoods);
}

Purchase::~Purchase()
{
	delete wares;
	delete fileNameForGoods;
	delete fileNameForCart;
	delete fileNameForSoldGoods;
}

void Purchase::showGoodsList()
{
	wares->getGoodsList();
}

Goods * Purchase::searchForGoods()
{
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
		for (auto goods : *searchList)
			goods->display();
		return (searchList->get(0));
	}
	else
	{
		std::cout << "有超过一种的商品符合查询条件，如下所示" << std::endl;
		for (auto goods : *searchList)
			goods->display();
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
			searchGoods->display();
			return searchGoods;
		}
	}
}

void Purchase::addToShoppingCart()
{
	Goods * goods = searchForGoods();
	int number = 0;
	std::cout << "请输入要添加的商品个数" << std::endl;
	std::cin >> number;
	if (number > goods->getNumber())
	{
		std::cout << "没有足够的商品可供添加" << std::endl;
		return;
	}
	Goods * goodsInCart = new Goods(goods);
	goodsInCart->setNumber(number);
	int i = 0;
	for (; i < user->shoppingCart.size(); i++)
		if (strcmp(user->shoppingCart[i]->getID(), goodsInCart->getID()) > 0)
			break;
	user->shoppingCart.insert(i, goodsInCart);
	std::cout << "添加成功！已在购物车中等亲！" << std::endl;
}

void Purchase::deleteGoodsInShoppingCart()
{
	std::cout << "请输入要删除的商品名称" << std::endl;
	char name[MAXSIZE];
	std::cin >> name;
	List<int> indexList;
	for (auto goods : user->shoppingCart)
		if (strcmp(goods->getName(), name) == 0)
		{
			int index = user->shoppingCart.getIndex(goods);
			indexList.insert(index);
		}
	if (indexList.size() == 0)
	{
		std::cout << "购物车内没有找到该商品" << std::endl;
		return;
	}
	else if (indexList.size() == 1)
	{
		user->shoppingCart.remove(indexList[0]);
		std::cout << "删除成功！" << std::endl;
	}
	else
	{
		std::cout << "有不止一件商品满足条件" << std::endl;
		for (int i : indexList)
			user->shoppingCart[i]->display();
		std::cout << "请输入ID进一步查询" << std::endl;
		char ID[MAXIDSIZE];
		std::cin >> ID;
		int index = -1;
		for(int i:indexList)
			if (strcmp(user->shoppingCart[i]->getID(), ID) == 0)
			{
				index = i;
				break;
			}
		if (index == -1)
		{
			std::cout << "查询不成功" << std::endl;
			return;
		}
		user->shoppingCart.remove(index);
		std::cout << "删除成功！" << std::endl;
	}
}

void Purchase::showShoppingCart()
{
	//for (auto goods : user->shoppingCart)
	//	goods->display();
	for (int i = 0; i < user->shoppingCart.size(); i++)
		user->shoppingCart[i]->display();
}

void Purchase::pay()
{
	std::cout << "您购物车中的商品有" << std::endl;
	showShoppingCart();
	double sum = 0.0;
	for (auto goods : user->shoppingCart)
		sum += goods->getPrice();
	std::cout << "一共需要支付" << sum << "元" << std::endl;
	std::cout << "确认请输入1，取消请输入0" << std::endl;
	int order = -1;
	std::cin >> order;
	if (order)
	{
		wares->soldGoods(user->shoppingCart, user->getUserName());
		user->shoppingCart.clear();
		std::cout << "成功！" << std::endl;
	}
	else
		std::cout << "操作取消！" << std::endl;
}

void Purchase::logOut()
{
	wares->writeGoodsList(fileNameForGoods);
	wares->writeSoldGoodsList(fileNameForSoldGoods);
	FILE * file;
	errno_t err = fopen_s(&file, fileNameForCart, "w");
	if (err != 0)
	{
		printf("open file error\n");
		return;
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量\n");
	for (auto goods : user->shoppingCart)
	{
		fprintf(file, "%s\t", goods->getID());
		fprintf(file, "%s\t", goods->getName());
		fprintf(file, "%s\t", goods->getBrand());
		fprintf(file, "%0.1lf\t", goods->getPrice());
		fprintf(file, "%d\n", goods->getNumber());
	}
	fclose(file);
}

#define TEST 0
#if TEST == 1

int main()
{
	char name[30], password[30];
	scanf_s("%s", name, 30);
	scanf_s("%s", password, 30);
	User *user = new User(name, password);
	if (user->logIn("用户.txt"))
		std::cout << "成功！" << std::endl;
	else
		return 0;
	Purchase pur("库存.txt", "已售清单.txt", "user1.txt", user);
	pur.showGoodsList();
	pur.showShoppingCart();
	pur.addToShoppingCart();
	pur.showShoppingCart();
	pur.deleteGoodsInShoppingCart();
	pur.showShoppingCart();
	pur.pay();
	pur.showShoppingCart();
	pur.logOut();
	system("pause");
}

#endif