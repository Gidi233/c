#include<stdio.h>
int main(){
    int a[25],b[33],c[23],x,y,z=0,t,i,m=0,n=0;
    scanf("%d",&x);
    for(i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&y);
    for(i=0;i<y;i++){
        scanf("%d",&b[i]);
    }
    for(i=0;i<x;i++){
        m=0;
        for(t=0;t<y;t++){
            if(a[i]==b[t]){
                m=1;
                break;
            }
        }if (m==0)
        {n=0;
            for(t=0;t<z;t++){
                if(a[i]==c[t]){
                    n=1;
                    break;
                }
            }
                 if(n==0){
                    c[z]=a[i];
                    z++;
                 }   
        }
    }

    for(i=0;i<y;i++){
        m=0;
        for(t=0;t<x;t++){
            if(a[t]==b[i]){
                m=1;
                break;
            }
        }if (m==0)
        {n=0;
            for(t=0;t<z;t++){
                if(b[i]==c[t]){
                    n=1;
                    break;
                }
            }
                 if(n==0){
                    c[z]=b[i];
                    z++;
                 }   
        }
    }
for(t=0;t<z;t++){
    printf("%d ",c[t]);
}
}