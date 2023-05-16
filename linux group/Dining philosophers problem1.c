#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>

//一共5个锁 一人持两个锁 先左再右 一个锁记录这是第几个人
//1.记录当前吃一个锁的人数（开另一种锁）如果人数为5 解锁sleep（1）再上锁

pthread_mutex_t mutex[5]={PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER},now_m=PTHREAD_MUTEX_INITIALIZER;
int now=0;

void *philosopher(void *num){
    int num1=( int )(*( int *)num);
    pthread_mutex_lock(&mutex[(num1)%5]);//左
    pthread_mutex_lock(&now_m);
    now++;
    pthread_mutex_unlock(&now_m);
    while(now==5){//set=1同时只有一个在等待
        pthread_mutex_unlock(&mutex[(num1)%5]);
        sleep(1);
        pthread_mutex_lock(&mutex[(num1)%5]);
    }
    pthread_mutex_lock(&mutex[(num1+1)%5]);//右
    pthread_mutex_lock(&now_m);
    now--;
    pthread_mutex_unlock(&now_m);
    //printf("哲学家%d在等待",&num+1);
    printf("哲学家%d已吃完\n",num1+1);
    pthread_mutex_unlock(&mutex[(num1)%5]);//左
    pthread_mutex_unlock(&mutex[(num1+1)%5]);//右
    pthread_exit(NULL);

}

int main(){
    pthread_t phi[5];
    int j=0,a[5]={0};

    while(1){
        for(int i=0;i<5;i++){
            a[i]=i;//??不加这一行会输出哲学家6已吃完
            pthread_create(&phi[i],NULL,philosopher,&a[i]);
        }
        
        for(int i=0;i<5;i++){
            pthread_join(phi[i],NULL);
        }
        printf("哲学家全部吃完\n\n\n");
        sleep(1);
    }
    return 0;
}