#include <stdio.h>
int main(){
    int a=0,b=0,x=0,y=0,ch;
    ch=getchar();
    while(ch!='0'){
        if(ch%2==0){//偶数
            a++;
            x+=ch-48;
        }
        if(ch%2!=0){
            b++;
            y+=ch-48;
        }
        ch=getchar();
    }
    printf("偶数个数：%d，平均数：%d\n",a,x/a);
    printf("奇数个数：%d，平均数：%d",b,y/b);
}