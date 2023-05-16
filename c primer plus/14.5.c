#include<stdio.h>
typedef struct name{
    char a[10];
    char b[10];
}NAME;
typedef struct student{
    NAME name;
    float grade[3];
    float aver;
}STUDENT;

void average(STUDENT a[]){
    for(int i=0;i<4;i++){
        float x=0;
            for(int t=0;t<3;t++){
                x+=a[i].grade[t];
            }
        a[i].aver=x/3;
    }
}

void put1(STUDENT a[]){
    for(int i=0;i<4;i++){
        printf("姓名为%s%s\n",a[i].name.a,a[i].name.b);
        printf("分数分别为");
        for(int t=0;t<3;t++){
            printf("%f ",a[i].grade[t]);
        }printf("\n");
        printf("平均数为%f",a[i].aver);
    }
}
void put2(STUDENT a[]){
    float x=0;
    for(int i=0;i<4;i++){
        x+=a[i].aver;
    }
    printf("班级平均分为%f",x/4);
}

int main(){
STUDENT a[4];
for(int i=0;i<4;i++){
    printf("输入姓名");
    scanf("%s%s",a[i].name.a,a[i].name.b);
    printf("输入分数");
    for(int t=0;t<3;t++){
        scanf("%f",&a[i].grade[t]);
    }
}
average(a);
put1(a);
put2(a);

}