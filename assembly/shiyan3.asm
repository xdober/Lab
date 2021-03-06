.386
STACK SEGMENT USE16 STACK
	DB 200 DUP(0)
STACK ENDS
DATA SEGMENT USE16
N EQU 100
BNB DB 7
BUF DB 'ZHANGSAN',0,0
	DB 100,85,80,?
	DB 'LISI',6 DUP(0)
	DB 80,100,70,?
	DB N-3 DUP('TempValue',0,80,90,95,?)
	DB 'WANGWU',0,0,0,0
	DB 85,85,100,?
POIN DW 0
OUPUT DB 0AH,0DH,'Please input student name:$'
UNFND DB 0AH,0DH,'Student not found!$'
INAME DB 10
	DB ?
NAMM	DB 10 DUP(0)
PAN DD 0
BBB DB 2
DATA ENDS

CODE SEGMENT USE16
		ASSUME CS:CODE,DS:DATA,SS:STACK
START:	MOV AX,DATA
		MOV DS,AX
INPUT:	MOV CX,10
		MOV BX,0
LLL:	MOV NAMM[BX],0
		INC BX
		DEC CX
		JNZ LLL
		MOV ECX,0
		MOV EBX,0
		MOV EDX,0
		MOV EAX,0
		LEA DX,OUPUT;功能1提示并输入学生姓名
		MOV AH,9
			INT 21H
		LEA DX,INAME
		MOV AH,10
			INT 21H
		CMP NAMM,13;输入了回车
		JZ INPUT
		MOV CL,INAME+1
		MOV NAMM[ECX],0
		CMP NAMM,'q';输入了q
		JZ EXIT

		MOV DL,10
		MOV AH,2
		INT 21H
		MOV DL,13
		MOV AH,2
		INT 21H
		CALL disptime
		MOV PAN,DWORD PTR 10000

LOOO:		
		MOV CX,N;功能2查找学生
		MOV EBX,0
LOOP2:	MOV ESI,0;0~10,循环把姓名中的每个字符放入AL
LOOP1:	MOV AL,NAMM[ESI]
		CMP AL,BUF[EBX][ESI]
		JNZ LOOP3
		INC SI
		CMP SI,10
		JZ SAVEP;保存起始地址
		JMP LOOP1
LOOP3:	ADD EBX,14
		DEC CX
		CMP CX,0
		JZ NFD;未找到学生结束循环
		JMP LOOP2
NFD:	LEA DX,UNFND
		MOV AH,9
			INT 21H
		JMP INPUT;回到功能1
SAVEP:	MOV POIN,BX
		MOV EBX,0
		ADD POIN,OFFSET BUF
		
		MOV ESI,OFFSET BUF;功能3计算平均成绩
		MOV CX,N
		MOV EAX,0
GNT:	MOV AL,BYTE PTR 10[ESI]
		IMUL EAX,2
		MOV EDX,EAX
		MOV EAX,0
		MOV AL,BYTE PTR 11[ESI]
		ADD EDX,EAX
		MOV EAX,0
		MOV AL,BYTE PTR 12[ESI]
		DIV BBB
		ADD EDX,EAX
		IMUL EDX,2
		MOV EAX,EDX
		MOV EDX,0
		DIV BNB
		MOV 13[ESI],AL
		ADD ESI,14
		MOV EAX,0
		DEC CX
		JNZ GNT

		DEC PAN
		JNZ LOOO

		CALL disptime

		MOV DL,10;功能4判定等级
		MOV AH,2
		INT 21H
		MOV DL,13
		MOV AH,2
		INT 21H
		MOV EAX,0
		MOV AX,POIN
		MOV SI,AX
		MOV EAX,0
		MOV AL,13[SI]
		CMP AL,90
		JNS PUTA
		CMP AL,80
		JNS PUTB
		CMP AL,70
		JNS PUTC
		CMP AL,60
		JNS PUTD
		JMP PUTE
PUTA:	MOV DL,'A'
		MOV AH,2
		INT 21H
		JMP INPUT
PUTB:	MOV DL,'B'
		MOV AH,2
		INT 21H
		JMP INPUT
PUTC:	MOV DL,'C'
		MOV AH,2
		INT 21H
		JMP INPUT
PUTD:	MOV DL,'D'
		MOV AH,2
		INT 21H
		JMP INPUT
PUTE:	MOV DL,'E'
		MOV AH,2
		INT 21H
		JMP INPUT

EXIT:		MOV AH,4CH
			INT 21H

disptime proc        ;显示秒和百分秒，精度为55ms。(未保护ax寄存器)
    local timestr[8]:byte     ;0,0,'"',0,0,0dh,0ah,'$'

         push cx
         push dx         
         push ds
         push ss
         pop  ds
         mov  ah,2ch 
         int  21h
         xor  ax,ax
         mov  al,dh
         mov  cl,10
         div  cl
         add  ax,3030h
         mov  word ptr timestr,ax
         mov  timestr+2,'"'
         xor  ax,ax
         mov  al,dl
         div  cl
         add  ax,3030h
         mov  word ptr timestr+3,ax
         mov  word ptr timestr+5,0a0dh
         mov  timestr+7,'$'    
         lea  dx,timestr  
         mov  ah,9
         int  21h    
         pop  ds 
         pop  dx
         pop  cx
         ret
disptime	endp
CODE ENDS
	END START