#include<stdio.h>
double fact( int n ){
    double a=1;    
        if(n==0){
            return 1;
           
        }
    for(int i=1;i<=n;i++){
            a*=i;
        }
        return a;
    }

int main(){
    double a,b,x;
    scanf("%lf%lf",&a,&b);
    x=fact(b)/(fact(a)*fact(b-a));
    printf("result = %.0lf",x);
}