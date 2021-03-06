;模块二，编写者：许荣仁，同组学生：徐飞鸿
PUBLIC FUNCTION3,FUNCTION4
.386
STACK SEGMENT USE16 PARA STACK'STACK'
	DB 200 DUP(0)
STACK ENDS
PRINTF MACRO STR1;9号功能调用输出字符串
	PUSH DX
	PUSH AX
	LEA DX,STR1
	MOV AH,9
	INT 21H
	POP AX
	POP DX
	ENDM

SCANF MACRO STR2;10号功能调用输入字符串
	PUSH DX
	PUSH AX
	LEA DX,STR2
	MOV AH,10
	INT 21H
	POP AX
	POP DX
	ENDM

DATA SEGMENT PARA PUBLIC USE16 'DATA'
SORTU DB 0,1,2;,3,4,5,6,7,8,9排序用的数组
TEMP DB 0;F2T10数字转字符要用
CHU100 DB 100;100作除数
CHU10 DB 10;10作除数
OLIST DB 0AH,0DH,'NAME     MATH    CHINESE ENGLISH AVERAGE$'
DATA ENDS
CODE1 SEGMENT USE16 PARA PUBLIC'C1'
		ASSUME CS:CODE1,DS:DATA,SS:STACK
;功能3成绩排序
;入口参数：第一个学生的偏移地址--SI，学生个数--EBX
;出口参数：无
FUNCTION3 PROC FAR
	PUSH DX
	PUSH EBP
	PUSH ESP
	PUSH EDI
	ADD SI,13;第一个学生的平均分地址
	MOV ECX,0
LOOP4:
	MOV SORTU[ECX],CL
	INC ECX
	CMP ECX,EBX
	JNZ LOOP4
	MOV ECX,0
LOOPA:
	CMP ECX,EBX
	JZ FINISH
	MOV EDX,ECX
	MOV AH,[SI]
	MOV DI,SI
	ADD DI,14
	LOOPB:
		INC EDX
		CMP EDX,EBX
		JNB FINISHS;循环结束
		MOV AL,[DI]
		CMP AH,AL
		JB NSWAP;不交换
		PUSH AX
		MOV AL,[EDX+SORTU]
		MOV AH,[ECX+SORTU]
		MOV [ECX+SORTU],AL
		MOV [EDX+SORTU],AH
		POP AX
	NSWAP:
		ADD DI,14
		JMP LOOPB
	FINISHS:
	INC ECX
	ADD SI,14
	JMP LOOPA
FINISH:
	POP EDI
	POP ESP
	POP EBP
	POP DX
	RET
FUNCTION3 ENDP
;功能4输出成绩单
;入口参数：第一个学生的偏移地址--BP，学生个数--CX，排序数组首址--SORTU
;出口参数：无
FUNCTION4 PROC FAR
	PUSH AX
	PUSH BX
	PUSH DX
	PUSH ESI
	LEA SI,OLIST
	PRINTF [SI]
LOOP3:
	CMP CX,0
	JNA FINISH1;结束打印
	DEC CX
	MOV DX,0
	MOV DL,[ECX+SORTU]
	IMUL DX,14
	MOV SI,BP
	ADD SI,DX

	MOV DL,0AH
	MOV AH,2
	INT 21H
	MOV DL,0DH
	MOV AH,2
	INT 21H
	PRINTF [SI]
	ADD SI,10
	MOV BL,[SI]
	MOV BH,0
	CALL F2T10
	ADD SI,1
	MOV BL,[SI]
	MOV BH,0
	CALL F2T10
	ADD SI,1
	MOV BL,[SI]
	MOV BH,0
	CALL F2T10
	ADD SI,1
	MOV BL,[SI]
	MOV BH,0
	CALL F2T10
	JMP LOOP3
FINISH1:
	POP ESI
	POP DX
	POP BX
	POP AX
	RET
FUNCTION4 ENDP

;功能：字节型数字转为十进制字符串并显示
;入口参数：字节型数字--BX
;出口参数：无
F2T10 PROC FAR
	PUSH ESI
	PUSH EDI
	PUSH AX
	PUSH DX
	MOV AX,BX
	DIV CHU100
	MOV TEMP,AL
	XCHG AL,AH
	ADD TEMP,'0'
	MOV DL,TEMP
	MOV AH,2
	INT 21H
	MOV AH,0
	DIV CHU10
	MOV TEMP,AL
	XCHG AL,AH
	ADD TEMP,'0'
	MOV DL,TEMP
	MOV AH,2
	INT 21H
	MOV TEMP,AL
	ADD TEMP,'0'
	MOV DL,TEMP
	MOV AH,2
	INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	POP DX
	POP AX
	POP EDI
	POP ESI
	RET
F2T10 ENDP
CODE1 ENDS
	END