#include<stdio.h>
int main(){
    int a[15],b,x,y=0;
    scanf("%d",&x);
    for(int i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&b);
    for(int i=0;i<x;i++){
        if(b<a[i]){
for(int t=x;t>=i;t--){
    a[t]=a[t-1];
}
a[i]=b;
y=1;
break;
        }
        
    }
    if(y==0){
        a[x]=b;
    }
    if(x==0)
    a[0]=b;
    for(int i=0;i<x+1;i++){
        printf("%d ",a[i]);
    }
}