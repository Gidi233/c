#include <memory>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
//#include<semaphore>
#include<semaphore.h>
#include<unistd.h>
using namespace std;

template <typename T>
class MPMCQueue {
public:
    explicit MPMCQueue(int capacity) : max_(capacity+1) {
        queue=new unique_ptr<T>[max_]();//环形缓冲区
        mutex_=new mutex[max_]();//给每一块内存上一个锁
        set=new int[max_]();//判断是否有内容
        sem_init(&pro,0,max_-1);//前面多申请一个内存是要判断头尾，而一共只有max_-1个可用//是历史遗留问题（之前用头尾判断空/满）了，改成这样的话就不用+1-1了
        sem_init(&con,0,0);

    }

    bool Push(unique_ptr<T> value) {
        sem_wait(&pro);
        int num=0,tail_=tail;
        while(1){
            unique_lock<mutex> lock(mutex_[(tail_+num)%max_],try_to_lock);
            if(lock.owns_lock()&&set[(tail_+num)%max_]==0){
                *(queue+(tail_+num)%max_)=move(value);
                set[(tail_+num)%max_]=1;
                tail=max(tail,(tail_+num+1))%max_;
                break;
            }
            else{
                num++;
            }
        }
        sem_post(&con);
        return true;
    }

//我想做一个（真）多线程，当线程A发现queue[1]正在被占用，就去看queue[2]

    unique_ptr<T> Pop() {
        sem_wait(&con);
        int num=0,head_=head;
        while(1){
            unique_lock<mutex> lock(mutex_[(head_+num)%max_],try_to_lock);
            if(lock.owns_lock()&&set[(head_+num)%max_]==1){
                unique_ptr<T> res(move(*(queue+(head_+num)%max_)));//*
                set[(head_+num)%max_]=0;
                head=max(head,(head_+num+1))%max_;
                sem_post(&pro);
                return res;
            }
            else{
                num++;
            }
        }
    }

    ~MPMCQueue() {
        delete []queue;
        delete []mutex_;
        delete []set;
        sem_destroy(&con);
        sem_destroy(&pro);
    }

private:
    // counting_semaphore s_con(0);//不知道怎么搞成c++20
    // counting_semaphore s_pro;
    int head=0,tail=0;//tail是插入的位置 head是弹出的位置
    unique_ptr<T> *queue;
    int max_;
    int *set;
    mutex *mutex_;
    condition_variable cond_;
    sem_t con,pro;
};


void producer(MPMCQueue<char> *arg){
    while(1){
    for(char i='a';i<'z';i++){
        unique_ptr<char> pchar(new char(i));
        (arg)->Push(move(pchar));
    }
    unique_ptr<char> pchar(new char('\n'));
    (arg)->Push(move(pchar));
    }

}

void consumer(MPMCQueue<char> *arg){
    while(1){
        printf("%c ",*(arg->Pop()));//问题：重复消费了
    }//给改变头尾加锁（那就始终只能有一个线程做改变，也就不用给每个内存都上锁了）pass   //判断是否有内容
}


int main(){
    int max,num;
    scanf("%d%d",&num,&max);
    MPMCQueue<char> dan(max);
    thread pro[100],con[100];
    for(int i=0;i<num;i++){
        pro[i]=thread(producer,&dan);
        con[i]=thread(consumer,&dan);
    }
    for(int i=0;i<num;i++){
        pro[i].join();
        con[i].join();
    }
    return 0;
}