#include<stdio.h>
int main(){
    int i;
    char a=65;
for ( i = 0; i < 6; i++)
{
    for(int t=0;t<=i;t++){
        printf("%c",a);
        a++;
    }
    printf("\n");
}

}