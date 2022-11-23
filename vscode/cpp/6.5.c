#include <stdio.h>
int main(){
    int b,i,t;
    char a,x;
    printf("输入大写字母");
    scanf("%c",&a);
    for(i=0;i<5;i++){
        x=a;
        for(t=0;t<4-i;t++){
            printf(" ");
        }
        for(int y=0;y<=i;y++){
            if(y==i)
            printf("%c",x--);

            else 
            printf("%c",x++);

        }
        for(int y=0;y<i;y++){
            printf("%c",x--);
        }
        printf("\n");
    }
}