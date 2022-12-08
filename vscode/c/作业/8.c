#include <stdio.h>
#include<math.h>
int main(){
int x=0,a;
scanf("%d",&a);
for(int i=1;i<=a;i++){
    x+=pow(2,i);
}
printf("result = %d",x);
}