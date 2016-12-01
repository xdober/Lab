#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <wait.h>
int wait_mark = 1;
int pipfd[2];
pid_t childpid1,childpid2;
char string[40],readbuffer[40];
int x = 1;//记录次数
void par_sig();
void fa();
void chi1_sig();
void chi2_sig();
void stop1();
void stop2();

int main(void) {
	pipe(pipfd);//建立管道
	while((childpid1 = fork()) == -1);//创建子进程1
	if(childpid1) {//不在子进程1
		while((childpid2 = fork()) == -1);//创建子进程2
		if(childpid2) {//在父进程
			par_sig();
		}
		if(!childpid2) {//在子进程2
			chi2_sig();
		}
	}
	if(!childpid1){//在子进程1
		chi1_sig();
	}
}
void par_sig() {
	signal(SIGINT,fa);
	while(1);
}
void fa()  {
	kill(childpid1,16);
	kill(childpid2,16);
	waitpid(childpid1,NULL,0);
	waitpid(childpid2,NULL,0);
	printf("\nParent Process is killed!\n");
	exit(0);
}
void chi1_sig() {
	signal(SIGINT,SIG_IGN);//设置忽略信号
	signal(16,stop1);
	while(1) {
		sprintf(string,"I send you %d times.\n",x++);
		close(pipfd[0]);//关闭读端口
		write(pipfd[1], string, (strlen(string)+1));//发送信息
		sleep(1);
	}

}
void chi2_sig() {
	signal(SIGINT,SIG_IGN);
	signal(16,stop2);
	while(1) {
		close(pipfd[1]);//关闭写端口
		read(pipfd[0],readbuffer,sizeof(readbuffer));
		printf("%s",readbuffer);
		sleep(1);
	}
}
void stop1() {//显示退出信息
	printf("\nChild Process1 is killed by Parent!");
	exit(0);
}
void stop2() {
	printf("\nChild Process2 is killed by Parent!");
	exit(0);
}
