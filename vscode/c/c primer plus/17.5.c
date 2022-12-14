#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    char date;
    struct node *next;
}LIST;

int main(){
    char a;
    LIST *head=(LIST *)malloc(sizeof(LIST));
    head->next=NULL;
    while((a=getchar())!='\n'){
        LIST *y=(LIST *)malloc(sizeof(LIST));
        y->date=a;
        y->next=head->next;
        head->next=y;
    }
    while(head->next!=NULL){
        printf("%c",head->date);
        head=head->next;
    }
    printf("%c",head->date);
}