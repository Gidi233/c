#include <memory>
#include <string>
#include <queue>
#include<pthread.h>
//#include <mutex>
//#include <condition_variable>
using namespace std;


template <typename T>
class SPSCQueue {
public:
    SPSCQueue(int capacity) : max_(capacity) {}

    bool Push(T value) {
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

    T Pop() {
        pthread_mutex_lock(&mutex);
        while (queue_.empty()) {
            pthread_cond_wait(&cond,&mutex);
        }
        now--;
        T value = move(queue_.front());
        queue_.pop();
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        return value;
    }

    ~SPSCQueue(){}

private:
    int max_,now=0;
    queue<T> queue_;
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
    //unique_ptr<T> value;
};

void *producer(void *arg){
    while(1){
    for(char i='a';i<'z';i++){
        unique_ptr<char> pchar(new char(i));
        ((SPSCQueue<unique_ptr<char>> *)arg)->Push(move(pchar));
    }        
    }

}

void *consumer(void *arg){
    while(1){
        printf("%c\n",*(((SPSCQueue<unique_ptr<char>> *)arg)->Pop()));
    }
}

int main(){
    int num=1,max;
    scanf("max:%d",&max);
    SPSCQueue<unique_ptr<char>> dan(max);
    pthread_t con[100],pro[100];
    for(int i=0;i<num;i++){
        pthread_create(&pro[i],nullptr,producer,&dan);
        pthread_create(&con[i],nullptr,consumer,&dan);
    }
    for(int i=0;i<num;i++){
        pthread_join(pro[i],nullptr);
        pthread_join(con[i],nullptr);
    }
    return 0;
}