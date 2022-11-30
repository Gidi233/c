#include<stdio.h>
int main(){
    int a[15],t,y,i,x;
    scanf("%d",&x);
    for(i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    for(i=1;i<x;i++){
        for(t=0;t<i;t++){
             if(a[i]==a[t]){
            for(y=i;y<x-1;y++){
                a[y]=a[y+1];
            }
             i--;
             x--;
             break;
        }
        }
    }
    for(i=0;i<x;i++){
        printf("%d ",a[i]);
    }
 //   printf("\b");
}