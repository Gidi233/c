#include <stdio.h>

int factorsum( int number );
void PrintPN( int m, int n );
    
int main()
{
    int m, n;

    scanf("%d %d", &m, &n);
    if ( factorsum(m) == m ) printf("%d is a perfect number\n", m);
    if ( factorsum(n) == n ) printf("%d is a perfect number\n", n);
    PrintPN(m, n);

    return 0;
}

int factorsum( int number ){
int i,a=0;
for(i=1;i<number;i++){
    if(number%i==0){
        a+=i;
    }

}return a;
}


void PrintPN( int m, int n ){
for(int i=m;i<=n;i++){
    int a=0;
    for(int t=1;t<i;t++){
    if(i%t==0){
        a+=t;
    }
    }
    if(a==i){
        printf("%d = 1",a);
        for(int t=2;t<i;t++){
    if(i%t==0){
        printf(" + %d",t);
    }

    }
    printf("\n");
}
}
}