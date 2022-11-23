#include<stdio.h>
int main(){
    int t,i,n,x=0,a[30]={0},b[30]={0},c[30]={0};
    a[0]=1;
    b[0]=1;
    scanf("%d",&n);
    for( i=2;i<n;i++){x=0;
        for( t=0;t<30;t++){ 
                c[t]+=a[t]+b[t];
            if(c[t]>=10){
               c[t+1]++;
                c[t]-=10;
            }
        }
        for(t=0;t<30;t++){
            a[t]=b[t];
            b[t]=c[t];
            c[t]=0;
        }
    }
    for(t=29;;t--){
        if(b[t]!=0){
            break;
        }
    }
    for(i=t;i>=0;i--){
        printf("%d",b[i]);
    }
}