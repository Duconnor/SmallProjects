#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEST 0 // 1 for test main, 0 for formal main

const int MAXSIZE = 1000;
const int TABLESIZE = 6;

// 价格表数据
int index[TABLESIZE];
char name[TABLESIZE][MAXSIZE];
int price[TABLESIZE];


// 从文件中读取价格表
void readDataFromFile(int index[], char name[][MAXSIZE], int price[])
{
	FILE* file;
	errno_t err = fopen_s(&file, "pricelist.txt", "r");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}
	for (int i = 0; i < TABLESIZE; i++)
	{
		fscanf_s(file, "%d", &index[i]);
		fscanf_s(file, "%s", name[i], MAXSIZE);
		fscanf_s(file, "%d", &price[i]);
	}
	fclose(file);
}


// 城市
struct City
{
	int index; // 该城市的编号
	char *name;
	int price;
	City(int i, char input[], int price) :index(i), name(input), price(price) {}
};

// 价格表
struct ListNode
{
	City* city;
	ListNode* next;
	ListNode(City* c) :city(c), next(NULL) {}
};

// 路线图
struct ListNodeRoute
{
	ListNode* node;
	ListNodeRoute* next;
	ListNodeRoute(ListNode* h) :node(h), next(NULL) {}
};

// 创建旅游城市价格表
ListNode* constructPriceTable()
{
	ListNode *head = NULL, *tail = NULL;
	for (int i = 0; i < TABLESIZE; i++)
	{
		City* city = new City(index[i], name[i], price[i]);
		ListNode* h = new ListNode(city);
		if (head == NULL)
		{
			// first element
			head = h;
			tail = h;
		}
		else
		{
			// not the first
			tail->next = h;
			tail = h;
		}
	}
	return head;
}


// 打印旅游城市价格表
void printPriceTable(ListNode* head)
{
	char delim[] = { "        " };
	for (ListNode* h = head; h != NULL; h = h->next)
		printf("%d%s%s%s%d\n", h->city->index, delim, h->city->name, delim, h->city->price);
}


// 利用给定的城市名称在旅游价格表中进行搜索，返回搜索到的结点的地址
// 没找到返回NULL
ListNode* searchForCity(char name[],ListNode *head)
{
	for (ListNode* h = head; h != NULL; h = h->next)
	{
		if (strcmp(name, h->city->name)==0)
			return h;
	}
	return NULL;
}


// 创建旅游路线
ListNodeRoute* constructTravelRoute(ListNode* priceHead, char *names)
{
	ListNodeRoute *routeHead = NULL, *tail = NULL;
	char *next = NULL, *name = NULL;
	char delim[] = { " " };
	name = strtok_s(names, delim, &next);
	while (name != NULL)
	{
		ListNodeRoute* h = new ListNodeRoute(searchForCity(name, priceHead));
		if (routeHead == NULL)
		{
			routeHead = h;
			tail = h;
		}
		else
		{
			tail->next = h;
			tail = h;
		}
		name = strtok_s(NULL, delim, &next);
	}
	return routeHead;
}

// 打印旅游路线
void printTravelRoute(ListNodeRoute* routeHead)
{
	int sum = 0;
	for (ListNodeRoute* h = routeHead; h != NULL; h = h->next)
	{
		sum += h->node->city->price;
		if (h->next == NULL)
			printf("%s\n", h->node->city->name);
		else
			printf("%s-", h->node->city->name);
	}
	printf("总价格：%d\n", sum);
}


// 将旅游路线图中的一个城市(this city)替换为另一个城市(that city)
bool replace(ListNodeRoute* &routeHead,ListNode* priceHead, char thisCity[], char thatCity[])
{
	ListNodeRoute* temp = new ListNodeRoute(searchForCity(thatCity, priceHead)); // 找到要替换的城市
	ListNodeRoute* pre = NULL, *h = routeHead;
	for (; h != NULL; h = h->next)
	{
		if (strcmp(thisCity, h->node->city->name) != 0)
			pre = h;
		else
			break;
	}
	if (pre == NULL)
	{
		// first element is the wanted one
		pre = routeHead;
		routeHead = temp;
		temp->next = pre->next;
		delete pre;
		return true;
	}
	else if (h != NULL)
	{
		temp->next = h->next;
		pre->next = temp;
		delete h;
		return true;
	}
	else
		return false; // 没找到要改的城市
}


