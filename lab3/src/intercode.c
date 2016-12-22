#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"intercode.h"

InterCode code_h=NULL;
InterCode code_t=NULL;

int varCount=1;
int labCount=1;



void insertCode(InterCode c)
{
	c->pre=NULL;
	c->next=NULL;
	if(code_h==NULL)
	{
		code_h=c;
		code_t=c;
	}
	else
	{
		c->pre=code_t;
		code_t->next=c;
		code_t=c;
	}
}

//print code in file
void printCode(char* fname)
{
	FILE *fp=fopen(fname,"w");
	if(fp==NULL)
	{
		printf("open file error\n");
		return;
	}
	InterCode c=code_h;
	while(c!=NULL)
	{
		switch(c->kind)
		{
			case ASSIGN_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	",fp);
				printOp(c->u.assign.right,fp);
				break;
			case ADD_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("+	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case SUB_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("-	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case MUL_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("*	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case DIV_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("/	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case RETURN_K:
				fputs("RETURN	",fp);
				printOp(c->u.one.op,fp);
				break;
			case LABEL_K:
				fputs("LABEL	",fp);
				printOp(c->u.one.op,fp);
				fputs(":	",fp);
				break;
			case GOTO_K:
				fputs("GOTO	",fp);
				printOp(c->u.one.op,fp);
				break;
			case IFGOTO_K:
				fputs("IF	",fp);
				printOp(c->u.triop.t1,fp);
				fputs(c->u.triop.op,fp);
				fputs("	",fp);
				printOp(c->u.triop.t2,fp);
				fputs("GOTO	",fp);
				printOp(c->u.triop.label,fp);
				break;
			case READ_K:
				fputs("READ	",fp);
				printOp(c->u.one.op,fp);
				break;
			case WRITE_K:
				fputs("WRITE	",fp);
				printOp(c->u.one.op,fp);
				break;
			case CALL_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	CALL	",fp);
				printOp(c->u.assign.right,fp);
				break;
			case ARG_K:
				fputs("ARG	",fp);
				printOp(c->u.one.op,fp);
				break;
			case FUNCTION_K:
				fputs("FUNCTION	",fp);
				printOp(c->u.one.op,fp);
				fputs(":",fp);
				break;
			case PARAM_K:
				fputs("PARAM	",fp);
				printOp(c->u.one.op,fp);
				break;
			case RIGHTAT_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	&",fp);
				printOp(c->u.assign.right,fp);
				break;
			case DEC_K:
				fputs("DEC	",fp);
				printOp(c->u.dec.op,fp);
				char size[32];
				sprintf(size,"%d",c->u.dec.size);
				fputs(size,fp);
				break;
		}
		fputs("\n",fp);
		c=c->next;
	}
	fclose(fp);
}

void printOp(Operand op,FILE* fp)
{
	if(op==NULL)
	{
		fputs("t0	",fp);//t0 is use less but can avoid some error
		return;
	}

	char var[32];
	memset(var,0,sizeof(var));
	switch(op->kind)
	{
		case TEMPVAR:
			fputs("t",fp);
			sprintf(var,"%d",op->u.var_no);
			fputs(var,fp);
			break;
		case VARIABLE:
			fputs(op->u.value,fp);
			break;
		case CONSTANT:
			fputs("#",fp);
			fputs(op->u.value,fp);
			break;
		case LABEL:
			fputs("label",fp);
			sprintf(var,"%d",op->u.var_no);
			fputs(var,fp);
			break;
		case FUNCTION:
			fputs(op->u.value,fp);
			break;
		case TADDRESS: fputs("*t",fp);
			sprintf(var,"%d",op->u.name->u.var_no);
			fputs(var,fp);
			break;
		case VADDRESS:
			fputs("*",fp);
			fputs(op->u.name->u.value,fp);
			break;
	}
	fputs("	",fp);
}


