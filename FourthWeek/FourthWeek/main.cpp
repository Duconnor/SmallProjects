// ����̨Ӧ��

#include "cityList.h"
#include "viproute.h"
#include <stdio.h>
#include <iostream>
using namespace std;

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
	printf("    7.������·��������ļ���\n");
	printf("    8.���ļ��ж�ȡ����·��\n");
	printf("    9.��ʾ��ǰ����·��\n");
	printf("    *.�˳�����\n");
	printf("%s\n", delim);
	printf("\n");
}


int main()
{
	CityList priceTable;
	VIPRoute VRoute;
	Route route;
	File file;
	priceTable.initialize("pricelist.txt");
	char order = 'a';
	int flag = 0; // flagΪ1������VIP��Ϊ0����ʱ��ͨ�û�
	while (order != '*')
	{
		showMenu();
		cout << "���������Ĳ���" << endl;
		cin >> order;
		switch (order)
		{
		case '1':priceTable.printList(); break;
		case '2':
		{
			cout << "����VIP�������������1������������0" << endl;
			cin >> flag;
			while (getchar() != '\n');
			char cityNames[MAXSIZE];
			printf("��������У��Կո�ָ���н�����");
			gets_s(cityNames, MAXSIZE);
			City ** cityRoute = new City*[MAXSIZE];
			int count = 0;
			char *next = NULL, *name = NULL;
			char delim[] = { " " };
			name = strtok_s(cityNames, delim, &next);
			while (name != NULL)
			{
				cityRoute[count] = priceTable.seekForAddress(name);
				count++;
				name = strtok_s(NULL, delim, &next);
			}
			if(flag)
			{
				if (!VRoute.isEmpty())
				{
					int check = -1;
					cout << "ע�⣡��ǰ�Ѵ���һ��VIP·�ߣ��ٴ���������֮ǰ��·�ߣ���ȷ�ϲ�����ȷ��������1��ȡ������������0" << endl;
					cin >> check;
					if (check == 0)
						break;
					else
						VRoute.clear();
				}
				if (!VRoute.createRoute(cityRoute,count))
				{
					printf("����ʧ�ܣ������Ǽ����˲����ڵĳ��������������ڴ����ʧ��\n");
					break;
				}
				else
				{
					printf("�����ɹ���\n");
					printf("������·Ϊ��");
					VRoute.printRoute();
					break;
					}
			}
			else
			{
				if (!route.isEmpty())
				{
					int check = -1;
					cout << "ע�⣡��ǰ�Ѵ���һ����VIP·�ߣ��ٴ���������֮ǰ��·�ߣ���ȷ�ϲ�����ȷ��������1��ȡ������������0" << endl;
					cin >> check;
					if (check == 0)
						break;
					else
						route.clear();
				}
				if (!route.createRoute(cityRoute, count))
				{
					printf("����ʧ�ܣ������Ǽ����˲����ڵĳ��������������ڴ����ʧ��\n");
					break;
				}
				else
				{
					printf("�����ɹ���\n");
					printf("������·Ϊ��");
					route.printRoute();
					break;
				}
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
				City * newCity = priceTable.seekForAddress(thatCity);
				if (flag)
				{
					if (!VRoute.replaceCity(thisCity, newCity))
					{
						printf("�޸�ʧ�ܣ������Ǽ����˲�������������·�еĳ���\n");
						break;
					}
					printf("������·����Ϊ��");
					VRoute.printRoute();
					break;
				}
				else
				{
					if (!route.replaceCity(thisCity, newCity))
					{
						printf("�޸�ʧ�ܣ������Ǽ����˲�������������·�еĳ���\n");
						break;
					}
					printf("������·����Ϊ��");
					route.printRoute();
					break;
				}
			}
		case '4':
		{
			char cityOne[MAXSIZE], cityTwo[MAXSIZE], newCityName[MAXSIZE];
			char inputStream[MAXSIZE];
			printf("��������������·�������ĳ��У��������ͷ��ǰ��β������ֻ����һ������\n");
			while (getchar() != '\n');
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
			scanf_s("%s", newCityName, MAXSIZE);
			while (getchar() != '\n');
			City * newCity = priceTable.seekForAddress(newCityName);
			if (flag)
			{
				if (!VRoute.insertCity(cityOne, cityTwo, newCity))
				{
					printf("�޸�ʧ�ܣ������Ǽ����˲��������������У����߼���ĳ�������һ������������������·����\n");
					break;
				}
				else
				{
					printf("����·���޸�Ϊ��");
					VRoute.printRoute();
					break;
				}
			}
			else
			{
				if (!route.insertCity(cityOne, cityTwo, newCity))
				{
					printf("�޸�ʧ�ܣ������Ǽ����˲��������������У����߼���ĳ�������һ������������������·����\n");
					break;
				}
				else
				{
					printf("����·���޸�Ϊ��");
					route.printRoute();
					break;
				}
			}
		}
		case '5':
		{
			printf("��������Ҫɾ���ĳ��У�");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			if (flag)
			{
				if (!VRoute.removeCity(city))
				{
					printf("ɾ��ʧ�ܣ������Ǽ����˲�������·���еĳ���\n");
					break;
				}
				else
				{
					printf("����·�߸���Ϊ��");
					VRoute.printRoute();
				}
				break;
			}
			else
			{
				if (!route.removeCity(city))
				{
					printf("ɾ��ʧ�ܣ������Ǽ����˲�������·���еĳ���\n");
					break;
				}
				else
				{
					printf("����·�߸���Ϊ��");
					route.printRoute();
				}
				break;
			}
		}
		case '6':
		{
			printf("��������Ҫ�����۸�ĳ��У�");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');

			int price = priceTable.getPrice(city);
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
				priceTable.adjustPrice(city, price);
				priceTable.printList();
				if (flag)
				{
					printf("������·��");
					VRoute.printRoute();
					break;
				}
				else
				{
					printf("������·��");
					route.printRoute();
					break;
				}
			}
		}
		case '7':
		{
			if (flag)
			{
				int number = 0, flagV = 0;
				City ** list = VRoute.getRoute(number, flagV);
				if (file.writeToBinaryFile("route.dat", list, flagV, number))
					cout << "�ɹ�" << endl;
				else
					cout << "ʧ��" << endl;
			}
			else
			{
				int number = 0, flagV = 0;
				City ** list = route.getRoute(number, flagV);
				if (file.writeToBinaryFile("route.dat", list, flagV, number))
					cout << "�ɹ�" << endl;
				else
					cout << "ʧ��" << endl;
			}
			break;
		}
		case '8':
		{
			route.clear();
			VRoute.clear();
			City ** list = nullptr;
			int number = 0;
			flag = file.readBinaryFile("route.dat", list, number);
			City ** cityRoute = priceTable.seekForAddress(list, number);
			if (flag)
			{
				cout << "��ȡ�ɹ�" << endl;
				VRoute.createRoute(cityRoute, number);
				VRoute.printRoute();
			}
			else
			{
				cout << "��ȡ�ɹ�" << endl;
				route.createRoute(cityRoute, number);
				route.printRoute();
			}
			break;
		}
		case '9':
		{
			if (flag)
				VRoute.printRoute();
			else
				route.printRoute();
			break;
		}
		case '*':break;
		default:break;
		}
	}
}