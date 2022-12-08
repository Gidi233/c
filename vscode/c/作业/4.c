#include <stdio.h>

void printdigits( int n );

int main()
{
    int n;
    
    scanf("%d", &n);
    printdigits(n);

    return 0;
}

void printdigits( int n ){
    int a[10],i=0,c=0,b=n;
    while(b>0){
        a[i]=b%10;
        b/=10;
        i++;
        c++;
    }
    for(int i=c-1;i>=0;i--){
        printf("%d\n",a[i]);
    }
    if(n==0)
    printf("0");
}
