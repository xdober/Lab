#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <wait.h>
int wait_mark = 1;
int pipfd[2];
char string[100],readbuffer[100];
int x = 1;//记录次数
void waiting1();
void waiting2();
void waiting();
void stop();

int main(void) {
	pipe(pipfd);//建立管道
	pid_t childpid1,childpid2;
	while((childpid1 = fork()) == -1);//创建子进程1
	if(childpid1) {//在父进程中
		while((childpid2 = fork()) == -1);//创建子进程2
		signal(SIGINT,stop);
		waiting();
		kill(childpid1,16);
		kill(childpid2,16);
		wait(0);
		wait(0);
		printf("Parent Process is killed!\n");
		exit(0);
	}
	if(!childpid1) {//在子进程1中
		signal(16,stop);
		signal(SIGINT,SIG_IGN);
		waiting1();
		printf("Child Process1 is killed by Parent!\n");
		exit(0);
	}
	if(!childpid2) {//在子进程2中
		signal(16,stop);
		signal(SIGINT,SIG_IGN);
		waiting2();
		printf("Child Process2 is killed by Parent!\n");
		exit(0);
	}
}
void waiting1(){
	while(wait_mark) {
		sprintf(string,"I send you %d times.\n",x++);
		close(pipfd[0]);//关闭读端口
		write(pipfd[1], string, (strlen(string)+1));//发送信息
		sleep(1);
	}
}

void waiting2() {
	sleep(0.9);
	while(wait_mark) {
		close(pipfd[1]);//关闭写端口
		read(pipfd[0],readbuffer,sizeof(readbuffer));
		printf("%s",readbuffer);
		sleep(1);
	}	
}

void waiting() {
	while(wait_mark) 
		;
}
void stop() {
	wait_mark = 0;
}
