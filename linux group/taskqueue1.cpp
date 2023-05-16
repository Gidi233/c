#include <memory>
#include <string>
#include <queue>
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
        unique_lock<mutex> lock(mutex_);
        while (queue_.size() >= max_) {
            cond_.wait(lock);
        }
        now++;
        queue_.push(value);
        lock.unlock();
        cond_.notify_one();
        return true;
    }

    unique_ptr<T> Pop() {
        unique_lock<mutex> lock(mutex_);
        while (queue_.empty()) {
            cond_.wait(lock);
        }
        now--;
        value = move(queue_.front());
        queue_.pop();
        lock.unlock();
        cond_.notify_one();
        return value;
    }

private:
    int max_,now=0;
    queue<T> queue_;
    mutex mutex_;
    condition_variable cond_;
    unique_ptr<T> value;
};

int main(){
    return 0;
}