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
			if (Main_Menu_Ser_Register())
				User_UI_First();
			break;
		case '2':
			if (Main_Menu_Ser_Login())
				User_UI_First();

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

void User_UI_First()
{
	char choice;
	UserBase self = From_Json_UserBase(client::Recv()); // 用一个_Ser兼顾收发,把返回用户信息事件和登录注册分开
														// 没刷新
	do
	{
		system("clear");
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
			Friend_UI_First(self);
			break;
		case '2':
			Group_UI_First(self);
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

void Friend_UI_First(UserTotal self)
{
	char choice;
	do
	{
		system("clear");
		cout << "好友界面\n";
		Friend_Ser(self.ID);
		Friend_UI();
		printf("输入(0-2):");
		cin >> choice;
		if (choice == '0')
		{
			// To_User_Ser(self.ID);

			return;
		}
		if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Add_Frd_Ser(self.ID);
			break;
		case '2':
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Group_UI_First(UserTotal self)
{
}

void Friend_UI()
{
	printf("1.加好友\n2.删好友\n3.选择好友聊天\n4.搜索好友\n0.退出\n");
}