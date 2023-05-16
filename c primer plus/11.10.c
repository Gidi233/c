#include<stdio.h>
char *delete(char *a){
    while(*a!='\0'){
        if(*a==' '){
            int x=0;
            while(*a!='\0'){
                *a=*(a+1);
                a++;
                x++;
            }
            a-=x;
        }
        else
        a++;
    }
    return 0;
}

int main(){
char a[10];
a[0]=getchar();

while(a[0]!='\n'){
gets(a+1);
    delete(a);
    printf("%s",a);
    a[0]=getchar();
    
}
}