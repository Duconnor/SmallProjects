#include "purchase.h"
#include "md5.h"
#include <algorithm>
#include <string>

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
	while (!undoStack.empty())
	{
		undoObject * temp = undoStack.top();
		undoStack.pop();
		delete temp;
	}
}

void Purchase::showGoodsList()
{
	wares->getGoodsList(1);
}

// ������������Ʒ���ֱ����ӵ����ﳵ����
Goods * Purchase::searchForGoods(bool flag = false)
{
	// flag���Ϊtrue��Ϊ�������ã�����Ϊ�������ܵ��ã���ʱ����ֱ����ӹ��ܣ�
	if (flag)
	{
		std::cout << "�Ƿ���Ҫ�������ɹ�ʱ����Ʒ��ӽ����ﳵ����������1������������0��";
		int order = -1;
		std::cin >> order;
		if (order == 1)
		{
			addToShoppingCart();
			return nullptr;
		}
	}
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
		if (searchList->get(0)->getNumber() == 0)
		{
			std::cout << "û���ҵ�����Ʒ" << std::endl;
			return nullptr;
		}
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
		int count = 0;
		for(auto goods:*searchList)
			if (goods->getNumber() == 0)
				count++;
		if (count == searchList->size())
		{
			std::cout << "û���ҵ���Ӧ��Ʒ" << std::endl;
			return nullptr;
		}
		if (count == searchList->size() - 1)
		{
			std::cout << "�ɹ���" << std::endl;
			char delim[] = { "*******************************************************************************************************" };
			std::cout << delim << std::endl;
			for (auto goods : *searchList)
				if (goods->getNumber() != 0)
					goods->display();
			std::cout << delim << std::endl;
			return (searchList->get(0));
		}
		std::cout << "�г���һ�ֵ���Ʒ���ϲ�ѯ������������ʾ" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			if(goods->getNumber()!=0)
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
	undoObject * undoGoods = nullptr;
	if (goods == nullptr)
		return;
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
			undoGoods = new undoObject(user->shoppingCart[i]);
			undoGoods->setIndex(i);
			undoGoods->setType(3);
			user->shoppingCart[i]->setNumber(user->shoppingCart[i]->getNumber() + goodsInCart->getNumber());
			delete goodsInCart;
			addFlag = false;
			break;
		}
		if (strcmp(user->shoppingCart[i]->getID(), goodsInCart->getID()) > 0)
			break;
	}
	if (addFlag)
	{
		undoGoods = new undoObject(goodsInCart);
		undoGoods->setIndex(i);
		undoGoods->setType(1);
		user->shoppingCart.insert(i, goodsInCart);
	}
	undoStack.push(undoGoods);
	std::cout << "��ӳɹ������ڹ��ﳵ�е��ף�" << std::endl;
	std::cout << "���ﳵ�е���Ʒ��" << std::endl;
	showShoppingCart();
}

void Purchase::deleteGoodsInShoppingCart()
{
	undoObject * undoGoods = nullptr;
	std::cout << "������Ҫɾ������Ʒ����" << std::endl;
	char name[MAXSIZE];
	std::cin >> name;
	std::cout << "������Ҫɾ������Ʒ����" << std::endl;
	int number = 0;
	std::cin >> number;
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
		if (number == user->shoppingCart[indexList[0]]->getNumber())
		{
			undoGoods = new undoObject(user->shoppingCart[indexList[0]]);
			undoGoods->setIndex(indexList[0]);
			undoGoods->setType(0);
			user->shoppingCart.remove(indexList[0]);
		}
		else if (number < user->shoppingCart[indexList[0]]->getNumber())
		{
			undoGoods = new undoObject(user->shoppingCart[indexList[0]]);
			undoGoods->setIndex(indexList[0]);
			undoGoods->setType(2);
			user->shoppingCart[indexList[0]]->setNumber(user->shoppingCart[indexList[0]]->getNumber() - number);
		}
		else
		{
			std::cout << "ɾ�������������ﳵ�и���Ʒ��������ɾ��ʧ��" << std::endl;
			return;
		}
		undoStack.push(undoGoods);
		std::cout << "ɾ���ɹ���" << std::endl;
		std::cout << "���ﳵ�е���Ʒ��" << std::endl;
		showShoppingCart();
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
		if (number == user->shoppingCart[index]->getNumber())
		{
			undoGoods = new undoObject(user->shoppingCart[index]);
			undoGoods->setIndex(index);
			undoGoods->setType(0);
			user->shoppingCart.remove(index);
		}
		else if (number < user->shoppingCart[index]->getNumber())
		{
			undoGoods = new undoObject(user->shoppingCart[index]);
			undoGoods->setIndex(index);
			undoGoods->setType(2);
			user->shoppingCart[index]->setNumber(user->shoppingCart[index]->getNumber() - number);
		}
		else
		{
			std::cout << "ɾ�������������ﳵ�и���Ʒ��������ɾ��ʧ��" << std::endl;
			return;
		}
		undoStack.push(undoGoods);
		std::cout << "ɾ���ɹ���" << std::endl;
		std::cout << "���ﳵ�е���Ʒ��" << std::endl;
		showShoppingCart();
	}
}

