#include <iostream>
//使用你的名字替换YOUR_NAME
//#include<gtest/gtest.h>
namespace YOUR_NAME
{
    template <class T>
    // list存储的节点
    // 可以根据你的需要添加适当的成员函数与成员变量
    struct node
    {
        node<T> *prev_;
        node<T> *next_;
        T data_;
        //构造函数
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }
        node()
            : prev_(nullptr), next_(nullptr)
        {
        }
        //稀构函数
        ~node()
        {
            //delete data_;
        }
    };

    template <class T>
    //迭代器类,(类比指针)

    struct iterator
    {
        typedef node<T> node_;
        typedef iterator<T> iterator_;
        node_ *data_;
        iterator()
        {
        }
        iterator(node_ *data)
            : data_(data)
        {
        }
        ~iterator()
        {
            
        }
        //迭代到下一个节点
        //++it
        iterator_ &operator++()
        {
            data_=data_->next_;
            return *this;
        }
        //迭代到前一个节点
        //--it
        iterator_ &operator--()
        {
            data_=data_->prev_;//要不维护一个尾（空）节点，要不做双向链表(点) 情况：end是空指针无法--
            return *this;
        }
        // it++
        iterator_ operator++(int)
        {
            iterator_ ret=*this;
            ++*this;
            return ret;
        }
        //it--
        iterator_ operator--(int)
        {
            iterator_ ret=*this;
            --*this;
            return ret;
        }
        //获得迭代器的值
        T &operator*()
        {
            return this->data_->data_;
        }
        //获得迭代器对应的指针
        T *operator->()
        {
            return &(this->operator*());
        }
        //重载==
        bool operator==(const iterator_ &t)
        {
            return data_==t.data_;
            // if(t.data_==nullptr||data_==nullptr){
            //     return data_==t.data_;//*this==t错误 因为两个iterator_比较会再次 重载== 导致无限递归(点)
            // } 
            // else
            // return data_->prev_==t.data_->prev_&&
            // data_->next_==t.data_->next_&&
            // data_->data_==t.data_->data_;
        }
        //重载！=
        bool operator!=(const iterator_ &t)
        {
            return !(*this==t);
        }

        //**可以添加需要的成员变量与成员函数**
    };

    template <class T>
    class list
    {
    public:
        typedef node<T> node_;
        typedef iterator<T> Iterator;

    private:
        //可以添加你需要的成员变量
        node_ *head_=&head1; //头节点,哨兵（不存储有效数据） 
        node_ head1;//要给头结点分配空间（点）
    public:
        //构造函数
        list()
        {
            //head_->data_=0;
            head_->prev_=nullptr;//应该改为指向自己，把之后的检测为空的条件修改为(head_->next_==head_->prev_&&head_->prev_==head_)
            head_->next_=nullptr;
        }
        //拷贝构造，要求实现深拷贝
        list(const list<T> &lt)//:head_(lt.head_),tail_(lt.tail_)//不能共用同一块内存
        {
            node_* a=lt.head_->next_;
            while (a!=lt.head_)
            {
                push_back(a->data_);
                a=a->next_;
            }
        }
        template <class inputIterator>
        //迭代器构造
        list(inputIterator begin, inputIterator end)
        {
            node_* a=begin.data_;
            while (a!=end.data_)
            {
                push_back(a->data_);
                a=a->next_;
            }
        }

        ~list()
        {
            clear();
        }

        // //重载==
        // bool operator==(const list<T> &t)
        // {
        //    return t.head_==head_;
        // }
        // //重载！=
        // bool operator!=(const list<T> &t)
        // {
        //     return !(*this==t);
        // }

        //拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
            if(&lt!=this){//(点)lt!=*this因为重载运算符的第一个参数（隐式）是非const的而lt是const的，所以报错//解决方法：1.const_cast<list<T>&>(lt)强行转换2.将两个参数反过来*this==lt3.比较两个对象的地址，这样也不用重载运算符了(但应该还是比较两个对象更不容易出错)
            //先clear
            clear();//(点)this是对象指针,调用成员函数应为（*this）.clear();或 this->clear(); this是一个常量指针//当我们调用一个成员函数时，用请求该函数的对象地址初始化 this。
            node_* a=lt.head_->next_;
            while (a!=lt.head_)
            {
                push_back(a->data_);
                a=a->next_;
            }
            }
            return *this;
        }
        //清空list中的数据
        void clear()
        {
            if(head_->prev_==nullptr||head_->next_==nullptr) return ;
            else{

                node_ *i=head_->next_;
                while(head_!=i){
                    i=i->next_;
                    delete i->prev_;
                }
                head_->next_=head_->prev_=nullptr;
            }
        }
        //返回容器中存储的有效节点个数
        size_t size() const
        {
            node_ *now=head_;
            size_t a=0;
            if(head_->prev_==nullptr||head_->next_==nullptr) return 0;
            while(now->next_!=head_){
                now=now->next_;
                a++;
            }
            return a;
        }
        //判断是否为空
        bool empty() const
        {
            return head_->next_==nullptr||head_->prev_==nullptr;
        }
        //尾插
        void push_back(const T &data)
        {
            if(head_->prev_==nullptr||head_->next_==nullptr){
                head_->next_=new node(data);
                head_->prev_=head_->next_;
                head_->next_->next_=head_;
                head_->prev_->prev_=head_;
            } 
            else {
                head_->prev_->next_=new node(data);
                head_->prev_->next_->prev_=head_->prev_;
                head_->prev_=head_->prev_->next_;
                head_->prev_->next_=head_;
            }
        }
        //头插
        void push_front(const T &data)
        {
            //Iterator pos=head_;
            insert(head_,data,true);
        }
        //尾删
        void pop_back()
        {
            head_->prev_=head_->prev_->prev_;
            delete head_->prev_->next_;
            head_->prev_->next_=head_;
        }
        //头删
        void pop_front()
        {
            head_->next_=head_->next_->next_;
            delete head_->next_->prev_;
            head_->next_->prev_=head_;
        }
        //默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        void insert(Iterator pos, const T &data, bool back = true)
        {
            node_* a=new node_(data);
            if(back==false){//前
                pos.data_->prev_->next_=a;
                a->prev_=pos.data_->prev_;
                pos.data_->prev_=a;
                a->next_=pos.data_;
            }
            else{//后
                if(pos.data_->next_==nullptr||pos.data_->prev_==nullptr){
                    head_->next_=a;
                    a->prev_=head_;
                    a->next_=head_;
                    head_->prev_=a;
                }
                else{
                    a->next_=pos.data_->next_;
                    pos.data_->next_->prev_=a;
                    pos.data_->next_=a;
                    a->prev_=pos.data_;
                }
            }
        }
        //删除pos位置的元素
        void erase(Iterator pos)
        {
            if(pos.data_==head_) return ;
            else{
                pos.data_->prev_->next_=pos.data_->next_;
                pos.data_->next_->prev_=pos.data_->prev_;
                delete pos.data_;            
            }

        }

        //获得list第一个有效节点的迭代器
        Iterator begin() const
        {
            if(head_->next_==nullptr) return head_;
            else return head_->next_;
        }

        //获得list最后一个节点的下一个位置，可以理解为nullptr
        Iterator end() const
        {
            return head_;
        }
        //查找data对应的迭代器
        Iterator find(const T &data) const
        {
            node_ *now=head_->next_;
            
            while(now!=head_){
                if(now->data_==data){
                    //Iterator res(now);
                    return now;
                }
                now=now->next_;
            }
            return nullptr;
        }
        //获得第一个有效节点
        node_ front() const
        {
            return head_->next_;
        }
        //获得最后一个有效节点
        node_ back() const
        {
            return head_->prev_;
        }

    private:
        //可以添加你需要的成员函数
    };
};