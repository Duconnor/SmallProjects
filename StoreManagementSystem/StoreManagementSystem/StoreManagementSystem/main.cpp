// for main func

#include "administration.h"
#include "purchase.h"
#include "admin.h"

void showLogMenu()
{
	char delim[] = { "===============================================" };
	std::cout << delim << std::endl;
	char delim2[] = { "	" };
	std::cout << "1.�û���¼" << delim2 << "2.�û�ע��" << delim2 << "3.����Ա��¼" << std::endl;
	std::cout << delim << std::endl;
}

void showPurchaseMenu()
{
	// �ͻ�����Ĳ˵�
	char delim[] = { "================================================\
======================================================================" };
	char delim2[] = { "	" };
	std::cout << delim << std::endl;
	std::cout << "1.ע����¼" << delim2 << "2.�鿴��Ʒ" << delim2 << "3.��Ʒ����" << delim2 << "4.������Ʒ�����ﳵ" << delim2
		<< "5.ɾ�����ﳵ��Ʒ" << delim2 << "6.�鿴���ﳵ" << delim2 << "7.����" << std::endl;
	std::cout << delim << std::endl;
}

void showAdministrationMenu()
{
	char delim[] = { "================================================\
============================================================" };
	char delim2[] = { "	" };
	std::cout << delim << std::endl;
	std::cout << "1.ע����¼" << delim2 << "2.��ѯ��Ʒ" << delim2 << "3.������Ʒ" << delim2 << "4.ɾ����Ʒ" << delim2 << "5.�޸���Ʒ��Ϣ" << delim2
		<< "6.�ۻ��嵥" << delim2 << "7.���ۻ����嵥" << std::endl;
	std::cout << delim << std::endl;
}

void applicationOn()
{
	while (true)
	{
		char fileNameGoods[] = { "���.txt" };
		char fileNameSoldGoods[] = { "�����嵥.txt" };
		User * user = nullptr;
		Admin * admin = nullptr;
		showLogMenu();
		std::cout << "���������";
		int order = -1;
		std::cin >> order;
		bool flagUser = false; // ����¼����ע������Ƿ����
		bool flagAdmin = false;
		switch (order)
		{
		case 1:
		{
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "�����û�����";
			std::cin >> name;
			std::cout << "�������룺";
			std::cin >> password;
			user = new User(name, password);
			if (user->logIn("�û�.txt"))
			{
				std::cout << "********" << std::endl;
				std::cout << "��¼�ɹ���" << std::endl;
				std::cout << "********" << std::endl;
				flagUser = true;
			}
			else
			{
				std::cout << "****************" << std::endl;
				std::cout << "�û������������" << std::endl;
				std::cout << "****************" << std::endl;
			}
			break;
		}
		case 2:
		{
			// ע��
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "�����û�����";
			std::cin >> name;
			std::cout << "�������룺";
			std::cin >> password;
			user = new User(name, password);
			if (user->signIn("�û�.txt"))
			{
				std::cout << "****************" << std::endl;
				std::cout << "ע��ɹ�����¼�ɹ���" << std::endl;
				std::cout << "****************" << std::endl;
				flagUser = true;
			}
			else
			{
				std::cout << "********" << std::endl;
				std::cout << "ʧ�ܣ�" << std::endl;
				std::cout << "********" << std::endl;
			}
			break;
		}
		case 3:
		{
			char name[MAXSIZE], password[MAXSIZE];
			std::cout << "�������ԱID��";
			std::cin >> name;
			std::cout << "�������Ա���룺";
			std::cin >> password;
			admin = new Admin(name, password);
			if (admin->logIn(""))
			{
				std::cout << "********" << std::endl;
				std::cout << "��¼�ɹ���" << std::endl;
				std::cout << "********" << std::endl;
				flagAdmin = true;
			}
			else
			{
				std::cout << "****************" << std::endl;
				std::cout << "�û������������" << std::endl;
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
				std::cout << "���������";
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
				std::cout << "���������";
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