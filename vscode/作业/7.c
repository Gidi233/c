#include<stdio.h>
int main(){
    int a[1010],b,c[1010],d[1010]={0},x=0,y,t,i,m=0,max;
 //c[]数字，d[]次数
    scanf("%d",&b);
    for(i=0;i<b;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<b;i++){
        x=0;
        for(t=0;t<i;t++){
            if(c[t]==a[i]){
               x=1;
            break; 
            }
        }
       if(x==0){
        c[m]=a[i];
        d[m]++;
        m++;
        }
        if(x){
            d[t]++;
        }
    }
max=d[0];
y=0;
    for(i=0;i<m;i++){
        if(max<d[i]){
            max=d[i];
            y=i;
        }
    }
    printf("%d %d",c[y],d[y]);
}