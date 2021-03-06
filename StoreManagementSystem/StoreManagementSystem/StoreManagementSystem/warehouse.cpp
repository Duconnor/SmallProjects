#include "warehouse.h"
#include <stdio.h>
#include <stdlib.h>

const double VIPTHRESHOLD = 100.0;

WareHouse::WareHouse(char * fileName, char *fileName2)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	char fileID[MAXIDSIZE];
	char inputName[MAXSIZE];
	char fileBrand[MAXSIZE];
	double filePrice;
	int fileNumber;
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	while (true)
	{
		fscanf_s(file, "%s", fileID, MAXIDSIZE);
		if (feof(file))
			break;
		fscanf_s(file, "%s", inputName, MAXSIZE);
		fscanf_s(file, "%s", fileBrand, MAXSIZE);
		fscanf_s(file, "%lf", &filePrice);
		fscanf_s(file, "%d", &fileNumber);
		Goods *goods = new Goods(fileID, inputName, fileBrand, filePrice, fileNumber);
		goodsList.insert(goods);
	}
	fclose(file);
	if (errno_t err = fopen_s(&file, fileName2, "r") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	char fileBuyerName[MAXSIZE];
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	fscanf_s(file, "%s", inputName, MAXSIZE);
	while (true)
	{
		fscanf_s(file, "%s", fileID, MAXIDSIZE);
		if (feof(file))
			break;
		fscanf_s(file, "%s", inputName, MAXSIZE);
		fscanf_s(file, "%s", fileBrand, MAXSIZE);
		fscanf_s(file, "%lf", &filePrice);
		fscanf_s(file, "%d", &fileNumber);
		fscanf_s(file, "%s", fileBuyerName, MAXSIZE);
		SoldGoods *goods = new SoldGoods(fileID, inputName, fileBrand, filePrice, fileNumber, fileBuyerName);
		soldGoodsList.insert(goods);
	}
	fclose(file);
}

WareHouse::~WareHouse()
{
	for (Goods* goods : goodsList)
		delete goods;
	for (SoldGoods* goods : soldGoodsList)
		delete goods;
}

void WareHouse::writeGoodsList(char * fileName)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "w") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量\n");
	for (Goods* goods : goodsList)
	{
		fprintf(file, "%s\t", goods->getID());
		fprintf(file, "%s\t", goods->getName());
		fprintf(file, "%s\t", goods->getBrand());
		fprintf(file, "%0.1lf\t", goods->getPrice());
		fprintf(file, "%d\n", goods->getNumber());
	}
	fclose(file);
}

void WareHouse::writeSoldGoodsList(char * fileName)
{
	FILE *file;
	if (errno_t err = fopen_s(&file, fileName, "w") != 0)
	{
		printf("open file error\n");
		exit(-1);
	}
	fprintf(file, "ID\t");
	fprintf(file, "名称\t");
	fprintf(file, "品牌\t");
	fprintf(file, "价格\t");
	fprintf(file, "数量\t");
	fprintf(file, "用户名\n");
	for (SoldGoods* goods : soldGoodsList)
	{
		fprintf(file, "%s\t", goods->getID());
		fprintf(file, "%s\t", goods->getName());
		fprintf(file, "%s\t", goods->getBrand());
		fprintf(file, "%0.1lf\t", goods->getPrice());
		fprintf(file, "%d\t", goods->getNumber());
		fprintf(file, "%s\n", goods->getBuyerName());
	}
	fclose(file);
}

Goods * WareHouse::searchByID(char * ID)
{
	Goods * result = nullptr;
	for (auto goods : goodsList)
		if (strcmp(goods->getID(), ID) == 0)
			if (goods->getNumber() != -1)
			{
				result = goods;
				break;
			}
	return result;
}

List<Goods*>* WareHouse::searchByName(char * name)
{
	List<Goods*> *result = new List<Goods*>;
	for (auto goods : goodsList)
		if (strcmp(goods->getName(), name) == 0 && goods->getNumber() != -1)
			(*result).insert(goods);
	return result;
}

