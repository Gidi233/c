#include<stdio.h>
    int c;
double power(int a,int b){
    
if(a==0)
return 0;
else{
    if(b==0)
return 1;
if(b>1){
return power(a*c,b-1);
}
if(b<-1){
return power(a*c,b+1);
}
if(b==1)
return a;
if(b==-1)
return 1.0/a;
}

}
int main(){
    int a,b;
    printf("输入一个底数和它的幂");
    scanf("%d%d",&a,&b);
    c=a;
    printf("结果为%10lf",power(a,b));
}