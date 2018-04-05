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
		for (auto goods : *searchList)
			goods->display();
		return (searchList->get(0));
	}
	else
	{
		std::cout << "�г���һ�ֵ���Ʒ���ϲ�ѯ������������ʾ" << std::endl;
		for (auto goods : *searchList)
			goods->display();
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
			searchGoods->display();
			return searchGoods;
		}
	}
}

void Purchase::addToShoppingCart()
{
	Goods * goods = searchForGoods();
	user->shoppingCart.insert(goods);
	std::cout << "��ӳɹ������ڹ��ﳵ�е��ף�" << std::endl;
}

void Purchase::deleteGoodsInShoppingCart()
{
	std::cout << "������Ҫɾ������Ʒ����" << std::endl;
	
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