List<Goods*>* WareHouse::searchByBrand(char * brand)
{
	List<Goods*>* result = new List<Goods*>;
	for (auto goods : goodsList)
		if (strcmp(goods->getBrand(), brand) == 0 && goods->getNumber() != -1)
			(*result).insert(goods);
	return result;
}

Goods * WareHouse::administrationSearch(Goods & newGoods)
{
	Goods * result = nullptr;
	for (auto goods : goodsList)
		if (strcmp(goods->getName(), newGoods.getName()) == 0 && strcmp(goods->getBrand(), newGoods.getBrand()) == 0)
		{
			result = goods;
			break;
		}
	return result;
}

bool WareHouse::doesExist(char * name, char * brand)
{
	List<Goods*> *searchList = searchByName(name);
	for (auto goods : *searchList)
		if (strcmp(goods->getBrand(), brand) == 0)
			return true;
	return false;

}

void WareHouse::addNewGoods(Goods * newGoods)
{
	Goods * temp = administrationSearch(*newGoods);
	if (temp != nullptr)
	{
		temp->setPrice(newGoods->getPrice());
		temp->setNumber(newGoods->getNumber());
		return;
	}
	temp = goodsList.get(goodsList.size() - 1);
	char ID[MAXIDSIZE];
	strncpy_s(ID, MAXIDSIZE, temp->getID() + 1, 5);
	int nextID = atoi(ID) + 1;
	int length = strlen(ID);
	ID[0] = 'F';
	if (nextID / 10000 != 0)
		std::cout << "添加失败，库存内商品过多！" << std::endl;
	int index = 1;
	while (index <= 4)
	{
		ID[index] = (nextID / (int)pow(10, 4 - index)) + '0';
		nextID = nextID % (int)pow(10, 4 - index);
		index++;
	}
	ID[5] = '\0';
	newGoods->setID(ID);
	goodsList.insert(newGoods);
}

void WareHouse::deleteGoods(Goods * goods)
{
	goods->setNumber(-1);
}

void WareHouse::soldGoods(List<Goods*> & shoppingCart, char *buyerName)
{
	int count = 0, length = shoppingCart.size(), index = 0;
	while(true)
	{
		if (count >= length)
			break;
		Goods * goods = shoppingCart[index];
		Goods *temp = searchByID(goods->getID());
		if (goods->getNumber() > temp->getNumber())
		{
			index++;
			count++;
			continue;
		}
		temp->setNumber(temp->getNumber() - goods->getNumber());
		SoldGoods * soldGoods = new SoldGoods(temp->getID(), temp->getName(),
			temp->getBrand(), temp->getPrice(), goods->getNumber(), buyerName);
		soldGoodsList.insert(soldGoods);
		shoppingCart.remove(index);
		count++;
	}
}

void WareHouse::modifyGoodsPrice(Goods * goods, double newPrice)
{
	goods->setPrice(newPrice);
}

void WareHouse::modifyGoodsNumber(Goods * goods, int newNumber)
{
	goods->setNumber(newNumber);
}

void WareHouse::getSoldGoodsList()
{
	List<SoldGoods*> tempList;
	for (SoldGoods *goods : soldGoodsList)
	{
		SoldGoods * sold = new SoldGoods(*goods);
		tempList.insert(sold);
	}
	int length = tempList.size();
	// 合并相同ID和价格的商品
	for (int i = 0; i < length; i++)
		for (int j = i + 1; j < length; j++)
			if (strcmp(tempList[j]->getID(), tempList[i]->getID()) == 0 && tempList[j]->getPrice() == tempList[i]->getPrice())
			{
				tempList[i]->setNumber(tempList[j]->getNumber() + tempList[i]->getNumber());
				tempList.remove(j);
				j--;
				length--;
			}
	// 按照ID升序排列
	for (int i = 1; i < length; i++)
	{
		int j = i ;
		while (j > 0 && strcmp(tempList[j - 1]->getID(), tempList[j]->getID()) > 0)
		{
			SoldGoods * temp = tempList[j];
			tempList[j] = tempList[j-1];
			tempList[j - 1] = temp;
			j--;
		}
	}
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	std::cout << std::left << std::setw(16) << "ID" << std::setw(16) << "名称" << std::setw(16) 
		<< "品牌" << std::setw(16) << "价格" << std::setw(16) << "数量" << std::endl;
	for (auto goods : tempList)
		goods->display();
	std::cout << delim << std::endl;
	for (auto goods : tempList)
		delete goods;
}

