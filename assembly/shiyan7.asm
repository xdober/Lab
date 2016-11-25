.386
STACK SEGMENT USE16 STACK
	DB 200 DUP(0)
STACK ENDS
DATA SEGMENT USE16
N EQU 3
BNB DB 7
BUF DB 'X' XOR 'X','u' XOR 'N','r' XOR 'B','r' XOR 'X',6 DUP(0)
	DB 100 XOR 'X',85 XOR 'N',80 XOR 'B',?
	DB 'L' XOR 'X','I' XOR 'N','S' XOR 'B','I' XOR 'X',6 DUP(0)
	DB 80 XOR 'X',100 XOR 'N',70 XOR 'B',?
	DB 'W' XOR 'X','A' XOR 'N','N' XOR 'B','G' XOR 'X','W' XOR 'N','U' XOR 'B',0,0,0,0
	DB 85 XOR 'X',85 XOR 'N',100 XOR 'B',?
POIN DW 0
OUPUT DB 0AH,0DH,'Please input student name:$'
TIP1 DB 'Please input password:$'
UNFND DB 0AH,0DH,'Student not found!',0AH,0DH,'$'
PWD DB 3 XOR 'A'
	DB 'X' XOR 'M','N' XOR 'C','B' XOR 'B'
	DB 17H,4DH,8AH
IPWD DB 7
	DB ?
	DB 7 DUP(0)
INAME DB 10
	DB ?
NAMM	DB 10 DUP(0)
OLDINT1 DW  0,0               ;1号中断的原中断矢量（用于中断矢量表反跟踪）
OLDINT3 DW  0,0               ;3号中断的原中断矢量

DATA ENDS

CODE SEGMENT USE16
		ASSUME CS:CODE,DS:DATA,SS:STACK
START:	MOV AX,DATA
		MOV DS,AX
       xor  ax,ax                  ;接管调试用中断，中断矢量表反跟踪
       mov  es,ax
       mov  ax,es:[1*4]            ;保存原1号和3号中断矢量
       mov  OLDINT1,ax
       mov  ax,es:[1*4+2]
       mov  OLDINT1+2,ax
       mov  ax,es:[3*4]
       mov  OLDINT3,ax
       mov  ax,es:[3*4+2]
       mov  OLDINT3+2,ax
       cli                           ;设置新的中断矢量
       mov  ax,OFFSET NEWINT
       mov  es:[1*4],ax
       mov  es:[1*4+2],cs
       mov  es:[3*4],ax
       mov  es:[3*4+2],cs
       sti

		LEA DX,TIP1;提示输入密码
		MOV AH,9
			INT 21H
		LEA DX,IPWD;输入密码
		MOV AH,10
			INT 21H

	PASS2:
		XOR ESI,ESI;比较密码是否相同
		MOV EAX,DWORD PTR IPWD[SI+2]
		XOR EAX,'SBCM'
		AND EAX,00FFFFFFH
		OR EAX,17000000H
		CMP EAX,DWORD PTR PWD+1
		JNZ EXIT
		ADD SI,4
		MOV AX,WORD PTR IPWD[SI+2];干扰
		XOR AX,'FV';干扰
PASS3: mov  bx,es:[1*4]             ;检查中断矢量表是否被调试工具阻止修改或恢复
       inc  bx
       jmp  bx                 ;正常修改了的话，这里将转移到TESTINT，否则就不知道转到哪了

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

		MOV CX,9
		MOV SI,0
		MOV DI,0;把输入的姓名加密
	NEXXT:
		MOV AL,NAMM[SI]
		XOR AL,IPWD[DI+2]
		MOV NAMM[SI],AL
		INC SI
		MOV AX,SI
		DIV IPWD+1
		MOVZX DI,AH
		MOV BX,0
		MOV BL,INAME+1
		CMP SI,BX
		JNZ NEXXT
		MOV NAMM[EBX],0
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
		XOR AL,IPWD[2];解密
		SAL EAX,1
		MOV EDX,EAX
		MOV EAX,0
		MOV AL,BYTE PTR 11[ESI]
		XOR AL,IPWD[3];解密
		ADD EDX,EAX
		MOV EAX,0
		MOV AL,BYTE PTR 12[ESI]
		XOR AL,IPWD[4];解密
		SAR EAX,1
		ADD EDX,EAX
		SAL EDX,1
		MOV EAX,EDX
		MOV EDX,0
		DIV BNB
		MOV 13[ESI],AL
		ADD ESI,14
		MOV EAX,0
		DEC CX
		JNZ GNT

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
NEWINT: iret
TESTINT: jmp INPUT
  
EXIT:
       cli                           ;还原中断矢量
       mov  ax,OLDINT1
       mov  es:[1*4],ax
       mov  ax,OLDINT1+2
       mov  es:[1*4+2],ax
       mov  ax,OLDINT3
       mov  es:[3*4],ax
       mov  ax,OLDINT3+2
       mov  es:[3*4+2],ax 
       sti

			MOV AH,4CH
			INT 21H
CODE ENDS
	END START