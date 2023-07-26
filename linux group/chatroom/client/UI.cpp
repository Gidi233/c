#include <iostream>
#include "client.hpp"
#include "service.hpp"
#include "../Serialization.hpp"
#include "../user.hpp"
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
		cout << choice << endl;
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
	do
	{
		system("clear");
		cout << "个人界面\n";
		UserTotal self = From_Json_User(client::Recv());
		self.toString();
		User_UI();
		printf("输入(0-2):（个人界面）");
		cin >> choice;
		cout << choice << endl;
		if (choice == '0')
		{
			User_Ser_Exit(self.account);

			return;
		}
		if (choice != '1' && choice != '2')
		{
			continue;
		}

		switch (choice)
		{
		case '1':
			Friend_Ser();
			break;
		case '2':
			Group_Ser();
			break;
		default:
			cout << "啊？" << endl;
			break;
		}
	} while (choice != '0');
}

void User_UI()
{
	printf("1.好友\n2.群组\n0.退出\n");
}