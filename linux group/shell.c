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
        
        if(command_amout>1){//父
        for(int i=0;i<command_amout;i++){//先fork出所有的子进程
            if(i!=command_amout-1) pipe(fd[i]);
            shuru(command[i]);
            //在父进程输入 获得文件句柄继承给子进程（未）
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
            else{//子//子进程中不用检查（把stdin，stdout重定向到标准输入输出）不影响父进程。
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
            exit(0);  //祖父    
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
                else chdir(args[1]);//绝对路径(~)调用失败
            }

        }
        jiancha();
             
    }
    if(set_exit==1) {
        for(int i=0;i<20;i++) free(args[i]);
    }
}

void jiancha(){//管道去掉检查退出
    
    if(fp0_set) close(fp0),dup2(fp0_yuan,fp0);
    if(fp1_set) close(fp1),dup2(fp1_yuan,fp1);
}

void execute(char *args[]){
    int pid=fork();
    if(pid){
        if(houtai_set) houtai_set=0,printf("[1] %d\n",pid);
        wait(NULL);//后台的话应该不wait？？

    }
    else{
        execvp(args[0],args);//进程被新进程覆盖，之后的指令不运行
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
    do{//对参数的第一个字符判断if(args[i][0]=='~');args[i]=strcat("/home/用户名",args[i][1]);
        
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
            if(strcmp(argbuf,">")==0){//strtok 区分> >> ？？//指令不带空格
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
    if(chongin_set){//在读取完所有命令后再重定向到标准输入
        fp0_yuan=dup(STDIN_FILENO);
        fp0=fileno(freopen(chongin,"r",stdin));
        fp0_set=1;
    }
    return 0;
}


// 要在GDB中调试多线程程序，您需要使用以下命令：

//     set follow-fork-mode child：将GDB的跟踪模式设置为子进程（即新创建的线程）。
//     set detach-on-fork off：使GDB保留对主线程的控制。
//     break <function_name>：在目标函数上设置断点。
//     thread apply all bt：显示所有线程的回溯信息。
//     thread <thread_id>：切换到指定线程。
//     info threads：列出所有线程及其状态。
//     next, step, continue：执行代码，继续或单步执行线程。

// 使用这些命令，您可以轻松地在GDB中调试多线程程序，查找并修复错误。