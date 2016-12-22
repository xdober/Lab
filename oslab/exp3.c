#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
FILE* fp1, *fp2;
char *shmaddr1,*shmaddr2;
int *cout1,*cout2;
int shmid,global_var;//共享内存
int S;//信号灯
int Sv;//全局变量的信号灯
pid_t readbuf, writebuf;
void par_task(int shmid,int global_var,int S,int Sv) {
    waitpid(readbuf, NULL, 0);
    waitpid(writebuf, NULL, 0);
    semctl(S, 0, IPC_RMID, arg);
    semctl(S, 1, IPC_RMID, arg);
    semctl(Sv,0,IPC_RMID,arg);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(global_var,IPC_RMID,NULL);
}
void read_task(){
//    printf("\t\t\t\t\tread_task is processing!\n");
    shmaddr1 = shmat(shmid, NULL, 0);//连接共享内存
    cout1 = shmat(global_var,NULL,0);
    P(Sv,0);
    *cout1 = 0;
    *(cout1+8)=64;//最后一次从文件读到的内存大小，初始值设为64
    V(Sv,0);
    fp1 = fopen ("20161201190944.png","r");
    if (fp1!=NULL)
    {
        int i = 0,j=64;
        while (j==64) {
            P(S,0);//空个数
            j = fread(shmaddr1+i,1,64,fp1);
            V(S,1);//满个数
            if (j!=64) {
                P(Sv,0);
                //*cout1-=0;
                *(cout1+8)=j;//最后一次从文件读到的内存大小
                V(Sv,0);
//                printf("%d\n", j);
                break;
            }
//            printf("\t\t\t\tread:%d\n", i/64);
            i+=64;
            i=i%1024;
            P(Sv,0);
            (*cout1)++;
//            printf("\tcout1:%d\n", *cout1);
            V(Sv,0);
        }
        fclose (fp1);
    }
    shmdt(shmaddr1);//断开共享内存
    shmdt(cout1);
}
void write_task(){
//    printf("\t\t\t\t\twrite_task is processing!\n");
    shmaddr2 = shmat(shmid, NULL, SHM_RDONLY);//连接共享内存
    cout2 = shmat(global_var,NULL,0);//全局变量地址
    P(Sv,0);
    *(cout2+8)=64;
    V(Sv,0);
    fp2 = fopen("new.png","w");
    if (fp2!=NULL) {
        int i = 0,count2=0,j=64,count0;
    //    P(Sv,0);
    //    j=*cout2;
    //    V(Sv,0);
        while (j==64||count2<count0) {//只有上一次写到缓冲区的内存个数不足64并且写到文件的次数不小于从文件读取的次数时才是最后一次写操作
            P(S,1);
            //printf("%s\n",shmaddr2+i);
            fwrite(shmaddr2+i,1,64,fp2);
            V(S,0);
//            printf("write:%d\n", i/64);
            i=i+64;
            i=i%1024;
            count2++;
//            printf("\t\t\tcount2:%d\n", count2);
            P(Sv,0);
            j=*(cout2+8);//上一次从文件读到的内存个数
            count0=*cout2;//已经从文件读到缓冲区的次数
//            printf("\t\tcout2:%d\n", j);
            V(Sv,0);
        }
        fwrite(shmaddr2+i,1,*(cout2+8),fp2);//最后一次写操作，读到缓冲区几个内存大小就写到文件几个内存大小
//        printf("%d\n", *(cout2+8));
        fclose(fp2);
    }
    shmdt(shmaddr2);
    shmdt(cout2);
}

int main() {
    shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT|IPC_EXCL|0660);//创建共享内存
    global_var = shmget(IPC_PRIVATE,256,IPC_CREAT|IPC_EXCL|0660);//全局变量
    if (shmid == -1) {
        perror("shmget()");
    }
    S = semget(IPC_PRIVATE, 2, IPC_CREAT|0666);
    if (S<0) {
        perror("semget()");
        return -1;
    }
    arg.val = 16;//设置信号灯
    semctl(S, 0, SETVAL, arg);
    arg.val = 0;
    semctl(S, 1, SETVAL, arg);
    Sv = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);//全局变量的信号灯
    if (Sv<0) {
        perror("semget()");
        return -1;
    }
    arg.val = 1;//设置信号灯
    semctl(Sv, 0, SETVAL, arg);
    while ((readbuf = fork()) == -1);
    if (readbuf) {//不在readbuf进程
        while ((writebuf = fork()) == -1);
        if(writebuf){//在父进程
            par_task(shmid,global_var,S,Sv);
        }
        if(!writebuf) {//在writebuf进程
//            printf("\t\t\t\t\twrite_task is called!\n");
            write_task();
        }
    }
    if(!readbuf) {
//        printf("\t\t\t\t\tread_task is processing!\n");
        read_task();
    }
}
