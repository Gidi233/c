#include <memory>
#include <string>
#include <queue>
#include<pthread.h>
//#include <mutex>
//#include <condition_variable>
using namespace std;

// // Single-producer , single-consumer Queue
// template<class T>
// class SPSCQueue {
// public:
//     explicit SPSCQueue(int capacity);
//     virtual bool Push(std::unique_ptr<T>) = 0;
//     virtual std::unique_ptr<T> pop() = 0;
//     virtual ~SPSCQueue() = 0;
// };

int max_;
pthread_t con,pro;
    int now=0;
    queue<unique_ptr<char>> queue_;
    pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
    



    bool Push(unique_ptr<char>& value) {
        pthread_mutex_lock(&mutex);
        while (queue_.size() >= max_) {
            pthread_cond_wait(&cond,&mutex);
        }
        now++;
        queue_.push(move(value));
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        return true;
    }

    unique_ptr<char> Pop() {
        pthread_mutex_lock(&mutex);
        while (queue_.empty()) {
            pthread_cond_wait(&cond,&mutex);
        }
        now--;
        unique_ptr<char> value= move(queue_.front());
        queue_.pop();
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        return value;
    }



void *producer(void *arg){
    while(1){
    for(char i='a';i<'z';i++){
        unique_ptr<char> pchar(new char(i));
        Push(pchar);
    }        
    }

}

void *consumer(void *arg){
    while(1){
        printf("%c\n",*(Pop().release()));
    }
}

int main(){
    int num=0;
    //scanf("num & max:%d%d",&num,&max);
    scanf("max:%d",&max_);
    pthread_t con,pro;
        pthread_create(&pro,nullptr,producer,nullptr);
        pthread_create(&con,nullptr,consumer,nullptr);
    
        pthread_join(pro,nullptr);
        pthread_join(con,nullptr);
    
    return 0;
}