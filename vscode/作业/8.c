#include <stdio.h>
int main(){
    int a[25],x,b=0,y,i;
    scanf("%d%d",&x,&y);
    
    for(i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<x;i++){
        if(y==a[i]){
            b=1;
            break;
        }
    }
    if(b==1)
    printf("%d",i);
    else
    printf("Not Found");
}