FUNCTION	main	:
a	:=	#0	
b	:=	#3	
READ	n	
IF	n	>	#0	GOTO	label1	
GOTO	label2	
LABEL	label1	:	
a	:=	#1	
GOTO	label3	
LABEL	label2	:	
IF	n	<	#0	GOTO	label4	
GOTO	label5	
LABEL	label4	:	
a	:=	#2	*	b	
GOTO	label6	
LABEL	label5	:	
a	:=	b	+	#3	
LABEL	label6	:	
LABEL	label3	:	
IF	a	==	b	GOTO	label7	
GOTO	label9	
LABEL	label9	:	
IF	b	!=	n	GOTO	label7	
GOTO	label8	
LABEL	label7	:	
b	:=	#5	
GOTO	label10	
LABEL	label8	:	
b	:=	b	+	#1	
LABEL	label10	:	
RETURN	#0	
