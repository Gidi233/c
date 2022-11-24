#include<stdio.h>
//交换函数t
int main(){
    int t,a[15],b,c,i,max,min,x;
    scanf("%d",&x);
    for(i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    
    min=a[0];
    for(i=0;i<x;i++){
        if(a[i]<min){
            min=a[i];
            c=i;
        }
    }
    t=a[0];
    a[0]=a[c];
    a[c]=t;
    max=a[0];
        for(i=0;i<x;i++){
        if(a[i]>max){
            max=a[i];
            b=i;
        }
    }
    t=a[x-1];
    a[x-1]=a[b];
    a[b]=t;
    
     for(i=0;i<x;i++){
        printf("%d",a[i]);
    }
}