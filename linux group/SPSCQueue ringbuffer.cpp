#include <memory>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>
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
    explicit SPSCQueue(int capacity) : max_(capacity+1) {
        queue=new unique_ptr<T>[max_]();
    }

    bool Push(unique_ptr<T> value) {
        while((tail+1)%max_==head) sleep(0.1);
        *(queue+tail)=move(value);
        tail=(tail+1)%max_;
        return 1;
    }

    unique_ptr<T> Pop() {
        while(tail==head) sleep(0.1);
        unique_ptr<T> res(move(*(queue+head)));//*
        head=(head+1)%max_;
        return res;
    }
    ~SPSCQueue() {
        delete []queue;
    }

private:
    int head=0,tail=0;//tail是插入的位置 head是弹出的位置
    unique_ptr<T> *queue;
    int max_;
    mutex mutex_;
    condition_variable cond_;
};


void producer(SPSCQueue<char> *arg){
    while(1){
    for(char i='a';i<'z';i++){
        unique_ptr<char> pchar(new char(i));
        (arg)->Push(move(pchar));
    }
    // unique_ptr<char> pchar(new char('\n'));
    // (arg)->Push(move(pchar));
    }

}

void consumer(SPSCQueue<char> *arg){
    while(1){
        printf("%c \n",*(arg->Pop()));
    }
}


int main(){
    int max;
    scanf("%d",&max);
    SPSCQueue<char> dan(max);
    thread pro(producer,&dan);
    thread con(consumer,&dan);
    pro.join();
    con.join();
    return 0;
}