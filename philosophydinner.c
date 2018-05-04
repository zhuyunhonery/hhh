#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<utime.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<pthread.h>
#define	N 5//定义五个哲学家
#define LEFT (i+N-1)%N
#define RIGHT (i-2+N)%N
pthread_mutex_t mutex[5]={PTHREAD_MUTEX_INITIALIZER};
void takechopstick(int i);//拿起筷子
void putchopstick(int i);//放下筷子
void* philosopher(void *i);//哲学家操作
void thinking(int i);//哲学家思考
void eating(int i);//哲学家就餐

int main()
{
	int i;
	pthread_t tid[N];//哲学家线程单位
	for(i=0;i<N;i++)
	{
		pthread_create(&tid[i],NULL,(void*)philosopher,(void*)(&hhh[i]));
	}
	for(i=0;i<N;i++)
	{
		pthread_join(tid[i],NULL);//等待线程结束
	}
	return 0;
}
void takechopstick(int i)
{
	int ret;
ymc:
	while(1)
	{
	ret=pthread_mutex_trylock(&mutex[LEFT]);
	if(ret!=0)
	continue;//加锁成功则返回0
	else
	break;
	}
	while(1)
	{
	ret=pthread_mutex_trylock(&mutex[RIGHT]);
	if(ret!=0)
	{
		pthread_mutex_unlock(&mutex[LEFT]);
		goto ymc;
	}
	else
	break;
	}
}
void putchopstick(int i)
{
	pthread_mutex_unlock(&mutex[LEFT]);
	pthread_mutex_unlock(&mutex[RIGHT]);
}
void* philosopher(void *arg)
{
	int i = *(int *)arg;
	while(1){
		thinking(i);
		takechopstick(i);
		eating(i);
		putchopstick(i);
		}
}
void thinking(int i)
{
	printf("philosopher %d is thinking\n",i);
	sleep(2);
}
void eating(int i)
{
	printf("philosopher %d is eating\n",i);
	sleep(2);
}