// ������չʾ���ﳵʱͬʱչʾ���ﳵ����Ʒ�ܼ۸�Ĺ���
void Purchase::showShoppingCart()
{
	//for (auto goods : user->shoppingCart)
	//	goods->display();
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	double sum = 0.0;
	for (int i = 0; i < user->shoppingCart.size(); i++)
	{
		user->shoppingCart[i]->display();
		sum += (user->shoppingCart[i]->getPrice()*user->shoppingCart[i]->getNumber());
	}
	std::cout << delim << std::endl;
	std::cout << "�ܽ��Ϊ��" << sum << std::endl;
}

void Purchase::pay()
{
	std::cout << "�����ﳵ�е���Ʒ��" << std::endl;
	showShoppingCart();
	double sum = 0.0;
	bool notEnoughFlag = false;
	for (auto goods : user->shoppingCart)
	{
		Goods * temp = wares->searchByID(goods->getID());
		if (temp->getNumber() < goods->getNumber())
		{
			std::cout << "��Ʒ " << goods->getName() << " " << goods->getBrand() << " ��治��" << std::endl;
			notEnoughFlag = true;
			continue;
		}
		sum += (goods->getPrice())*goods->getNumber();
	}
	std::cout << "һ����Ҫ֧��" << sum << "Ԫ" << std::endl;
	std::cout << "ȷ��������1��ȡ��������0" << std::endl;
	int order = -1;
	std::cin >> order;
	if (order)
	{
		wares->soldGoods(user->shoppingCart, user->getUserName());
		std::cout << "�ɹ���" << std::endl;
		if (!notEnoughFlag)
			user->shoppingCart.clear();
		else
		{
			std::cout << "�Ƿ���Ҫ����ɾ������治�����Ʒ��Ҫɾ��������1����������0" << std::endl;
			int order2 = -1;
			std::cin >> order2;
			if (order2)
				user->shoppingCart.clear();
		}
	}
	else
		std::cout << "����ȡ����" << std::endl;
	std::cout << "���ﳵ�е���Ʒ��" << std::endl;
	showShoppingCart();
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

void Purchase::revisePassword()
{
	std::cout << "������������: ";
	char newPassword[MAXSIZE];
	std::cin >> newPassword;
	MD5 md5(newPassword);
	string s = md5.toStr();
	bool flag = user->revisePassword(s.c_str(), "�û�.txt");
	if (flag)
		std::cout << "�ɹ���" << std::endl;
	else
		std::cout << "ʧ�ܣ�" << std::endl;
}

void Purchase::undo()
{
	if (undoStack.empty())
	{
		std::cout << "û�в���ɳ���" << std::endl;
		return;
	}
	undoObject * undo = undoStack.top();
	undoStack.pop();
	if (undo->getType() == removal)
	{
		// ����Ʒԭ���Ĳ�����ɾ��
		Goods * undoGoods = new Goods;
		undoGoods->setBrand(undo->getBrand());
		undoGoods->setID(undo->getID());
		undoGoods->setName(undo->getName());
		undoGoods->setNumber(undo->getNumber());
		undoGoods->setPrice(undo->getPrice());
		std::cout << "ɾ��" << undo->getName()<<"�Ĳ���������" << std::endl;
		user->shoppingCart.insert(undo->getIndex(), undoGoods);
	}
	else if (undo->getType() == add)
	{
		std::cout << "���" << undo->getName() << "�Ĳ���������" << std::endl;
		user->shoppingCart.remove(undo->getIndex());
	}
	else if (undo->getType() == numberLess)
	{
		std::cout << "ɾ��" << undo->getNumber() - user->shoppingCart[undo->getIndex()]->getNumber() <<
			"��" << undo->getName() << "�Ĳ���������" << std::endl;
		user->shoppingCart[undo->getIndex()]->setNumber(undo->getNumber());
	}
	else if (undo->getType() == numberPlus)
	{
		std::cout << "����" << user->shoppingCart[undo->getIndex()]->getNumber() - undo->getNumber() <<
			"��" << undo->getName() << "�Ĳ���������" << std::endl;
		user->shoppingCart[undo->getIndex()]->setNumber(undo->getNumber());
	}
	std::cout << "���ﳵ�е���Ʒ��" << std::endl;
	showShoppingCart();
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