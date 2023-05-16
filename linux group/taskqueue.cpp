#include <memory>
#include <string>
#include <queue>
#include<pthread.h>
#include <mutex>
#include <condition_variable>
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





template <typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(int capacity) : max_(capacity) {}

    bool Push(unique_ptr<T> value) {
        pthread_mutex_lock(&mutex);
        while (queue_.size() >= max_) {
            pthread_cond_wait(&cond,&mutex);
        }
        now++;
        queue_.push(value);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        return true;
    }

    unique_ptr<T> Pop() {
        pthread_mutex_lock(&mutex);
        while (queue_.empty()) {
            pthread_cond_wait(&cond,&mutex);
        }
        now--;
        value = move(queue_.front());
        queue_.pop();
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        return value;
    }

    ~MPMCQueue(){}

private:
    int max_,now=0;
    queue<T> queue_;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    unique_ptr<T> value;
};

//Multi-producer , Multi-consumer Queue
// template<class T>
// class MPMCQueue {
// public:
//     explicit MPMCQueue(int capacity);
//     virtual bool Push(std::unique_ptr<T>) = 0;
//     virtual std::unique_ptr<T> pop() = 0;
//     virtual ~MPMCQueue() = 0;
// };

int main(){
    int num=0;
    //scanf("num & max:%d%d",&num,&max);
    scanf("max:%d",&max);
    pthread_t con[100],pro[100];
    for(int i=0;i<num;i++){
        pthread_create(&pro[i],nullptr,producer,nullptr);
        pthread_create(&con[i],nullptr,consumer,nullptr);
    }
    for(int i=0;i<num;i++){
        pthread_create(pro[i],nullptr);
        pthread_create(con[i],nullptr);
    }
    return 0;
}