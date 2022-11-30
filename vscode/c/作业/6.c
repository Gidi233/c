#include<stdio.h>
int main(){
    int a[10],i,t,x=1;
    for(i=0;i<10;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<10;i++){
        if(a[i]%5==0){
            x+=a[i];
        }
    }
    printf("%d",x);
}