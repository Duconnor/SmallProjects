#include "purchase.h"
#include "md5.h"
#include <algorithm>
#include <string>

Purchase::Purchase(char * fileNameGoods, char * fileNameSoldGoods,char * fileNameCart, User * u)
{
	wares = new WareHouse(fileNameGoods, fileNameSoldGoods);
	user = u;
	std::cout << "更新购物车..." << std::endl;
	for (int i = 0; i < user->shoppingCart.size(); i++)
	{
		Goods * goods = user->shoppingCart[i];
		Goods * temp = wares->searchByID(goods->getID());
		if (temp == nullptr)
		{
			// 该商品已被删除或数量小于购物车中的数量
			std::cout << "商品" << goods->getName() << " " << goods->getBrand() << " 已下架，已从购物车中为您删除" << std::endl;
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

// 增加搜索到物品后可直接添加到购物车功能
Goods * Purchase::searchForGoods(bool flag = false)
{
	// flag如果为true则为单独调用，否则为其它功能调用（此时禁用直接添加功能）
	if (flag)
	{
		std::cout << "是否需要在搜索成功时将物品添加进购物车，是请输入1，否则请输入0：";
		int order = -1;
		std::cin >> order;
		if (order == 1)
		{
			addToShoppingCart();
			return nullptr;
		}
	}
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
		if (searchList->get(0)->getNumber() == 0)
		{
			std::cout << "没有找到该物品" << std::endl;
			return nullptr;
		}
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
		int count = 0;
		for(auto goods:*searchList)
			if (goods->getNumber() == 0)
				count++;
		if (count == searchList->size())
		{
			std::cout << "没有找到对应商品" << std::endl;
			return nullptr;
		}
		if (count == searchList->size() - 1)
		{
			std::cout << "成功！" << std::endl;
			char delim[] = { "*******************************************************************************************************" };
			std::cout << delim << std::endl;
			for (auto goods : *searchList)
				if (goods->getNumber() != 0)
					goods->display();
			std::cout << delim << std::endl;
			return (searchList->get(0));
		}
		std::cout << "有超过一种的商品符合查询条件，如下所示" << std::endl;
		char delim[] = { "*******************************************************************************************************" };
		std::cout << delim << std::endl;
		for (auto goods : *searchList)
			if(goods->getNumber()!=0)
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

void Purchase::addToShoppingCart()
{
	Goods * goods = searchForGoods();
	undoObject * undoGoods = nullptr;
	if (goods == nullptr)
		return;
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
	bool addFlag = true;
	for (; i < user->shoppingCart.size(); i++)
	{
		if (strcmp(user->shoppingCart[i]->getID(), goodsInCart->getID()) == 0)
		{
			if (user->shoppingCart[i]->getNumber() + goodsInCart->getNumber() > goods->getNumber())
			{
				std::cout << "没有足够的商品可供添加" << std::endl;
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
	std::cout << "添加成功！已在购物车中等亲！" << std::endl;
	std::cout << "购物车中的商品有" << std::endl;
	showShoppingCart();
}

void Purchase::deleteGoodsInShoppingCart()
{
	undoObject * undoGoods = nullptr;
	std::cout << "请输入要删除的商品名称" << std::endl;
	char name[MAXSIZE];
	std::cin >> name;
	std::cout << "请输入要删除的商品数量" << std::endl;
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
		std::cout << "购物车内没有找到该商品" << std::endl;
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
			std::cout << "删除数量超过购物车中该商品的数量，删除失败" << std::endl;
			return;
		}
		undoStack.push(undoGoods);
		std::cout << "删除成功！" << std::endl;
		std::cout << "购物车中的商品有" << std::endl;
		showShoppingCart();
	}
	else
	{
		char delim[] = { "*******************************************************************************************************" };
		std::cout << "有不止一件商品满足条件" << std::endl;
		std::cout << delim << std::endl;
		for (int i : indexList)
			user->shoppingCart[i]->display();
		std::cout << delim << std::endl;
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
			std::cout << "删除数量超过购物车中该商品的数量，删除失败" << std::endl;
			return;
		}
		undoStack.push(undoGoods);
		std::cout << "删除成功！" << std::endl;
		std::cout << "购物车中的商品有" << std::endl;
		showShoppingCart();
	}
}

// 增加在展示购物车时同时展示购物车内商品总价格的功能
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
	std::cout << "总金额为：" << sum << std::endl;
}

void Purchase::pay()
{
	std::cout << "您购物车中的商品有" << std::endl;
	showShoppingCart();
	double sum = 0.0;
	bool notEnoughFlag = false;
	for (auto goods : user->shoppingCart)
	{
		Goods * temp = wares->searchByID(goods->getID());
		if (temp->getNumber() < goods->getNumber())
		{
			std::cout << "商品 " << goods->getName() << " " << goods->getBrand() << " 库存不足" << std::endl;
			notEnoughFlag = true;
			continue;
		}
		sum += (goods->getPrice())*goods->getNumber();
	}
	std::cout << "一共需要支付" << sum << "元" << std::endl;
	std::cout << "确认请输入1，取消请输入0" << std::endl;
	int order = -1;
	std::cin >> order;
	if (order)
	{
		wares->soldGoods(user->shoppingCart, user->getUserName());
		std::cout << "成功！" << std::endl;
		if (!notEnoughFlag)
			user->shoppingCart.clear();
		else
		{
			std::cout << "是否需要帮您删除掉库存不足的物品，要删除请输入1，否则输入0" << std::endl;
			int order2 = -1;
			std::cin >> order2;
			if (order2)
				user->shoppingCart.clear();
		}
	}
	else
		std::cout << "操作取消！" << std::endl;
	std::cout << "购物车中的商品有" << std::endl;
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

void Purchase::revisePassword()
{
	std::cout << "请输入新密码: ";
	char newPassword[MAXSIZE];
	std::cin >> newPassword;
	MD5 md5(newPassword);
	string s = md5.toStr();
	bool flag = user->revisePassword(s.c_str(), "用户.txt");
	if (flag)
		std::cout << "成功！" << std::endl;
	else
		std::cout << "失败！" << std::endl;
}

void Purchase::undo()
{
	if (undoStack.empty())
	{
		std::cout << "没有步骤可撤销" << std::endl;
		return;
	}
	undoObject * undo = undoStack.top();
	undoStack.pop();
	if (undo->getType() == removal)
	{
		// 该商品原来的操作是删除
		Goods * undoGoods = new Goods;
		undoGoods->setBrand(undo->getBrand());
		undoGoods->setID(undo->getID());
		undoGoods->setName(undo->getName());
		undoGoods->setNumber(undo->getNumber());
		undoGoods->setPrice(undo->getPrice());
		std::cout << "删除" << undo->getName()<<"的操作被撤销" << std::endl;
		user->shoppingCart.insert(undo->getIndex(), undoGoods);
	}
	else if (undo->getType() == add)
	{
		std::cout << "添加" << undo->getName() << "的操作被撤销" << std::endl;
		user->shoppingCart.remove(undo->getIndex());
	}
	else if (undo->getType() == numberLess)
	{
		std::cout << "删除" << undo->getNumber() - user->shoppingCart[undo->getIndex()]->getNumber() <<
			"件" << undo->getName() << "的操作被撤销" << std::endl;
		user->shoppingCart[undo->getIndex()]->setNumber(undo->getNumber());
	}
	else if (undo->getType() == numberPlus)
	{
		std::cout << "增加" << user->shoppingCart[undo->getIndex()]->getNumber() - undo->getNumber() <<
			"件" << undo->getName() << "的操作被撤销" << std::endl;
		user->shoppingCart[undo->getIndex()]->setNumber(undo->getNumber());
	}
	std::cout << "购物车中的商品有" << std::endl;
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