// 在旅游路线中的两个城市(city one & city two)之间插入一个新的城市(new city)
bool insert(ListNodeRoute* &routeHead, ListNode* priceHead,char cityOne[], char cityTwo[], char newCity[])
{
	ListNodeRoute* temp = new ListNodeRoute(searchForCity(newCity, priceHead));
	ListNodeRoute* pre = routeHead;
	for (; pre != NULL; pre = pre->next)
		if (strcmp(cityOne, pre->node->city->name) == 0)
			break;
	if (pre == NULL)
		return false;
	ListNodeRoute*  post = pre->next;
	if (pre == routeHead && (strcmp(post->node->city->name, cityTwo) != 0))
	{
		// 插入位置在头结点前面
		temp->next = routeHead;
		routeHead = temp;
		return true;
	}
	else if (post == NULL)
	{
		// 插入位置在尾结点后面
		pre->next = temp;
		return true;
	}
	if (strcmp(cityTwo, post->node->city->name) != 0)
		return false;
	temp->next = post;
	pre->next = temp;
	return true;
}


// 删除旅游路线中的某一个城市(city)
bool remove(ListNodeRoute* &routeHead, ListNode* priceHead, char city[])
{
	ListNodeRoute* h = routeHead, *pre = NULL;
	for (; h != NULL; h = h->next)
		if (strcmp(city, h->node->city->name) == 0)
			break;
		else
			pre = h;
	if (h == NULL)
		return false;
	if (pre == NULL)
	{
		pre = h;
		routeHead = h->next;
		delete pre;
		return true;
	}
	else
	{
		pre->next = h->next;
		delete h;
		return true;
	}
}


// 查询指定城市的价格
int getPrice(ListNode* priceHead,char city[])
{
	for (ListNode* h = priceHead; h != NULL; h = h->next)
		if (strcmp(h->city->name, city) == 0)
			return h->city->price;
	return -1;
}


// 调整价格
bool adjustPrice(ListNode* priceHead, char city[], int price)
{
	for (ListNode* h = priceHead; h != NULL; h = h->next)
	{
		if (strcmp(h->city->name, city) == 0)
		{
			h->city->price = price;
			return true;
		}
	}
	return false;
}


#if TEST == 1

int main()
{

	/**********************/
	// test of struct City
	// result: OK
	//char *name = new char[MAXSIZE];
	//int price;
	//scanf_s("%d", &price);
	//scanf_s("%s", name, MAXSIZE);
	//City* city = new City(name, price);
	//printf("%d %s %d", city->index, city->name, city->price);
	//system("pause");
	//return 0;
	/***********************/

	/***********************/
	// test of printPriceTable
	// result: OK
	// information must be declared as global variables
	//readDataFromFile(index, name, price);
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//system("pause");
	//return 0;
	/**********************/

	/**********************/
	// test of constructTravelRoute
	// result: OK
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//char *names = new char[MAXSIZE];
	//gets_s(names, MAXSIZE);
	//ListNodeRoute* routeHead = constructTravelRoute(head, names);
	//printTravelRoute(routeHead);
	//system("pause");
	//return 0;
	/***********************/

	/***********************/
	// test of replace
	// result: OK
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//char *names = new char[MAXSIZE];
	//gets_s(names, MAXSIZE);
	//ListNodeRoute* routeHead = constructTravelRoute(head, names);
	//printTravelRoute(routeHead);
	//scanf_s("%s", names, MAXSIZE);
	//char *s = new char[MAXSIZE];
	//scanf_s("%s", s, MAXSIZE);
	//replace(routeHead, head, names, s);
	//printTravelRoute(routeHead);
	//system("pause");
	//return 0;
	/***********************/

	/***********************/
	// test of insert
	// result
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//char *names = new char[MAXSIZE];
	//gets_s(names, MAXSIZE);
	//ListNodeRoute* routeHead = constructTravelRoute(head, names);
	//printTravelRoute(routeHead);
	//scanf_s("%s", names, MAXSIZE);
	//char *s1 = new char[MAXSIZE], *s2 = new char[MAXSIZE];
	////scanf_s("%s", s1, MAXSIZE);
	//scanf_s("%s", s2, MAXSIZE);
	//insert(routeHead, head, names, s1, s2);
	//printTravelRoute(routeHead);
	//system("pause");
	//return 0;
	/**************************/

	/**************************/
	// test of remove
	// result: OK
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//char *names = new char[MAXSIZE];
	//gets_s(names, MAXSIZE);
	//ListNodeRoute* routeHead = constructTravelRoute(head, names);
	//printTravelRoute(routeHead);
	//scanf_s("%s", names, MAXSIZE);
	//remove(routeHead, head, names);
	//printTravelRoute(routeHead);
	//system("pause");
	//return 0;

	/***************************/
	// test of adjustPrice
	// result: good!
	//ListNode* head = constructPriceTable();
	//printPriceTable(head);
	//char *names = new char[MAXSIZE];
	//gets_s(names, MAXSIZE);
	//ListNodeRoute* routeHead = constructTravelRoute(head, names);
	//printTravelRoute(routeHead);
	//scanf_s("%s", names, MAXSIZE);
	//int price = 0;
	//scanf_s("%d", &price);
	//adjustPrice(head, names, price);
	//printTravelRoute(routeHead);
	//system("pause");
	//return 0;
    /*****************************/
}

