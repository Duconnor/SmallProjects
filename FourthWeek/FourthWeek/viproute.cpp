#include "viproute.h"
#include <iostream>
using namespace std;

bool VIPRoute::printRoute()
{
	if (head == nullptr)
		return false;
	cout << "该路线为VIP路线" << endl;
	int sum = 0;
	for (Node *h = head; h != nullptr; h = h->next)
	{
		sum += h->city->getPrice();
		if (h->next != nullptr)
			cout << h->city->getName() << "-";
		else
			cout << h->city->getName() << endl;
	}
	cout << "旅游费用为：" << (double)sum*(0.8) << endl;
	return true;
}

City ** VIPRoute::getRoute(int &number,int &flag)
{
	City **route = new City*[MAXSIZE];
	int count = 0;
	for (Node *h = head; h != nullptr; h = h->next)
	{
		route[count] = h->city;
		count++;
	}
	number = count;
	flag = 1; // VIP
	return route;
}

#if TEST == 3
int main()
{
	char name[MAXSIZE];
	City **c = new City*[3];
	CityList list;
	list.initialize("pricelist.txt");
	list.printList();
	cin >> name;
	c[0] = list.find(name);
	cin >> name;
	c[1] = list.find(name);
	cin >> name;
	c[2] = list.find(name);
	VIPRoute vroute;
	vroute.createRoute(c, 3);
	vroute.printRoute();
	system("pause");
	return 0;
}
#endif