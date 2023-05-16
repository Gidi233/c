#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

typedef struct t{
    time_t time;
    struct dirent * Ent;
}file;

int a,l,t,r,i,s,R;

int cmp(const void *a,const void *b);
void ls_t(DIR *dir);
void ls_R(struct dirent *ent);
int ls_s(struct dirent *ent);
void ls_l(struct dirent *ent);
//void ls_read(DIR *dir);
void ls_open(char *dir_path);

int cmp(const void *a,const void *b){
    file *aa=(file *)a;
    file *bb=(file *)b;
    return (int)(bb->time-aa->time);
}

//时间顺序
void ls_t(DIR *dir){
    int mount=0;
    struct dirent *ent; 
    while ((ent = readdir(dir)) != NULL) {
        mount++;
        }
        file *fil=(file *)malloc((mount)*sizeof(file));
        mount=0;
        rewinddir(dir);
        int t1=0;
        struct stat statbuf;
        while((ent = readdir(dir)) != NULL){
            struct dirent *ent_copy = (struct dirent*)malloc(sizeof(struct dirent));
            memcpy(ent_copy, ent, sizeof(struct dirent));
            stat(ent->d_name,&statbuf);
            fil[t1].time=statbuf.st_mtime;
            fil[t1].Ent=ent_copy;
            t1++;
        }
        if(t==1)qsort(fil,t1,sizeof(file),cmp);//cmp()返回值要强制转化为int
        closedir(dir);
        int blocks=0;
        if(r==0){
           for(int i1=0;i1<t1;i1++){
            
        if(a==0){
            if(strcmp(fil[i1].Ent->d_name,".")==0||strcmp(fil[i1].Ent->d_name,"..")==0||fil[i1].Ent->d_name[0]=='.')
            continue;
        }
        if(i==1){//没有选项-i但会在循环到ls.c时//在循环时i会不规律递增//循环变量名和-i选项重叠
            printf("%lu  ",fil[i1].Ent->d_ino);
        }
        if(s==1){
            blocks+=ls_s(fil[i1].Ent);
        }
        if(l==1){
            ls_l(fil[i1].Ent);
        }
        
        printf("%s  ", fil[i1].Ent->d_name);
        if(l==1) printf("\n");
        }
        if(s==1){
            printf("\n总用量：  %d",blocks);
            blocks=0;
        }
        if(R==1){
        for(int i1=0;i1<t1;i1++){
            if(a==0&&fil[i1].Ent->d_name[0]=='.') {
                free(fil[i1].Ent);
                continue;//cv后变量没有改为该函数内对应的变量
            }
            if(strcmp(fil[i1].Ent->d_name,".")==0||strcmp(fil[i1].Ent->d_name,"..")==0){
                free(fil[i1].Ent);
                continue;
            }
            
            //printf("\n\n");
            ls_R(fil[i1].Ent);
            free(fil[i1].Ent);
        }
        }
        }
    
        if(r==1){
            for(int i1=t1-1;i1>=0;i1--){
            if(a==0){
            if(strcmp(fil[i1].Ent->d_name,".")==0||strcmp(fil[i1].Ent->d_name,"..")==0||fil[i1].Ent->d_name[0]=='.')
            continue;
        }
        if(i==1){
            printf("%lu  ",fil[i1].Ent->d_ino);
        }
        if(s==1){
            blocks+=ls_s(fil[i1].Ent);
        }
        if(l==1){
            ls_l(fil[i1].Ent);
        }
        printf("%s  ", fil[i1].Ent->d_name);
        if(l==1) printf("\n");
        }
        if(s==1){
            printf("\n总用量：  %d",blocks);
            blocks=0;
        }
        if(R==1){
        for(int i1=t1-1;i1>=0;i1--){
            if(a==0&&fil[i1].Ent->d_name[0]=='.') {
                free(fil[i1].Ent);
                continue;
            }
            
            if(strcmp(fil[i1].Ent->d_name,".")==0||strcmp(fil[i1].Ent->d_name,"..")==0){
                free(fil[i1].Ent);
                continue;
            }
            
            ls_R(fil[i1].Ent);
            free(fil[i1].Ent);
        }
            
        }
        }
        free(fil); 
        //pause();
}