void WareHouse::getGoodsList()
{
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	std::cout << std::left << std::setw(16) << "ID" << std::setw(16) << "名称" << std::setw(16) << "品牌"
		<< std::setw(16) << "价格" << std::setw(16) << "数量" << std::endl;
	for (Goods *goods : goodsList)
		if(goods->getNumber()!=-1)
			goods->display();
	std::cout << delim << std::endl;
}

void WareHouse::getGoodsList(int x)
{
	char delim[] = { "*******************************************************************************************************" };
	std::cout << delim << std::endl;
	std::cout << std::left << std::setw(16) << "ID" << std::setw(16) << "名称" << std::setw(16) << "品牌"
		<< std::setw(16) << "价格" << std::setw(16) << "数量" << std::endl;
	for (Goods *goods : goodsList)
		if (goods->getNumber() != -1 && goods->getNumber() != 0)
			goods->display();
	std::cout << delim << std::endl;
}

void WareHouse::undoAdd(undoObject * undo)
{
	int index = -1;
	for (auto goods : goodsList)
		if (strcmp(goods->getName(), undo->getName()) == 0 && strcmp(goods->getBrand(), undo->getBrand()) == 0)
			index = goodsList.getIndex(goods);
	if (index == -1)
		return;
	goodsList.remove(index);
}

void WareHouse::undoDelete(undoObject * undo)
{
	for (auto goods : goodsList)
		if (strcmp(undo->getName(), goods->getName()) == 0 && strcmp(undo->getBrand(), goods->getBrand()) == 0)
		{
			goods->setNumber(undo->getNumber());
			break;
		}
}

void WareHouse::undoModify(undoObject * undo)
{
	for (auto goods : goodsList)
		if (strcmp(undo->getName(), goods->getName()) == 0 && strcmp(undo->getBrand(), goods->getBrand()) == 0)
		{
			if (undo->getType() == numberLess || undo->getType() == numberPlus)
				goods->setNumber(undo->getNumber());
			else if (undo->getType() == priceLess || undo->getType() == pricePlus)
				goods->setPrice(undo->getPrice());
			break;
		}
}

bool WareHouse::isVIP(char * userName)
{
	double sumSpent = getSumSpent(userName);
	if (sumSpent > VIPTHRESHOLD)
		return true;
	else
		return false;
}

double WareHouse::getSumSpent(char * userName)
{
	double sumSpent = 0.0;
	for (auto goods : soldGoodsList)
		if (strcmp(goods->getBuyerName(), userName) == 0)
			sumSpent += (goods->getPrice()*goods->getNumber());
	return sumSpent;
}




#define TEST 0
#if TEST == 1

int main()
{
	WareHouse warehouse("库存.txt", "已售清单.txt");
//	warehouse.getSoldGoodsList();
	warehouse.getGoodsList();
	Goods * goods = warehouse.searchByID("F0002");
	warehouse.modifyGoodsNumber(goods, -1);
	warehouse.getGoodsList();
	List<Goods*> *searchList = warehouse.searchByName("酸奶");
	for (auto g : *searchList)
		g->display();
	Goods newGoods("F0010", "酸奶", "蒙牛", 101.1, 2);
	Goods * pointer = warehouse.administrationSearch(newGoods);
	pointer->display();
	warehouse.addNewGoods(&newGoods);
	warehouse.getGoodsList();
	//Goods * goods = warehouse.searchByID("F0002");
	//std::cout << goods->getName() << std::endl;
	system("pause");
	return 0;
}

#endif