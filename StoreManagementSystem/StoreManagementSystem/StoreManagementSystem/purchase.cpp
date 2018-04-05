#include "purchase.h"

Purchase::Purchase(char * fileNameGoods, char * fileNameSoldGoods,char * fileNameCart, User * u)
{
	wares = new WareHouse(fileNameGoods, fileNameSoldGoods);
	user = u;
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
	user->shoppingCart.insert(goods);
	std::cout << "添加成功！已在购物车中等亲！" << std::endl;
}

void Purchase::deleteGoodsInShoppingCart()
{
	std::cout << "请输入要删除的商品名称" << std::endl;
	
}

void Purchase::showShoppingCart()
{
}

void Purchase::pay()
{
}

void Purchase::logOut()
{
}