//打开子目录
//如果是链接，不打开？？？
void ls_R(struct dirent *ent){
    struct stat statbuf;
    stat(ent->d_name,&statbuf);
    if(S_ISDIR(statbuf.st_mode)&&S_ISLNK(statbuf.st_mode)==0){// &&strcmp(ent->d_name,".")!=0&&strcmp(ent->d_name,"..")!=0
        char name[256];
        printf("\n\033[32m%s/%s：\n\033[0m",getcwd(name,256),ent->d_name);
        chdir(ent->d_name);
        ls_open(".");
        chdir("..");
        //printf("[32m%s:\n",getcwd(name,256));
    }
    
}

//块大小
int ls_s(struct dirent *ent){
    struct stat statbuf;
stat(ent->d_name,&statbuf);
printf("%lu  ",statbuf.st_blocks/2);
return statbuf.st_blocks/2;
}

//详细属性
void ls_l(struct dirent *ent){
    struct stat statbuf;
stat(ent->d_name,&statbuf);
        switch (statbuf.st_mode & S_IFMT)
    {
        case S_IFREG:
            printf("-");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFBLK:
            printf("b");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
    }
    if(statbuf.st_mode&S_IRUSR)printf("r");else printf("-");
    if(statbuf.st_mode&S_IWUSR)printf("w");else printf("-");
    if(statbuf.st_mode&S_IXUSR)printf("x");else printf("-");
    if(statbuf.st_mode&S_IRGRP)printf("r");else printf("-");
    if(statbuf.st_mode&S_IWGRP)printf("w");else printf("-");
    if(statbuf.st_mode&S_IXGRP)printf("x");else printf("-");
    if(statbuf.st_mode&S_IROTH)printf("r");else printf("-");
    if(statbuf.st_mode&S_IWOTH)printf("w");else printf("-");
    if(statbuf.st_mode&S_IXOTH)printf("x");else printf("-");
      struct passwd *pw = getpwuid(statbuf.st_uid);
    struct group *gr = getgrgid(statbuf.st_gid);
            printf("  %lu  %s  %s  %ld  %s",statbuf.st_nlink,pw->pw_name,gr->gr_name,statbuf.st_blksize,ctime(&statbuf.st_mtime));
}

// void ls_read(DIR *dir){
//     struct dirent *ent; 
//     int blocks=0;
//      while ((ent = readdir(dir)) != NULL) {
//         if(r==1){
//             ls_read(dir);//while 改掉
//         }
//         if(a==0){
//             if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0||ent->d_name[0]=='.')
//             continue;
//         }
//         if(i==1){
//             printf("%lu  ",ent->d_ino);
//         }
//         if(s==1){
//             blocks+=ls_s(ent);
//         }
//         if(l==1){
//             ls_l(ent);
//         }
//         printf("%s  ", ent->d_name);
//         if(l==1) printf("\n");
//         }
//         if(s==1){
//             printf("\n总用量：  %d",blocks);
//             blocks=0;
//         }
//         if(R==1){
//             rewinddir(dir);
//         while((ent=readdir(dir))!=NULL){
//             if(a==0&&ent->d_name[0]=='.') continue;
//             if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0)
//             continue;
//             ls_R(ent);
//         }
            
//         }
        
        
// }

void ls_open(char *dir_path){
    DIR *dir;
    if ((dir = opendir(dir_path)) != NULL) {
            ls_t(dir);
            //closedir(dir);
    } else {
        perror("打开目录失败");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *ent;
    char *dir_path = ".";
   int opt,opterr=0;

    while ((opt = getopt(argc, argv, "alRtris")) != -1) {
        switch (opt) {
            case 'a':
                a=1;
                break;
            case 'l':
                l=1;
                break;
            case 'R':
                R=1;
                break;
            case 't':
                t=1;
                break;
            case 'r':
                r=1;
                break;
            case 'i':
                i=1;
                break;
            case 's':
                s=1;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
        }
    }
    char dir_path_yuan[256];
    char dirr[256];
    getcwd(dir_path_yuan,256);//存储原先的地址
    if(argc==optind){
        printf("\033[32m%s:\n\033[0m",getcwd(dirr,256));
                ls_open(".");
                printf("\n");
            }
    while(optind<argc){
        dir_path=argv[optind];
        chdir(dir_path);
        printf("\033[32m%s:\n\033[0m",getcwd(dirr,256));
        
        ls_open(".");//改变工作目录后又打开了工作目录的名字 ".."（含路径的参数）会出错
        chdir(dir_path_yuan);
               printf("\n");
               optind++;
    }
    
               
    return EXIT_SUCCESS;
}