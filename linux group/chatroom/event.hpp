#ifndef EVENT
#define EVENT

enum Event
{
    Register,
    Login,
    Exit,
    User,
    Get_Frd_ManageList,
    Frd_List,
    Send_Add_Frd,
    Recv_Add_Frd,
    Del_Frd,
    Block_Frd,
    Search_Frd,
    Able_To_Send_Frd,
    Get_frdChat,
    Sendmsg_Tofrd,
    Grp_List,
    New_Grp,
    Choose_Grp,
    Check_Authority,
    Grp_Member_List,
    Add_Manager,
    Del_Manager,
    Send_Add_Grp,
    Recv_Add_Grp,
    Get_Grp_ManageList,
    Del_Member,
    Quit_Grp,
    Get_grpChat,
    Sendmsg_Togrp,
    Dissolve_Grp,
    Sendfile,
    Recvfile,
    File_List,
};

#endif