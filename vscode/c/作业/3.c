#include <stdio.h>

int fib( int n );
void PrintFN( int m, int n );
    
int main()
{
    int m, n, t;

    scanf("%d %d %d", &m, &n, &t);
    printf("fib(%d) = %d\n", t, fib(t));
    PrintFN(m, n);

    return 0;
}

int fib( int n ){
if(n==1||n==2)
return 1;
else
return fib(n-1)+fib(n-2);
}

void PrintFN( int m, int n ){
int item=0,j=1; 
while (fib(j)<m) j++;
while (fib(j)<=n){
    if (item==0) printf ("%d", fib(j));
    else printf (" %d", fib(j));
    item=1;
    j++;
}
if (!item) printf ("No Fibonacci number");
}