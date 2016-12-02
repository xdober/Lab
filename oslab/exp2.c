#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux specific) */
}arg;
void P(int semid, int index) {//P操作
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
	semop(semid,&sem,1);	//1:表示执行命令的个数
	return;
}
void V(int semid, int index) {//V操作
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
	return;
}

int S;//信号灯
int a;//缓冲区
void *subp1();
void *subp2();

int main() {
	S = semget(IPC_PRIVATE, 2, IPC_CREAT|0666);
	if(S<0) {
		perror("semget()");
		return -1;
	}
	arg.val = 1;
	semctl(S, 0, SETVAL, arg);//信号灯S[0]赋初值1
	arg.val = 0;
	semctl(S, 1, SETVAL, arg);//信号灯S[1]赋初值0
	pthread_t p1,p2;//线程句柄
	int rt1,rt2;
	rt1 = pthread_create(&p1, NULL, (void*) subp1, NULL);//创建线程
	rt2 = pthread_create(&p2, NULL, (void*) subp2, NULL);
	if(rt1!=0 || rt2!=0) {
		printf("Creat pthread error!\n");
		exit(1);
	}
	pthread_join(p1, NULL);//等待线程结束
	pthread_join(p2, NULL);

	semctl(S, 2, IPC_RMID, arg);//删除信号灯
    return  0;
}
void *subp1() {//线程1计算
	for(int i = 1; i<=100; i++) {
		P(S,0);
		a += i;
		V(S,1);
	}
	return NULL;
}
void *subp2() {//线程2打印
	for(int i = 1; i<=100; i++) {
		P(S,1);
		printf("%7d\t", a);
		V(S,0);
	}
	printf("\n");
	return NULL;
}
