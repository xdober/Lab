#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
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
FILE* fp1, fp2;
char* shmaddr1,shmaddr2;
int main() {
    int shmid;
    shmid = shmget(IPC_PRIVATE,4096,IPC_CREATE|IPC_EXCL|0660);//创建共享内存
    if (shmid == -1) {
        perror("shmget()");
    }
    int S;//信号灯
    S = semget(IPC_PRIVATE, 2, IPC_CREAT|0666);
    if (S<0) {
        perror("semget()");
        return -1;
    }
    arg.val = 1;
    semctl(S, 0, SETVAL, arg);
    arg.val = 1;
    semctl(S, 1, SETVAL, arg);
    pid_t readbuf, writebuf;
    while ((readbuf = fork()) == -1);
    if (readbuf) {//不在readbuf进程
        while ((writebuf = fork()) == -1);
        if(writebuf){//在父进程
            par_task();
        }
        else {//在writebuf进程
            write_task();
        }
    }
    else {
        read_task();
    }
}
void par_task() {
    waitpid(readbuf, NULL, 0);
    waitpid(writebuf, NULL, 0);
    semctl(S, 2, IPC_RMID, arg);
    shmctl(shmid, IPC_RMID, NULL)
}
void read_task(){
    shmaddr1 = shmat(shmid, NULL, 0);//连接共享内存
    fp1 = fopen ("exp3.c","r");
    if (fp1!=NULL)
    {

        fclose (fp1);
    }
    shmdt(shmaddr1);//断开共享内存
}
void write_task(){
    shmaddr2 = shmat(shmid, NULL, SHM_RDONLY);
    fp2 = fopen("test.c","w");
    if (fp2!=NULL) {

        fclose(fp2);
    }
    shmdt(shmaddr2);
}
