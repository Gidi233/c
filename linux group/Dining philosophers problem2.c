#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>

//一共5个锁 一人持两个锁 先左再右 一个锁记录这是第几个人
//2.一个人先持一个锁然后cond_wait 等另一个与他公用一只筷子的人cond_signal 

pthread_mutex_t mutex[5]={PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER},set_m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int set,num_set;

void *philosopher(void *num){
    int num1=( int )(*( int *)num);
    pthread_mutex_lock(&mutex[(num1)%5]);//左
    do{
        if(set==0&&pthread_mutex_trylock(&set_m)==0){
        set=1;
        num_set=num1;
        pthread_mutex_unlock(&set_m);
        }
        if(num_set==num1) pthread_cond_wait(&cond,&mutex[(num1)%5]);//不能让哲学家再开吃所以会卡在这里
    }while(pthread_mutex_trylock(&mutex[(num1+1)%5])!=0);//条件变量为while（右没有人持有）

    if(set==1&&num_set==num1){
        pthread_mutex_lock(&set_m);
        set=0;
        pthread_mutex_unlock(&set_m);
    }

    //printf("哲学家%d在等待",&num+1);
    printf("哲学家%d已吃完\n",num1+1);
    pthread_mutex_unlock(&mutex[(num1)%5]);//左
    pthread_mutex_unlock(&mutex[(num1+1)%5]);//右
    if(num1==(num_set-1+5)%5) pthread_cond_signal(&cond);
    pthread_exit(NULL);

}

int main(){
    pthread_t phi[5];
    int j=0,a[5]={0};

    while(1){
        set=0;
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