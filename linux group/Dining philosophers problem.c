//一共5个锁 一人持两个锁 先左再右 一个锁记录这是第几个人
//1.记录当前吃一个锁的人数（开另一种锁）如果人数为5 解锁wait（1）再上锁
//2.一个人先持一个锁然后cond_wait 等另一个与他公用一只筷子的人cond_signal  if(num==(num0+5-1)%5) pthread_cond_signal;
// if(set==0)//检测有没有人先持这个锁
// if(pthread_mutex_trylock(&mutex)==0) {
//     set=1;
//     pthread_mutex_unlock(mutex);
// }
