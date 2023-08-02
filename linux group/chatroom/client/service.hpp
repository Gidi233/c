#ifndef SERVICE_CIL
#define SERVICE_CIL

#include "../user.hpp"

int Main_Menu_Ser_Register();
int Main_Menu_Ser_Login();

void User_Ser_Exit(int ID);
void Friend_Ser(int ID);
void Add_Frd_Ser(int ID);
void Del_Frd_Ser(int ID);
void Send_Msg_Ser(UserBase usr);
void Search_Frd_Ser(int ID);

void Group_Ser(int ID);
UserBase Get_User_Ser(int ID);

#endif
