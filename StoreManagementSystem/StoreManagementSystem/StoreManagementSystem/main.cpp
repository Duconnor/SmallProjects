// for main func

#include "administration.h"
#include "purchase.h"
#include "admin.h"

void showLogMenu()
{
	char delim[] = { "===============================================" };
	std::cout << delim << std::endl;
	char delim2[] = { "	" };
	std::cout << "1.用户登录" << delim2 << "2.用户注册" << delim2 << "3.管理员登录" << std::endl;
	std::cout << delim << std::endl;
}

void showPurchaseMenu()
{
	// 客户界面的菜单
	char delim[] = { "================================================\
======================================================================" };
	char delim2[] = { "	" };
	std::cout << delim << std::endl;
	std::cout << "1.注销登录" << delim2 << "2.查看商品" << delim2 << "3.商品搜索" << delim2 << "4.添加商品至购物车" << delim2
		<< "5.删除购物车商品" << delim2 << "6.查看购物车" << delim2 << "7.结账" << std::endl;
	std::cout << delim << std::endl;
}

void showAdministrationMenu()
{
	char delim[] = { "================================================\
============================================================" };
	char delim2[] = { "	" };
	std::cout << delim << std::endl;
	std::cout << "1.注销登录" << delim2 << "2.查询商品" << delim2 << "3.增加商品" << delim2 << "4.删除商品" << delim2 << "5.修改商品信息" << delim2
		<< "6.售货清单" << delim2 << "7.在售货物清单" << std::endl;
	std::cout << delim << std::endl;
}

void applicationOn()
{
	while (true)
	{
		char fileNameGoods[] = { "库存.txt" };
		char fileNameSoldGoods[] = { "已售清单.txt" };
		User * user = nullptr;
		Admin * admin = nullptr;
		showLogMenu();
		std::cout << "输入操作：";
		int order = -1;
		std::cin >> order;
		bool flagUser = false; // 检查登录或者注册操作是否完成
		bool flagAdmin = false;
		switch (order)
		{
		case 1:
		{
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "输入用户名：";
			std::cin >> name;
			std::cout << "输入密码：";
			std::cin >> password;
			user = new User(name, password);
			if (user->logIn("用户.txt"))
			{
				std::cout << "********" << std::endl;
				std::cout << "登录成功！" << std::endl;
				std::cout << "********" << std::endl;
				flagUser = true;
			}
			else
			{
				std::cout << "****************" << std::endl;
				std::cout << "用户名或密码错误！" << std::endl;
				std::cout << "****************" << std::endl;
			}
			break;
		}
		case 2:
		{
			// 注册
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "输入用户名：";
			std::cin >> name;
			std::cout << "输入密码：";
			std::cin >> password;
			user = new User(name, password);
			if (user->signIn("用户.txt"))
			{
				std::cout << "****************" << std::endl;
				std::cout << "注册成功！登录成功！" << std::endl;
				std::cout << "****************" << std::endl;
				flagUser = true;
			}
			else
			{
				std::cout << "********" << std::endl;
				std::cout << "失败！" << std::endl;
				std::cout << "********" << std::endl;
			}
			break;
		}
		case 3:
		{
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "输入管理员ID：";
			std::cin >> name;
			std::cout << "输入管理员密码：";
			std::cin >> password;
			admin = new Admin(name, password);
			if (admin->logIn(""))
			{
				std::cout << "********" << std::endl;
				std::cout << "登录成功！" << std::endl;
				std::cout << "********" << std::endl;
				flagAdmin = true;
			}
			else
			{
				std::cout << "****************" << std::endl;
				std::cout << "用户名或密码错误！" << std::endl;
				std::cout << "****************" << std::endl;
			}
			break;
		}
		default:break;
		}
		// switch end
		if (!flagUser && !flagAdmin)
			continue;
		if (flagUser)
		{
			char fileNameCart[MAXSIZE];
			strcpy_s(fileNameCart, strlen(user->getUserName()) + 1, user->getUserName());
			strcat_s(fileNameCart, sizeof(fileNameCart), ".txt");
			Purchase userInterface(fileNameGoods, fileNameSoldGoods, fileNameCart, user);
			order = -1;
			while (order != 1)
			{
				showPurchaseMenu();
				std::cout << "输入操作：";
				std::cin >> order;
				switch (order)
				{
				case 1:userInterface.logOut(); break;
				case 2:userInterface.showGoodsList(); break;
				case 3:userInterface.searchForGoods(); break;
				case 4:userInterface.addToShoppingCart(); break;
				case 5:userInterface.deleteGoodsInShoppingCart(); break;
				case 6:userInterface.showShoppingCart(); break;
				case 7:userInterface.pay(); break;
				default:break;
				}
			}
			continue;
		}
		if (flagAdmin)
		{
			Administration adminInterface(fileNameGoods, fileNameSoldGoods);
			order = -1;
			while (order != 1)
			{
				showAdministrationMenu();
				std::cout << "输入操作：";
				std::cin >> order;
				switch (order)
				{
				case 1:adminInterface.logOut(); break;
				case 2:adminInterface.searchForGoods(); break;
				case 3:adminInterface.addNewGoods(); break;
				case 4:adminInterface.deleteGoods(); break;
				case 5:adminInterface.modifyGoodsInformation(); break;
				case 6:adminInterface.showSoldList(); break;
				case 7:adminInterface.showGoodList(); break;
				default:break;
				}
			}
			continue;
		}
	}
}

int main()
{
	applicationOn();
	system("pause");
}