#include <stdio.h>
int main()
{
   const int a[2]={10}; //若const a=10，编译器也会默认为a是int类型的
   int *P=a; //注意需要强制&a前需要加int*类型强制类型转换
   *P=12;
   printf("a=%d\n",a[0]);
   return 0;
}