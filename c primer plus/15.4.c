#include<stdio.h>
int change(int a,int b){
    int x=1;
    for(int i=0;i<b;i++){
        x*=2;
    }
    while(a>x){
        a/=2;
    }
    return a%2;
}
int main(){
    int b,a,c;
    scanf("%d%d",&a,&c);
    b=change(a,c);
    printf("%d",b);
}