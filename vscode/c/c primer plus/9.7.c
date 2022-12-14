#include<stdio.h>
int pos (char ch){
if(ch>='A'&&ch<='Z')
ch+=32;
if(ch>='a'&&ch<='z')
return ch-96;
else
return -1;
} 
int main(){
    int a=0;
    char ch;
    ch=getchar();
    while(ch!='\n'){
        a=pos(ch);
        printf("%d",a);
        ch=getchar();
    }
}