#include<stdio.h>
int main(){
    int a,b,c;
    scanf("%d",&a);
    while(a>0){
    if (a>=7){
        b=a/7;
        c=a%7;
    }else{
        b=0;
        c=a;
    }
    printf("%d days are %d weeks, %d days.\n",a,b,c);
    scanf("%d",&a);
}
}