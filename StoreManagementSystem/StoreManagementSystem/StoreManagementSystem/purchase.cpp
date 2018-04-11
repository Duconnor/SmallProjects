#include "purchase.h"
#include <algorithm>

Purchase::Purchase(char * fileNameGoods, char * fileNameSoldGoods,char * fileNameCart, User * u)
{
	wares = new WareHouse(fileNameGoods, fileNameSoldGoods);
	user = u;
	std::cout << "���¹��ﳵ..." << std::endl;
	for (int i = 0; i < user->shoppingCart.size(); i++)
	{
		Goods * goods = user->shoppingCart[i];
		Goods * temp = wares->searchByID(goods->getID());
		if (temp == nullptr)
		{
			// ����Ʒ�ѱ�ɾ��������С�ڹ��ﳵ�е�����
			std::cout << "��Ʒ" << goods->getName() << " " << goods->getBrand() << " ���¼ܣ��Ѵӹ��ﳵ��Ϊ��ɾ��" << std::endl;
			user->shoppingCart.remove(i);
		}
	}
	std::cout << "���ﳵ�������" << std::endl;
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

void Purchase::addToShoppingCart()
{
	Goods * goods = searchForGoods();
	int number = 0;
	std::cout << "������Ҫ��ӵ���Ʒ����" << std::endl;
	std::cin >> number;
	if (number > goods->getNumber())
	{
		std::cout << "û���㹻����Ʒ�ɹ����" << std::endl;
		return;
	}
	Goods * goodsInCart = new Goods(goods);
	goodsInCart->setNumber(number);
	int i = 0;
	bool addFlag = true;
	for (; i < user->shoppingCart.size(); i++)
	{
		if (strcmp(user->shoppingCart[i]->getID(), goodsInCart->getID()) == 0)
		{
			if (user->shoppingCart[i]->getNumber() + goodsInCart->getNumber() > goods->getNumber())
			{
				std::cout << "û���㹻����Ʒ�ɹ����" << std::endl;
				addFlag = false;
				return;
			}
			user->shoppingCart[i]->setNumber(user->shoppingCart[i]->getNumber() + goodsInCart->getNumber());
			delete goodsInCart;
			addFlag = false;
			break;
		}
		if (strcmp(user->shoppingCart[i]->getID(), goodsInCart->getID()) > 0)
			break;
	}
	if(addFlag)
		user->shoppingCart.insert(i, goodsInCart);
	std::cout << "��ӳɹ������ڹ��ﳵ�е��ף�" << std::endl;
}

void Purchase::deleteGoodsInShoppingCart()
{
	std::cout << "������Ҫɾ������Ʒ����" << std::endl;
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
		std::cout << "���ﳵ��û���ҵ�����Ʒ" << std::endl;
		return;
	}
	else if (indexList.size() == 1)
	{
		user->shoppingCart.remove(indexList[0]);
		std::cout << "ɾ���ɹ���" << std::endl;
	}
	else
	{
		char delim[] = { "*******************************************************************************************************" };
		std::cout << "�в�ֹһ����Ʒ��������" << std::endl;
		std::cout << delim << std::endl;
		for (int i : indexList)
			user->shoppingCart[i]->display();
		std::cout << delim << std::endl;
		std::cout << "������ID��һ����ѯ" << std::endl;
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
			std::cout << "��ѯ���ɹ�" << std::endl;
			return;
		}
		user->shoppingCart.remove(index);
		std::cout << "ɾ���ɹ���" << std::endl;
	}
}

void Purchase::showShoppingCart()
{
	//for (auto goods : user->shoppingCart)
	//	goods->display();
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	for (int i = 0; i < user->shoppingCart.size(); i++)
		user->shoppingCart[i]->display();
	std::cout << delim << std::endl;
}

void Purchase::pay()
{
	std::cout << "�����ﳵ�е���Ʒ��" << std::endl;
	showShoppingCart();
	double sum = 0.0;
	for (auto goods : user->shoppingCart)
	{
		Goods * temp = wares->searchByID(goods->getID());
		if (temp->getNumber() < goods->getNumber())
		{
			std::cout << "��Ʒ" << goods->getName() << " " << goods->getBrand() << " ��治��" << std::endl;
			continue;
		}
		sum += goods->getPrice();
	}
	std::cout << "һ����Ҫ֧��" << sum << "Ԫ" << std::endl;
	std::cout << "ȷ��������1��ȡ��������0" << std::endl;
	int order = -1;
	std::cin >> order;
	if (order)
	{
		wares->soldGoods(user->shoppingCart, user->getUserName());
		std::cout << "�ɹ���" << std::endl;
		std::cout << "�Ƿ���Ҫ����ɾ������治�����Ʒ��Ҫɾ��������1����������0" << std::endl;
		int order2 = -1;
		std::cin >> order2;
		if(order2)
			user->shoppingCart.clear();
	}
	else
		std::cout << "����ȡ����" << std::endl;
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
	fprintf(file, "����\t");
	fprintf(file, "Ʒ��\t");
	fprintf(file, "�۸�\t");
	fprintf(file, "����\n");
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
	if (user->logIn("�û�.txt"))
		std::cout << "�ɹ���" << std::endl;
	else
		return 0;
	Purchase pur("���.txt", "�����嵥.txt", "user1.txt", user);
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