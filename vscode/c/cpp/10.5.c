#include<stdio.h>
double cha(double a[],int t){
    double min=a[0],max=a[0];
    for(int i=1;i<t;i++){
        if(a[i]<min){
          min=a[i];  
        }
        if(a[i]>max)
        max=a[i];
    }
    return max-min;
}
int main(){
    double a[10]={1.1,2.2,3.3,4.4,5.5};
    double b;
    b=cha(a,5);
    printf("%lf",b);
}