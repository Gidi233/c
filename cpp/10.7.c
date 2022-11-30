#include<stdio.h>
void copy(double a[],double b[],int x){
    for(int i=0;i<x;i++){
        b[i]=a[i];
    }
}
int main(){
    double a[2][2]={1,2,3,4},b[2][2];
for(int i=0;i<2;i++){
    copy(a[i],b[i],2);
}
for(int i=0;i<2;i++){
    for(int t=0;t<2;t++){
        printf("%lf\n",b[i][t]);
    }
}

}