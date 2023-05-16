#include<stdio.h>
void scanf1(double a[][5],int x){
for(int i=0;i<x;i++){
    for(int t=0;t<5;t++){
        scanf("%lf",&a[i][t]);
    }
}
}

double aver1(double a[],int x){
    double y=0;
    for(int i=0;i<x;i++){
        y+=a[i];
    }
    return y/x;
}

double MAX(double a[][5],int x){
    double max=a[0][0];
    for(int i=0;i<x;i++){
        for(int t=0;t<5;t++){
            if(a[i][t]>max){
                max=a[i][t];
            }
        }
    }
    return max;
}
int main(){
    double a[3][5];
    double x[3],y,z;
    scanf1(a,3);
    for(int i=0;i<3;i++){
        x[i]=aver1(a[i],5);
    }
    y=aver1(x,3);
    z=MAX(a,3);
    printf("每组的平均数为%lf，%lf，%lf。\n"
    "所有数据的平均数为%lf\n最大值为%lf",x[0],x[1],x[2],y,z);
}