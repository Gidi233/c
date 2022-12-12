#include<stdio.h>
#include<string.h>
char *string_in(char *a,char *b){
while(*a!='\0'){
    int y=0;
    while(*b!='\0'){
    int x=0;
    if(*a==*b){
        while(*a==*b){
        a++;
        b++;
        x++;
        y++;
        if(*a=='\0')
        return b-x;
        if(*b=='\0')
        return a-x;
    }
    }
    else{
       b++; 
       y++;
    }
a-=x;    
    }
b-=y;
a++;
}
return 0;
}

int main(){
    char a[10],b[10];
    scanf("%s%s",a,b);
    char *x;
    while(1){
        x=string_in(a,b);
        if(x!=0){if(strlen(a)>strlen(b))
            printf("%s中有%s,地址为%p\n",a,b,x);
            else
            printf("%s中有%s,地址为%p\n",b,a,x);
        }
        
        else
        printf("无包含\n");
        scanf("%s%s",a,b);
    }

}