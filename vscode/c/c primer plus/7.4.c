#include<stdio.h>
int main(){
    int a=0;
    char ch;
    ch=getchar();
    while(ch!='#'){
        if(ch=='.'){
            putchar('!');
            a++;
        }else{
            if(ch=='!'){
            putchar(ch);
            putchar(ch);
            a++;
        }else{
            putchar(ch);
        }
        }    
        ch=getchar();
    }
    printf("\n%d",a);
}