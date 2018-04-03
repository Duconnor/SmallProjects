#include "route.h"
#include "cityList.h"
#include <iostream>
using namespace std;

bool Route::createRoute(City ** list, int number)
{
	if (number < 0 || list == nullptr)
		return false;
	Node *tail = nullptr;
	for (int i = 0; i < number; i++)
	{
		Node *n = new Node(list[i]);
		if (head == nullptr)
		{
			// first element
			head = n;
			tail = n;
		}
		else
		{
			tail->next = n;
			tail = n;
		}
	}
	return true;
}

bool Route::printRoute()
{
	if (head == nullptr)
		return false;
	cout << "该路线为普通用户路线" << endl;
	int sum = 0;
	for (Node *h = head; h != nullptr; h = h->next)
	{
		sum += h->city->getPrice();
		if (h->next != nullptr)
			cout << h->city->getName() << "-";
		else
			cout << h->city->getName() << endl;
	}
	cout << "旅游费用为：" << sum << endl;
	return true;
}

bool Route::replaceCity(char * oldCityName, City * newCity)
{
	Node *pre = nullptr;
	Node *h = head;
	Node *node = new Node(newCity);
	for (; h != nullptr; h = h->next)
		if (strcmp(h->city->getName(), oldCityName) == 0)
			break;
		else
			pre = h;
	if (h == nullptr)
		return false;
	if (pre == nullptr)
	{
		// the first one to replace
		node->next = head->next;
		pre = head;
		head = node;
		delete pre;
		return true;
	}
	node->next = h->next;
	pre->next = node;
	delete h;
	return true;
}

bool Route::removeCity(char * cityName)
{
	Node *pre = nullptr;
	Node *h = head;
	for (; h != nullptr; h = h->next)
		if (strcmp(h->city->getName(), cityName) == 0)
			break;
		else
			pre = h;
	if (h == nullptr)
		return false;
	if (pre == nullptr)
	{
		// the first one to remove
		pre = head;
		head = head->next;
		delete pre;
		return true;
	}
	pre->next = h->next;
	delete h;
	return true;
}

bool Route::insertCity(char * cityPre, char * cityPost, City * newCity)
{
	Node *node = new Node(newCity);
	Node *pre = head;
	for (; pre != NULL; pre = pre->next)
		if (strcmp(cityPre, pre->city->getName()) == 0)
			break;
	if (pre == NULL)
		return false;
	Node *post = pre->next;
	if (pre == head && (strcmp(post->city->getName(), cityPost) != 0))
	{
		// 插入位置在头结点前面
		node->next = head;
		head = node;
		return true;
	}
	else if (post == NULL)
	{
		// 插入位置在尾结点后面
		pre->next = node;
		return true;
	}
	if (strcmp(cityPost, post->city->getName()) != 0)
		return false;
	node->next = post;
	pre->next = node;
	return true;
}

City ** Route::getRoute(int &number,int &flag)
{
	City **route = new City*[MAXSIZE];
	int count = 0;
	for (Node *h = head; h != nullptr; h = h->next)
	{
		route[count] = h->city;
		count++;
	}
	number = count;
	flag = 0; // 非VIP
	return route;
}

void Route::clear()
{
	Node *pre = nullptr;
	for (Node* h = head; h != nullptr;)
	{
		pre = h;
		h = h->next;
		delete pre;
	}
	head = nullptr;
}

bool Route::isEmpty()
{
	return (head == nullptr);
}

#if TEST == 2

// 单元测试
int main()
{
	char name[MAXSIZE];
	City **c = new City*[3];
	CityList list;
	//list.initialize("pricelist.txt");
	//list.printList();
	//cin >> name;
	//c[0] = list.find(name);
	//cin >> name;
	//c[1] = list.find(name);	
	//cin >> name;
	//c[2] = list.find(name);
	Route route;
	//route.createRoute(c, 3);
	//route.printRoute();
	//cin >> name;
	//City* city = list.find(name);
	//route.replaceCity("南京", city);
	//route.printRoute();
	File file;
	int number, flag;
	City ** alist = nullptr;
//	file.writeToBinaryFile("route.txt", alist, flag, number);
	City ** newlist = nullptr;
	file.readBinaryFile("route.txt", newlist, number);
	alist  = list.seekForAddress(newlist, number);
	Route newRoute;
	newRoute.createRoute(alist, number);
	newRoute.printRoute();
	system("pause");
	return 0;
}

#endif