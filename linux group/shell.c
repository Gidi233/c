#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdlib.h>
#include<signal.h>
void execute(char *args[]);
int shuru(char *command);
void jiancha();

int set_exit=0,argnum,houtai_set;
int fp0,fp0_set,fp0_yuan,fp1,fp1_yuan,fp1_set,fp_hou,cd_set;
char *args[20];


int main(){
    char sr[100];
    char dir_path_yuan[256];
    char dir_path[256];
    
    signal(SIGINT, SIG_IGN);
    int pid=0,shuru_set;
    int command_amout=0;
    char *command[20];
    int fd[10][2];
    getcwd(dir_path,256);
    strcpy(dir_path_yuan,dir_path);
    while(1){
        shuru_set=0;
        if(cd_set) {
            cd_set=0;
            strcpy(dir_path_yuan,dir_path);
        }
        getcwd(dir_path,256);
        printf("\033[32mljc-shell:\033[31m%s$ \033[0m",dir_path);
        fflush(stdout);
        command_amout=0;
        gets(sr);
        command[command_amout++]=strtok(sr,"|");
        for(;;command_amout++){
            command[command_amout]=strtok(NULL,"|");
            if(command[command_amout]==NULL) break;
        }
        
        if(command_amout>1){//��
        for(int i=0;i<command_amout;i++){//��fork�����е��ӽ���
            if(i!=command_amout-1) pipe(fd[i]);
            shuru(command[i]);
            //�ڸ��������� ����ļ�����̳и��ӽ��̣�δ��
            pid=fork();
            if(pid){
                if(i>0){
                    close(fd[i-1][0]);
                    close(fd[i-1][1]);
                } 
                if(i==command_amout-1){
                    for(int j=0;j<command_amout;j++) wait(NULL);
                }
            }
            else{//��//�ӽ����в��ü�飨��stdin��stdout�ض��򵽱�׼�����������Ӱ�츸���̡�
             if(i==0){
                close(fd[i][0]);
                dup2(fd[i][1],STDOUT_FILENO);

                execute(args);
            }
            else if(i==command_amout-1){
                close(fd[i-1][1]);
                dup2(fd[i-1][0],STDIN_FILENO);

                execute(args);
            }else{
                close(fd[i-1][1]);
                close(fd[i][0]);
                dup2(fd[i-1][0],STDIN_FILENO);
                dup2(fd[i][1],STDOUT_FILENO);    
                
                execute(args);
            }    
            wait(NULL);
            exit(0);  //�游    
            }
        }
        }
        else{
            if(shuru_set=shuru(command[0])) continue;
            if(set_exit==1) break;   
            if(strcmp(args[0],"cd")!=0) 
            execute(args);
            else{
                cd_set=1;
                if(strcmp(args[1],"-")==0) chdir(dir_path_yuan);
                else chdir(args[1]);//����·��(~)����ʧ��
            }

        }
        jiancha();
             
    }
    if(set_exit==1) {
        for(int i=0;i<20;i++) free(args[i]);
    }
}

void jiancha(){//�ܵ�ȥ������˳�
    
    if(fp0_set) close(fp0),dup2(fp0_yuan,fp0);
    if(fp1_set) close(fp1),dup2(fp1_yuan,fp1);
}

void execute(char *args[]){
    int pid=fork();
    if(pid){
        if(houtai_set) houtai_set=0,printf("[1] %d\n",pid);
        wait(NULL);//��̨�Ļ�Ӧ�ò�wait����

    }
    else{
        execvp(args[0],args);//���̱��½��̸��ǣ�֮���ָ�����
        perror("");
        exit(0);
    }
}

int shuru(char *command){
    char ch,*argbuf,*chongin;
    int chongin_set=0;
    argnum=0;
    argbuf=strtok(command," ");
    if(argbuf==NULL){
        return 1;
    }
    do{//�Բ����ĵ�һ���ַ��ж�if(args[i][0]=='~');args[i]=strcat("/home/�û���",args[i][1]);
        
        if(argnum==0&&strcmp(argbuf,"exit")==0){
        set_exit=1;
        }   
        if(strcmp(argbuf,"&")==0&&fp1_set==0){
            houtai_set=1;
            fp1_yuan=dup(STDOUT_FILENO);
            fp_hou=open("/dev/null",O_RDWR);
            fp1=dup2(fp_hou,STDOUT_FILENO);
            fp1_set=1;
            break;
        }
        if(strcmp(argbuf,"<")==0||strcmp(argbuf,">")==0||strcmp(argbuf,">>")==0) {
            if(strcmp(argbuf,"<")==0){
                chongin=strtok(NULL," ");
                chongin_set=1;
            }
            if(strcmp(argbuf,">")==0){//strtok ����> >> ����//ָ����ո�
                argbuf=strtok(NULL," ");
                fp1_yuan=dup(STDOUT_FILENO);
                fp1=fileno(freopen(argbuf,"w",stdout));
                fp1_set=1;
            }
            if(strcmp(argbuf,">>")==0){
                argbuf=strtok(NULL," ");
                fp1_yuan=dup(STDOUT_FILENO);
                fp1=fileno(freopen(argbuf,"a",stdout));
                fp1_set=1;
            }
        }
        else{
        args[argnum]=realloc(args[argnum],strlen(argbuf)+1);
        strcpy(args[argnum++],argbuf);            
        }
        argbuf=strtok(NULL," ");
        if(argbuf==NULL) break;
    }while(1);
    args[argnum]=NULL;
    if(chongin_set){//�ڶ�ȡ��������������ض��򵽱�׼����
        fp0_yuan=dup(STDIN_FILENO);
        fp0=fileno(freopen(chongin,"r",stdin));
        fp0_set=1;
    }
    return 0;
}


// Ҫ��GDB�е��Զ��̳߳�������Ҫʹ���������

//     set follow-fork-mode child����GDB�ĸ���ģʽ����Ϊ�ӽ��̣����´������̣߳���
//     set detach-on-fork off��ʹGDB���������̵߳Ŀ��ơ�
//     break <function_name>����Ŀ�꺯�������öϵ㡣
//     thread apply all bt����ʾ�����̵߳Ļ�����Ϣ��
//     thread <thread_id>���л���ָ���̡߳�
//     info threads���г������̼߳���״̬��
//     next, step, continue��ִ�д��룬�����򵥲�ִ���̡߳�

// ʹ����Щ������������ɵ���GDB�е��Զ��̳߳��򣬲��Ҳ��޸�����