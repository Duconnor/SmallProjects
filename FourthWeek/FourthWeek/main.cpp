// 控制台应用

#include "cityList.h"
#include "viproute.h"
#include <stdio.h>
#include <iostream>
using namespace std;

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
	printf("    7.将旅游路线输出到文件中\n");
	printf("    8.从文件中读取旅游路线\n");
	printf("    9.显示当前旅游路线\n");
	printf("    *.退出程序\n");
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
	int flag = 0; // flag为1代表是VIP，为0代表时普通用户
	while (order != '*')
	{
		showMenu();
		cout << "请输入您的操作" << endl;
		cin >> order;
		switch (order)
		{
		case '1':priceTable.printList(); break;
		case '2':
		{
			cout << "您是VIP吗，如果是请输入1，不是请输入0" << endl;
			cin >> flag;
			while (getchar() != '\n');
			char cityNames[MAXSIZE];
			printf("请输入城市，以空格分割，换行结束：");
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
					cout << "注意！当前已存在一条VIP路线，再创建将覆盖之前的路线，请确认操作，确认请输入1，取消操作请输入0" << endl;
					cin >> check;
					if (check == 0)
						break;
					else
						VRoute.clear();
				}
				if (!VRoute.createRoute(cityRoute,count))
				{
					printf("创建失败，可能是键入了不存在的城市名，或者是内存分配失败\n");
					break;
				}
				else
				{
					printf("创建成功！\n");
					printf("旅游线路为：");
					VRoute.printRoute();
					break;
					}
			}
			else
			{
				if (!route.isEmpty())
				{
					int check = -1;
					cout << "注意！当前已存在一条非VIP路线，再创建将覆盖之前的路线，请确认操作，确认请输入1，取消操作请输入0" << endl;
					cin >> check;
					if (check == 0)
						break;
					else
						route.clear();
				}
				if (!route.createRoute(cityRoute, count))
				{
					printf("创建失败，可能是键入了不存在的城市名，或者是内存分配失败\n");
					break;
				}
				else
				{
					printf("创建成功！\n");
					printf("旅游线路为：");
					route.printRoute();
					break;
				}
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
				City * newCity = priceTable.seekForAddress(thatCity);
				if (flag)
				{
					if (!VRoute.replaceCity(thisCity, newCity))
					{
						printf("修改失败，可能是键入了不存在于旅游线路中的城市\n");
						break;
					}
					printf("旅游线路更改为：");
					VRoute.printRoute();
					break;
				}
				else
				{
					if (!route.replaceCity(thisCity, newCity))
					{
						printf("修改失败，可能是键入了不存在于旅游线路中的城市\n");
						break;
					}
					printf("旅游线路更改为：");
					route.printRoute();
					break;
				}
			}
		case '4':
		{
			char cityOne[MAXSIZE], cityTwo[MAXSIZE], newCityName[MAXSIZE];
			char inputStream[MAXSIZE];
			printf("请输入两个在线路中连续的城市，如果插在头部前或尾部后，请只输入一个城市\n");
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
			printf("请输入需要插入的城市：");
			scanf_s("%s", newCityName, MAXSIZE);
			while (getchar() != '\n');
			City * newCity = priceTable.seekForAddress(newCityName);
			if (flag)
			{
				if (!VRoute.insertCity(cityOne, cityTwo, newCity))
				{
					printf("修改失败，可能是键入了不连续的两个城市，或者键入的城市中有一个或多个不存在于旅游路线中\n");
					break;
				}
				else
				{
					printf("旅游路线修改为：");
					VRoute.printRoute();
					break;
				}
			}
			else
			{
				if (!route.insertCity(cityOne, cityTwo, newCity))
				{
					printf("修改失败，可能是键入了不连续的两个城市，或者键入的城市中有一个或多个不存在于旅游路线中\n");
					break;
				}
				else
				{
					printf("旅游路线修改为：");
					route.printRoute();
					break;
				}
			}
		}
		case '5':
		{
			printf("请输入需要删除的城市：");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');
			if (flag)
			{
				if (!VRoute.removeCity(city))
				{
					printf("删除失败，可能是键入了不存在于路线中的城市\n");
					break;
				}
				else
				{
					printf("旅游路线更改为：");
					VRoute.printRoute();
				}
				break;
			}
			else
			{
				if (!route.removeCity(city))
				{
					printf("删除失败，可能是键入了不存在于路线中的城市\n");
					break;
				}
				else
				{
					printf("旅游路线更改为：");
					route.printRoute();
				}
				break;
			}
		}
		case '6':
		{
			printf("请输入需要调整价格的城市：");
			char city[MAXSIZE];
			scanf_s("%s", city, MAXSIZE);
			while (getchar() != '\n');

			int price = priceTable.getPrice(city);
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
				priceTable.adjustPrice(city, price);
				priceTable.printList();
				if (flag)
				{
					printf("旅游线路：");
					VRoute.printRoute();
					break;
				}
				else
				{
					printf("旅游线路：");
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
					cout << "成功" << endl;
				else
					cout << "失败" << endl;
			}
			else
			{
				int number = 0, flagV = 0;
				City ** list = route.getRoute(number, flagV);
				if (file.writeToBinaryFile("route.dat", list, flagV, number))
					cout << "成功" << endl;
				else
					cout << "失败" << endl;
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
				cout << "读取成功" << endl;
				VRoute.createRoute(cityRoute, number);
				VRoute.printRoute();
			}
			else
			{
				cout << "读取成功" << endl;
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