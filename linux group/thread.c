#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX_NUM 10

typedef struct{
    void (*function)(void *);
    void *arg;
} threadpool_task_t;

struct threadpool_t{
    pthread_mutex_t lock; // 互斥锁
    pthread_cond_t notify; // 条件变量
    pthread_t *threads; // 指向工作线程数组的指针
    threadpool_task_t *queue; // 指向任务队列的指针
    int thread_count; // 线程数
    int queue_size; // 队列大小
    int head; // 队头
    int tail; // 队尾
    int count; // 当前任务数量
    int shutdown; // 是否关闭线程池
    int started; // 已经创建的线程数
};
void *threadpool_thread(void *threadpool);
int threadpool_destroy(struct threadpool_t *pool);

// 初始化线程池
struct threadpool_t *threadpool_init(int thread_num, int queue_size){
    struct threadpool_t *pool;
    int i;

    if((pool = (struct threadpool_t *)malloc(sizeof(struct threadpool_t))) == NULL){
        return NULL;
    }

    // 初始化 pool
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    // 初始化队列和线程数组
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);
    pool->queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);

    // 初始化互斥锁和条件变量
    if((pthread_mutex_init(&(pool->lock), NULL) != 0) ||
       (pthread_cond_init(&(pool->notify), NULL) != 0) ||
       (pool->threads == NULL) ||
       (pool->queue == NULL)){
        if(pool){
            threadpool_destroy(pool);
        }

        return NULL;
    }

    // 创建工作线程
    for(i = 0; i < thread_num; ++i){
        if(pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool) != 0){
            threadpool_destroy(pool);

            return NULL;
        }

        pool->thread_count++;
        pool->started++;
    }

    return pool;
}

// 向线程池中添加任务
int threadpool_add(struct threadpool_t *pool, void (*function)(void *), void *argument){
    int err = 0;
    int next;

    if(pool == NULL || function == NULL){
        return -1;
    }

    // 加锁保护共享数据结构
    if(pthread_mutex_lock(&(pool->lock)) != 0){
        return -1;
    }

    next = (pool->tail + 1) % pool->queue_size;

    // 判断队列是否已满
    do{
        if(pool->count == pool->queue_size){
            err = -1;
            break;
        }

        // 添加任务到队列中
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].arg = argument;
        pool->tail = next;
        pool->count++;

        // 发送信号给工作线程
        if(pthread_cond_signal(&(pool->notify)) != 0){
            err = -1;
            break;
        }
    }while(0);

    // 解锁
    if(pthread_mutex_unlock(&pool->lock) != 0){
        err = -1;
    }

    return err;
}

// 每个工作线程执行此函数
void *threadpool_thread(void *threadpool){
    struct threadpool_t *pool = (struct threadpool_t *)threadpool;
    threadpool_task_t task;

    for(;;){
        pthread_mutex_lock(&(pool->lock));

        // 判断是否关闭线程池并且任务队列为空
        while((pool->count == 0) && (!pool->shutdown)){
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        // 判断是否关闭线程池并且任务队列为空
        if((pool->shutdown == 1) && (pool->count == 0)){
            break;
        }

        // 取出任务并处理
        task.function = pool->queue[pool->head].function;
        task.arg = pool->queue[pool->head].arg;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count--;

        pthread_mutex_unlock(&(pool->lock));

        (*(task.function))(task.arg); // 执行任务
    }

    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
}

// 销毁线程池
int threadpool_destroy(struct threadpool_t *pool){
    int i;

    if(pool == NULL){
        return -1;
    }

    pool->shutdown = 1;

    // 唤醒所有工作线程
    pthread_cond_broadcast(&(pool->notify));

    // 等待线程退出
    for(i = 0; i < pool->thread_count; ++i){
        if(pthread_join(pool->threads[i], NULL) != 0){
            return -1;
        }
    }

    // 释放内存
    if(pool->threads){
        free(pool->threads);
    }

    if(pool->queue){
        free(pool->queue);
    }

    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));

    free(pool);

    return 0;
}

// 测试函数
void task(void *arg){
    printf("Thread #%u working on %d\n", (unsigned int)pthread_self(), *(int *)arg);
    sleep(1);
}

int main(){
    struct threadpool_t *pool;
    int i;
    int *arg;

    pool = threadpool_init(THREAD_MAX_NUM, 1024);

    for(i = 0; i < 10000; ++i){
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        threadpool_add(pool, task, arg);
    }

    sleep(20);

    threadpool_destroy(pool);

    return 0;
}