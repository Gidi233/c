#include <iostream>
#include <list>
#include "../Message.hpp"
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
	list<Message> Offline_Msg = From_Json_MsgList(To_Notice(client::Recv())); // 还是得构造list
	bool set = 1;
	client::ID = ID;
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

		if (set)
		{
			for (auto &l : Offline_Msg)
			{
				l.toString();
			}
			set = 0;
		}

		cin >> choice;
		if (choice == '0')
		{
			User_Ser_Exit(self.ID);

			return;
		}
		if (choice != '1' && choice != '2' && choice != '3')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Friend_UI_First(self);
			break;
		case '2':
			Group_UI_First(self.ID);
			break;
		case '3':
			Manage_Apply_UI(self.ID);
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

void Manage_Apply_UI(int ID)
{
	char choice;
	int num;
	list<Message> manage;
	while (1)
	{
		system("clear");
		manage = Get_ManageList_Ser(ID);
		if (manage.empty())
		{
			cout << "当前无任何请求\n";
			sleep(1);
			return;
		}
		for (auto &m : manage)
		{
			m.toString();
		}
		cout << "1.逐个处理\n0.返回\n";
		cin >> choice;
		if (choice == '0')
		{
			return;
		}
		Manage_Apply_Ser(ID, manage);
	}
}

void Friend_UI_First(UserBase usr)
{
	char choice;
	do
	{
		system("clear");
		cout << "好友界面\n";
		Friend_Ser(usr.ID);
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
			Add_Frd_Ser(usr.ID);
			break;
		case '2':
			Del_Frd_Ser(usr.ID);
			break;
		case '3':
			Send_Msg_Ser(usr);
			break;
		case '4':
			Block_Frd_Ser(usr.ID);
			break;
		case '5':
			Search_Frd_Ser(usr.ID);
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Friend_UI()
{
	printf("1.加好友\n2.删好友\n3.选择好友聊天(输入\\q退出)\n4.改变屏蔽状态\n5.搜索账户对应ID\n0.退出\n");
}
void Group_UI_First(int ID)
{
}
