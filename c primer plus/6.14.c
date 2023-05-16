#include<stdio.h>
int main(){
    double a[8],b[8];
    for(int i=0;i<8;i++){
        scanf("%lf",&a[i]);
    }
    for(int i=0;i<8;i++){
        if(i==0)
        b[i]=a[i];
        else
        b[i]=a[i]+b[i-1];
    }
    for(int i=0;i<8;i++){
        printf("%lf\n",a[i]);
    }
    for(int i=0;i<8;i++){
        printf("%lf\n",b[i]);
    }
}