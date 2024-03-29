#ifndef SERVICE_CIL
#define SERVICE_CIL

#include "../user.hpp"
#include "../Message.hpp"
#include <list>

int Get_Int();
string Scan();
string ScanPass();
void Pause();

int Main_Menu_Ser_Register();
int Main_Menu_Ser_Login();

UserBase Get_User_Ser(int ID);
void User_Ser_Exit(int ID);
void Friend_Ser(int ID);
void Add_Frd_Ser(int ID);
void Del_Frd_Ser(int ID);
void Send_Msg_Ser(UserBase usr);
void Sendfile_Ser(int ID);
list<File> Recvfile_List_Ser(int ID);
void Recvfile_Ser(list<File>);
void Block_Frd_Ser(int ID);
void Search_Frd_Ser(int ID);
set<Message, MessageComparator> Get_Frd_ManageList_Ser(int ID);

void Group_Ser(int ID);
void New_Grp_Ser(int ID);
int Choose_Grp_Ser(int ID);
void Add_Grp_Ser(int ID);
void In_Grp_Ser(int GID);
void Add_Manager_Ser(int GID);
void Del_Manager_Ser(int GID);
int Check_Authority_Ser(int GID);
set<Message, MessageComparator> Get_Grp_ManageList_Ser(int GID);
void Manage_Apply_Ser(int ID, set<Message, MessageComparator> manage);
void Del_Member_Ser(int GID);
bool Quit_Ser(int GID);
bool Dissolve_Ser(int GID);
void Send_Msg_Grp_Ser(int GID);

#endif
