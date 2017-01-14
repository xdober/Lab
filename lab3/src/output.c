FUNCTION	add	:
PARAM	temp	
t5	:=	#0	*	#4	
t6	:=	temp	+	t5	
t10	:=	#1	*	#4	
t11	:=	temp	+	t10	
t1	:=	*t6	+	*t11	
RETURN	t1	
FUNCTION	main	:
DEC	t12	8
op	:=	&t12	
i	:=	#0	
j	:=	#0	
LABEL	label1	:	
IF	i	<	#2	GOTO	label2	
GOTO	label3	
LABEL	label2	:	
LABEL	label4	:	
IF	j	<	#2	GOTO	label5	
GOTO	label6	
LABEL	label5	:	
t20	:=	j	*	#4	
t21	:=	op	+	t20	
t22	:=	i	+	j	
*t21	:=	t22	
j	:=	j	+	#1	
GOTO	label4	
LABEL	label6	:	
i	:=	i	+	#1	
j	:=	#0	
GOTO	label1	
LABEL	label3	:	
RETURN	#0	
