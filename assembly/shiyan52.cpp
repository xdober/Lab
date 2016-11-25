#include <stdio.h>
#include <string.h>
#define N 10
typedef struct Student{
	char name[10];
	char math;
	char chinese;
	char english;
	char average;
}Student,*student;
extern "C" void JudStu(Student * , int , char * );
extern "C" void CalAve(Student * , int );
Student allStu[N];
char bufName[10];
int flag=1;
int jpoin;
void InitStudent();
int main(){
	int i;
	InitStudent();
	printf("Please input student name:");
	scanf("%s",bufName);
	getchar();
	if('q'==bufName[0]){
		return 0;
	}
	JudStu(allStu , N , bufName);
	_asm{
		mov jpoin,ecx
	}
	if(!jpoin){
		flag=0;
	}
	if(!flag){
		printf("Student Not Found!\n");
	}
	else{
		CalAve(allStu , N );
		jpoin=N-jpoin;
		if(allStu[jpoin].average>=90){
			printf("A\n");
		}else if(allStu[jpoin].average>=80){
			printf("B\n");
		}else if (allStu[jpoin].average>=70)
		{
			printf("C\n");
		}else if (allStu[jpoin].average>=60)
		{
			printf("\n");
		}else printf("E\n");
	}
	return 0;
}	
void InitStudent(){
	int i;
	strcpy(allStu[0].name,"zhangsan");
	allStu[0].math=100;
	allStu[0].chinese=85;
	allStu[0].english=80;

	strcpy(allStu[1].name,"lisi");
	allStu[1].math=80;
	allStu[1].chinese=100;
	allStu[1].english=70;

	for(i=2;i<9;i++){	
		strcpy(allStu[i].name,"TempValue");
		allStu[i].math=0;
		allStu[i].chinese=0;
		allStu[i].english=0;
	}

	strcpy(allStu[9].name,"wangwu");
	allStu[9].math=85;
	allStu[9].chinese=85;
	allStu[9].english=100;
}
