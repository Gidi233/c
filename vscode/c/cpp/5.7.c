#include<stdio.h>
double sum(double a){
    a=a*a*a;
    return a;
}
int main(){
    double a;
    scanf("%lf",&a);
    a=sum(a);
    printf("%lf",a); 
}