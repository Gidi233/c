#include <iostream> 
class Object
{
private:
    int a;
    int b;
	//传统C语言方式，传一个指针进去
    int Add()
    {
        return Add1();
    }
        int Add1()
    {
        return a + b;
    }
 
public:
    void Set_value(int a, int b)
    {
        this->a = a;
        this->b = b;
    }

	//C++直接就在类内部实现了这个功能
    void Test_add()
    {
        printf("Add:%d \n", Add());
    }
 
    void Print_this()
    {
        printf("this:%p\n", this); //打印this地址
    }
};
 
int main()
{
    Object a;
    printf("a:%p\n", &a);//打印对象地址
    a.Print_this();
    a.Set_value(2, 6); //设置值
    a.Test_add(); //加法并打印
 
    std::cout << "Hello World!\n";
    return 0;
}