#include <iostream>
#include "client.hpp"
#include "service.hpp"
#include "../Serialization.hpp"
#include "UI.hpp"

using namespace std;

void Main_UI_First()
{
	client cil;
	bool flag;
	char choice;
	int ID;
	do
	{
		system("clear");
		Main_Menu();
		printf("输入(0-2):(初始界面)");
		cin >> choice;
		system("clear");
		if (choice == '0')
		{

			printf("BYE HAVE A GREAT TIME\n");
			return;
		}
		if (choice != '1' && choice != '2')
		{
			continue;
		}

		switch (choice)
		{

		case '1':
			if ((ID = Main_Menu_Ser_Register()))
				User_UI_First(ID);
			break;
		case '2':
			if ((ID = Main_Menu_Ser_Login()))
				User_UI_First(ID);

			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Main_Menu()
{
	printf("1.注册\n2.登录\n0.退出\n");
}

void User_UI_First(int ID) // 都改成引用
{
	char choice;
	UserBase self;
	do
	{
		system("clear");
		self = Get_User_Ser(ID);
		cout << "个人界面\n";
		self.toString();
		User_UI();
		cout << "输入(0-2):（个人界面）";
		cin >> choice;
		if (choice == '0')
		{
			User_Ser_Exit(self.ID);

			return;
		}
		if (choice != '1' && choice != '2')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Friend_UI_First(self.ID);
			break;
		case '2':
			Group_UI_First(self.ID);
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void User_UI()
{
	printf("1.好友\n2.群组\n3.处理通知\n9.注销\n0.退出\n");
}

void Friend_UI_First(int ID)
{
	char choice;
	do
	{
		system("clear");
		cout << "好友界面\n";
		Friend_Ser(ID);
		Friend_UI();
		printf("输入(0-2):");
		cin >> choice;
		if (choice == '0')
		{
			return;
		}
		if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Add_Frd_Ser(ID);
			break;
		case '2':
			Del_Frd_Ser(ID);
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Friend_UI()
{
	printf("1.加好友\n2.删好友\n3.选择好友聊天\n4.搜索好友\n0.退出\n");
}
void Group_UI_First(int ID)
{
}