#endif

// 展示菜单
void showMenu()
{
	char delim[] = "******************************************************************************************************************";
	printf("%s\n", delim);
	printf("                       菜单\n");
	printf("    1.打印旅游城市价格表\n");
	printf("    2.创建旅游路线\n");
	printf("    3.将旅游路线中的某个城市替换为其他的城市\n");
	printf("    4.在旅游路线中的两个城市之间，或第一个城市前面或最后一个城市后面，插入新的城市\n");
	printf("    5.删除旅游路线中的某个城市\n");
	printf("    6.调整旅游城市价格表中某个旅游城市的价格\n");
	printf("    *.退出程序\n");
	printf("%s\n", delim);
	printf("\n");
}


#if TEST == 0
// main
int main()
{
	readDataFromFile(index, name, price);
	ListNode* priceHead = constructPriceTable();
	ListNodeRoute* routeHead = NULL;
	int count = 0; // count表示创建了多少条旅游路线
	bool flag = true;
	while (flag)
	{
		char order;
		showMenu();
		printf("请输入您的操作：");
		scanf_s("%c", &order, 1);
		while (getchar() != '\n'); // 清空输入流
		switch (order)
		{
		case '1':printPriceTable(priceHead); break;
		case '2':
		{
			char cityNames[MAXSIZE];
			printf("请输入城市，已空格分割，换行结束：");
			gets_s(cityNames, MAXSIZE);
			routeHead = constructTravelRoute(priceHead, cityNames);
			if (routeHead == NULL)
			{
				printf("创建失败，可能是键入了不存在的城市名，或者是内存分配失败\n");
				break;
			}
			else
			{
				printf("创建成功！\n");
				printf("旅游线路为：");
				printTravelRoute(routeHead);
				break;
			}
		}
		case '3':
		{
			char thatCity[MAXSIZE], thisCity[MAXSIZE];
			printf("请输入被替换的城市：");
			scanf_s("%s", thisCity, MAXSIZE);
			while (getchar() != '\n');
			printf("请输入替换城市：");
			scanf_s("%s", thatCity, MAXSIZE);
			while (getchar() != '\n');
			if (!replace(routeHead, priceHead, thisCity, thatCity))
			{
				printf("修改失败，可能是键入了不存在于旅游线路中的城市\n");
				break;
			}
			printf("旅游线路更改为：");
			printTravelRoute(routeHead);
			break;
		}
		case '4':
		{
			char cityOne[MAXSIZE], cityTwo[MAXSIZE], newCity[MAXSIZE];
			char inputStream[MAXSIZE];
			printf("请输入两个在线路中连续的城市，如果插在头部前或尾部后，请只输入一个城市\n");
			gets_s(inputStream, MAXSIZE);
			char *s, *next;
			s = strtok_s(inputStream, " ", &next);
			int count = 0;
			while (s != NULL)
			{
				if (count == 0)
					strcpy_s(cityOne, s);
				else
					strcpy_s(cityTwo, s);
				s = strtok_s(NULL, " ", &next);
				count++;
			}
			printf("请输入需要插入的城市：");
			scanf_s("%s", newCity, MAXSIZE);
			while (getchar() != '\n');
			if (!insert(routeHead, priceHead, cityOne, cityTwo, newCity))
			{
				printf("修改失败，可能是键入了不连续的两个城市，或者键入的城市中有一个或多个不存在于旅游路线中\n");
				break;
			}
			else
			{
				printf("旅游路线修改为：");
				printTravelRoute(routeHead);
				break;
			}
		}
		case '5':
		{
			printf("请输入需要删除的城市：");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			if (!remove(routeHead, priceHead, city))
			{
				printf("删除失败，可能是键入了不存在于路线中的城市\n");
				break;
			}
			else
			{
				printf("旅游路线更改为：");
				printTravelRoute(routeHead);
			}
			break;
		}
		case '6':
		{
			printf("请输入需要调整价格的城市：");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			int price = getPrice(priceHead, city);
			if (price == -1)
			{
				printf("失败，可能是键入了不存在于价格表中的城市\n");
				break;
			}
			else
			{
				printf("%s原来的价格为%d，请输入调整后的价格：", city, price);
				scanf_s("%d", &price);
				while (getchar() != '\n');
				adjustPrice(priceHead, city, price);
				printPriceTable(priceHead);
				printf("旅游线路：");
				printTravelRoute(routeHead);
				break;
			}
		}
		case '*':flag = false; break;
		default:break;
		}
	}
	return 0;
}
#endif
