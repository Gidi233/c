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

int a,l,t,r,i,s,R,mount;
long long int blocks;
void ls_t(DIR *dir);
void ls_R(struct dirent *ent);
void ls_s(struct dirent *ent);
void ls_l(struct dirent *ent);
void ls_read(DIR *dir);
void ls_open(char *dir_path);


//时间顺序
void ls_t(DIR *dir){
    struct dirent *ent; 
     while ((ent = readdir(dir)) != NULL) {
        struct stat statbuf;
    stat(ent->d_name,&statbuf);
    
        }

        // if(r==1){
        //  ls_read(dir);   ;//把while改掉
        // }
        // if(a==0){
        //     if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0||ent->d_name[0]=='.')
        //     continue;
        // }
        // if(i==1){
        //     printf("%lu  ",ent->d_ino);
        // }
        // if(s==1){
        //     ls_s(ent);
        // }
        // if(l==1){
        //     ls_l(ent);
        // }
        // printf("%s  ", ent->d_name);
        
        // if(R==1){
        //     ls_R(ent);
        // }
        // if(l==1) printf("\n");
    

}

//打开子目录
//最后打开目录
void ls_R(struct dirent *ent){
    struct stat statbuf;
    stat(ent->d_name,&statbuf);
    if(S_ISDIR(statbuf.st_mode)){
        char name[100];
        printf("\n%s/%s:\n",getcwd(name,100),ent->d_name);
        chdir(ent->d_name);
        ls_open(".");
        chdir("..");
        printf("    结束\n");
    }
    
}

//块大小
//改为单个目录大小 返回blocks
void ls_s(struct dirent *ent){
    struct stat statbuf;
stat(ent->d_name,&statbuf);
blocks+=statbuf.st_blocks/2;
printf("%lu  ",statbuf.st_blocks/2);
}

//属性
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
            // free(pw);
            // free(gr);
}

void ls_read(DIR *dir){
    struct dirent *ent; 
     while ((ent = readdir(dir)) != NULL) {
        if(r==1){
            ls_read(dir);//把while改掉
        }
        if(a==0){
            if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0||ent->d_name[0]=='.')
            continue;
            // if(strcmp(R==0&&(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0||ent->d_name[0]=='.'))
            // continue;
            // if(strcmp(R==1&&ent->d_name[0]=='.'))
            // continue;
        }
        if(i==1){
            printf("%lu  ",ent->d_ino);
        }
        if(s==1){
            ls_s(ent);
        }
        if(l==1){
            ls_l(ent);
        }
        printf("%s  ", ent->d_name);
        
        if(R==1&&strcmp(ent->d_name,".")!=0&&strcmp(ent->d_name,"..")!=0){
            ls_R(ent);
        }
        if(l==1) printf("\n");
        }
        
}

void ls_open(char *dir_path){
    DIR *dir;
    if ((dir = opendir(dir_path)) != NULL) {
        if(t==1){
            ls_t(dir);
        }else {
            ls_read(dir);
        } 
        closedir(dir);
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

    if (optind<argc&&argc!=1){
        dir_path=argv[optind];
        chdir(dir_path);
    }
               ls_open(dir_path);
               if(s==1) printf("\n总用量  %lld",blocks);
               printf("\n");
    return EXIT_SUCCESS;
}