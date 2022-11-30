#include<stdio.h>
int main(){
    int max,a[11],b=0,x;
    scanf("%d",&x);

    for(int i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    max=a[0];
    for(int i=0;i<x;i++){
        if(a[i]>max){
            max=a[i];
            b=i;
        }
    }
    printf("%d %d",max,b);
    }