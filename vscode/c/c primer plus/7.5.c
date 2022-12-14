#include<stdio.h>
int main(){
    int a=0;
    char ch;
    ch=getchar();
    while(ch!='#'){
        switch (ch)
        {
        case '.':
            putchar('!');
            a++;
            break;
        case '!':
            putchar(ch);
            a++;
        default:
            putchar(ch);
        }
        ch=getchar();
    }
    printf("\n%d",a);
}