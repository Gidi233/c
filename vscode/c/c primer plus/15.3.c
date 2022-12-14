#include<stdio.h>
int change(int a){
    int x=0;
    while(a>0){
        a/=2;
        x++;
    }
    return x;
}
int main(){
    int b,a;
    scanf("%d",&a);
    b=change(a);
    printf("%d",b);
}