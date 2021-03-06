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
Student allStu[N];
char bufName[10];
char flag;
char jpoin;
char bnb=7;
void InitStudent();
int main(){
	int i;
	InitStudent();
	printf("Please input student name:");
	scanf("%s",bufName);
	getchar();
	if ('q'==bufName[0]){
		return 0;
	}
	_asm{
		mov ecx,N
		mov ebx,0
	loop2:
		mov esi,0
	loop1:
		mov al,bufName[esi]
		cmp al,allStu[ebx][esi]
		jnz loop3
		inc esi
		cmp esi,10
		jz savep
		jmp loop1
	loop3:
		add ebx,14
		dec ecx
		cmp ecx,0
		jz nfd
		jmp loop2
	nfd:
		mov flag,byte ptr 0
		jmp eend
	savep:
		mov flag,byte ptr 1
		mov jpoin,cl
		mov ebx,0
	eend:
	}
	if(!flag){
		printf("Student Not Found!\n");
	}
	else{
		_asm{
			mov esi,offset allStu
			mov ecx,N
			mov eax,0
		gnt:
			mov al,10[esi]
			sal eax,2
			mov edx,0
			mov dl,11[esi]
			sal edx,1
			add edx,eax
			mov eax,0
			mov al,12[esi]
			add eax,edx
			mov edx,0
			div bnb
			mov 13[esi],al
			add esi,14
			mov eax,0
			dec ecx
			jnz gnt
		}
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
