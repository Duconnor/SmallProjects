#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEST 0 // 1 for test main, 0 for formal main

const int MAXSIZE = 1000;
const int TABLESIZE = 6;

// �۸������
int index[TABLESIZE];
char name[TABLESIZE][MAXSIZE];
int price[TABLESIZE];


// ���ļ��ж�ȡ�۸��
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


// ����
struct City
{
	int index; // �ó��еı��
	char *name;
	int price;
	City(int i, char input[], int price) :index(i), name(input), price(price) {}
};

// �۸��
struct ListNode
{
	City* city;
	ListNode* next;
	ListNode(City* c) :city(c), next(NULL) {}
};

// ·��ͼ
struct ListNodeRoute
{
	ListNode* node;
	ListNodeRoute* next;
	ListNodeRoute(ListNode* h) :node(h), next(NULL) {}
};

// �������γ��м۸��
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


// ��ӡ���γ��м۸��
void printPriceTable(ListNode* head)
{
	char delim[] = { "        " };
	for (ListNode* h = head; h != NULL; h = h->next)
		printf("%d%s%s%s%d\n", h->city->index, delim, h->city->name, delim, h->city->price);
}


// ���ø����ĳ������������μ۸���н��������������������Ľ��ĵ�ַ
// û�ҵ�����NULL
ListNode* searchForCity(char name[],ListNode *head)
{
	for (ListNode* h = head; h != NULL; h = h->next)
	{
		if (strcmp(name, h->city->name)==0)
			return h;
	}
	return NULL;
}


// ��������·��
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

// ��ӡ����·��
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
	printf("�ܼ۸�%d\n", sum);
}


// ������·��ͼ�е�һ������(this city)�滻Ϊ��һ������(that city)
bool replace(ListNodeRoute* &routeHead,ListNode* priceHead, char thisCity[], char thatCity[])
{
	ListNodeRoute* temp = new ListNodeRoute(searchForCity(thatCity, priceHead)); // �ҵ�Ҫ�滻�ĳ���
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
		return false; // û�ҵ�Ҫ�ĵĳ���
}


// ������·���е���������(city one & city two)֮�����һ���µĳ���(new city)
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
		// ����λ����ͷ���ǰ��
		temp->next = routeHead;
		routeHead = temp;
		return true;
	}
	else if (post == NULL)
	{
		// ����λ����β������
		pre->next = temp;
		return true;
	}
	if (strcmp(cityTwo, post->node->city->name) != 0)
		return false;
	temp->next = post;
	pre->next = temp;
	return true;
}


// ɾ������·���е�ĳһ������(city)
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


// ��ѯָ�����еļ۸�
int getPrice(ListNode* priceHead,char city[])
{
	for (ListNode* h = priceHead; h != NULL; h = h->next)
		if (strcmp(h->city->name, city) == 0)
			return h->city->price;
	return -1;
}


// �����۸�
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

// չʾ�˵�
void showMenu()
{
	char delim[] = "******************************************************************************************************************";
	printf("%s\n", delim);
	printf("                       �˵�\n");
	printf("    1.��ӡ���γ��м۸��\n");
	printf("    2.��������·��\n");
	printf("    3.������·���е�ĳ�������滻Ϊ�����ĳ���\n");
	printf("    4.������·���е���������֮�䣬���һ������ǰ������һ�����к��棬�����µĳ���\n");
	printf("    5.ɾ������·���е�ĳ������\n");
	printf("    6.�������γ��м۸����ĳ�����γ��еļ۸�\n");
	printf("    *.�˳�����\n");
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
	int count = 0; // count��ʾ�����˶���������·��
	bool flag = true;
	while (flag)
	{
		char order;
		showMenu();
		printf("���������Ĳ�����");
		scanf_s("%c", &order, 1);
		while (getchar() != '\n'); // ���������
		switch (order)
		{
		case '1':printPriceTable(priceHead); break;
		case '2':
		{
			char cityNames[MAXSIZE];
			printf("��������У��ѿո�ָ���н�����");
			gets_s(cityNames, MAXSIZE);
			routeHead = constructTravelRoute(priceHead, cityNames);
			if (routeHead == NULL)
			{
				printf("����ʧ�ܣ������Ǽ����˲����ڵĳ��������������ڴ����ʧ��\n");
				break;
			}
			else
			{
				printf("�����ɹ���\n");
				printf("������·Ϊ��");
				printTravelRoute(routeHead);
				break;
			}
		}
		case '3':
		{
			char thatCity[MAXSIZE], thisCity[MAXSIZE];
			printf("�����뱻�滻�ĳ��У�");
			scanf_s("%s", thisCity, MAXSIZE);
			while (getchar() != '\n');
			printf("�������滻���У�");
			scanf_s("%s", thatCity, MAXSIZE);
			while (getchar() != '\n');
			if (!replace(routeHead, priceHead, thisCity, thatCity))
			{
				printf("�޸�ʧ�ܣ������Ǽ����˲�������������·�еĳ���\n");
				break;
			}
			printf("������·����Ϊ��");
			printTravelRoute(routeHead);
			break;
		}
		case '4':
		{
			char cityOne[MAXSIZE], cityTwo[MAXSIZE], newCity[MAXSIZE];
			char inputStream[MAXSIZE];
			printf("��������������·�������ĳ��У��������ͷ��ǰ��β������ֻ����һ������\n");
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
			printf("��������Ҫ����ĳ��У�");
			scanf_s("%s", newCity, MAXSIZE);
			while (getchar() != '\n');
			if (!insert(routeHead, priceHead, cityOne, cityTwo, newCity))
			{
				printf("�޸�ʧ�ܣ������Ǽ����˲��������������У����߼���ĳ�������һ������������������·����\n");
				break;
			}
			else
			{
				printf("����·���޸�Ϊ��");
				printTravelRoute(routeHead);
				break;
			}
		}
		case '5':
		{
			printf("��������Ҫɾ���ĳ��У�");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			if (!remove(routeHead, priceHead, city))
			{
				printf("ɾ��ʧ�ܣ������Ǽ����˲�������·���еĳ���\n");
				break;
			}
			else
			{
				printf("����·�߸���Ϊ��");
				printTravelRoute(routeHead);
			}
			break;
		}
		case '6':
		{
			printf("��������Ҫ�����۸�ĳ��У�");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			int price = getPrice(priceHead, city);
			if (price == -1)
			{
				printf("ʧ�ܣ������Ǽ����˲������ڼ۸���еĳ���\n");
				break;
			}
			else
			{
				printf("%sԭ���ļ۸�Ϊ%d�������������ļ۸�", city, price);
				scanf_s("%d", &price);
				while (getchar() != '\n');
				adjustPrice(priceHead, city, price);
				printPriceTable(priceHead);
				printf("������·��");
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
