#include <stdio.h>
int main(){
    int a[100],b,x,i,t;
    scanf("%d",&b);
for(i=0;i<b;i++){
    scanf("%d",&a[i]);
}
scanf("%d",&x);
for(i=b-1;i>=0;i--){
    if(x<a[i]){
        for(t=b;t>i+1;t--){
            a[t]=a[t-1];
        }
        a[i+1]=x;
        break;
    }
if(x>=a[0]){
    for(t=b;t>0;t--){
        a[t]=a[t-1];
        
    }
    a[0]=x;
        break;
}
}
for(i=0;i<=b;i++){
    printf("%3d",a[i]);
}
}