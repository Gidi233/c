#include<stdio.h>
int er(int a,int b){
    while(a>0){
        er(a/b,b);
        printf("%d",a%b);
        return 0;
    }
}

int main(){
    int a,b;
    printf("输入数字： 输入进制：");
    scanf("%d%d",&a,&b);
    printf("%d的%d进制数为",a,b);
    er(a,b);
}