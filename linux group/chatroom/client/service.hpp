#ifndef SERVICE_CIL
#define SERVICE_CIL

#include "../user.hpp"
#include "../Message.hpp"
#include <list>

int Main_Menu_Ser_Register();
int Main_Menu_Ser_Login();

list<Message> Get_ManageList_Ser(int ID);
void Manage_Apply_Ser(int ID, list<Message> manage);

UserBase Get_User_Ser(int ID);
void User_Ser_Exit(int ID);
void Friend_Ser(int ID);
void Add_Frd_Ser(int ID);
void Del_Frd_Ser(int ID);
void Send_Msg_Ser(UserBase usr);
void Block_Frd_Ser(int ID);
void Search_Frd_Ser(int ID);

void Group_Ser(int ID);
void New_Grp_Ser(int ID);

#endif
