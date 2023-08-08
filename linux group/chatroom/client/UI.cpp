#include <iostream>
#include <list>
#include <set>
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
		client::account = self.account;
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
	printf("1.好友\n2.群组\n9.注销\n0.退出\n");
}

void Manage_Frd_Apply_UI(int ID) // 移到friend里
{
	char choice;
	int num;
	set<Message, MessageComparator> manage;
	while (1)
	{
		system("clear");
		manage = Get_Frd_ManageList_Ser(ID);
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
		if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6')
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
		case '6':
			Manage_Frd_Apply_UI(usr.ID);
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Friend_UI()
{
	printf("1.加好友\n2.删好友\n3.选择好友聊天(输入\\q退出)\n4.改变屏蔽状态\n5.搜索账户对应ID\n6.处理好友请求\n0.退出\n");
}
void Group_UI_First(int ID)
{
	int GID;
	char choice;
	do
	{
		system("clear");
		cout << "群组界面\n";
		Group_Ser(ID);
		Group_UI();
		printf("输入(0-2):");
		cin >> choice;
		if (choice == '0')
		{
			return;
		}
		if (choice != '1' && choice != '2' && choice != '3')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			New_Grp_Ser(ID);
			break;
		case '2':
			if ((GID = Choose_Grp_Ser(ID)))
				In_Grp_UI_First(GID);
			break;
		case '3':
			Add_Grp_Ser(ID);
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void Group_UI()
{
	printf("1.新建群聊\n2.选择群聊\n3.申请加入群聊\n0.退出\n");
}

void In_Grp_UI_First(int GID)
{
	char choice;
	do
	{
		system("clear");
		cout << "进入群组界面\n";
		In_Grp_Ser(GID);
		In_Grp_UI();
		printf("输入(0-7):");
		cin >> choice;
		if (choice == '0')
		{
			return;
		}
		if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Send_Msg_Grp_Ser(GID);
			break;
		// case '2':
		// 	Add_Manager_Ser(GID);
		// 	break;
		// case '3':
		// 	Del_Manager_Ser(GID);
		// 	break;
		case '5':
			Manage_Grp_Apply_UI(GID);
			break;
		case '6':
			if (Dissolve_Ser(GID))
				return;
			break;
		case '7':
			if (Quit_Ser(GID))
				return;
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void In_Grp_UI()
{
	printf("1.进入唠嗑\n2.添加管理员\n3.删除管理员\n4.移除用户\n5.处理信息\n6.解散群聊\n7.退出该群\n0.返回\n");
}

void Manage_Grp_Apply_UI(int GID) // 移到friend里
{
	system("clear");
	if (!Check_Authority_Ser(GID))
	{
		cout << "你什么身份！" << endl;
		sleep(1);
		return;
	}
	char choice;
	int num;
	set<Message, MessageComparator> manage;
	while (1)
	{
		system("clear");
		manage = Get_Grp_ManageList_Ser(GID);
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
		Manage_Apply_Ser(GID, manage);
	}
}
