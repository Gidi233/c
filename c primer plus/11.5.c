#include<stdio.h>

char *find(char *a,char b){
    while(*a!='\0'&&*a!=b){
        a++;
    }
    if(*a=='\0')
    return 0;
    if(*a==b)
    return a;
}
int main(){
    char a[10];
    char ch;
    char *c;
    printf("输入！退出\n");
    
    while((ch=getchar())!='z'){
        scanf("%s",a);
        while(getchar()!='\n')
        continue;
        c=find(a,ch);
        if(c!=0)
        printf("%s中有%c\n",a,*c);
        else
        printf("%s中没有%c\n",a,ch);
    }
}