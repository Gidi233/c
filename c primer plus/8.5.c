#include<stdio.h>
int main(){
    printf("想一个0-100的数\n");
    printf("小了输入'x',大了输入'd',正确输入'y'");
    int a=50,x=0,y=100;
    char ch;
    /*while(ch!='y'){
        printf("我猜是%d\n",a);
        ch=getchar();
        while(getchar()!='\n')
        continue;
        while(1){
           if(ch=='d'){
            y=a;
            a=(y+x)/2;
            break;
        }else{
            if(ch=='x'){
                x=a;
                a=(x+1+y)/2;
                break;
            }else{
                if(ch!='y'){
                    printf("请输入正确的字符");
                    ch=getchar();
                    while(getchar()!='\n')
                    continue;
                    continue;
                }else
                break;
            }
        } 
        }
        
    }*/
    while(1){
        printf("我猜是%d\n",a);
        ch=getchar();
        while(getchar()!='\n')
        continue;
        switch (ch)
    {
    case 'x':x=a;
                a=(x+1+y)/2;
                continue;
    case 'd':y=a;
            a=(y+x)/2;
             continue;
    case 'y':break;
    default:printf("请输入正确的字符");
                    ch=getchar();
                    while(getchar()!='\n')
                    continue;
                    continue;
        
    } 
   break;
    }
   
    printf("congratulations!");
}