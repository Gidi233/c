#include <stdio.h>

double fact( int n );

int main()
{    
    int i, n;
    double result; 

    scanf("%d", &n);
    for(i = 0; i <= n; i++){
        result = fact(i); 
        printf("%d! = %.0f\n", i, result);
     }

    return 0;
}

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

