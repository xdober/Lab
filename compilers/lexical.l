digit [0-9]
intnumber [+-]?{digit}+
floatnum [+-]?{digit}+\.{digit}*|[+-]?{digit}*\.{digit}+
letter [a-zA-Z]
identifier ({letter}|_)({digit}|{letter}|_)*
blank [\t\x0B\f\r\x20]+
notes (/\*)([.|\n])*(\*/)
error1 {digit}+_({letter}|{digit}|_)*

%%
"notes" { printf(" "); }
\n { printf("\n"); }
{error1} { printf("e_r_r_o_r"); }

int|float { printf("TYPE"); }
"if" { printf("IF"); }
"else" { printf("ELSE"); }
"while" { printf("WHILE"); }
"struct" { printf("STRUCT"); }
"return" { printf("RETURN"); }


"(" { printf("LB "); }
")" { printf("RB "); }
"[" { printf("LF "); }
"]" { printf("RF "); }
"{" { printf("LD"); }
"}" { printf("RD"); }
";" { printf("FH"); }
"," { printf("DH"); }

"." { printf("DOT "); }
"-" { printf("SU "); }
"!" { printf("NT "); }
"*" { printf("MU "); }
"/" { printf("DI "); }
"+" { printf("AD "); }
>|<|<=|>=|==|!= { printf("RELOP"); }
"&&" { printf("AND "); }
"||" { printf("OR "); }
"=" { printf("AS "); }

{blank} { printf(" "); }
{identifier} { printf("identifier"); }
{floatnum} { printf("floatnum"); }
{intnumber} { printf("intnumber"); }

. { printf("Error type A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext); }

%%
int main(int argc,char** argv) {
	if(argc>1) {
		if(!(yyin=fopen(argv[1],"r"))) {
         			perror(argv[1]);
         			return 1;
		}
	}
	while(yylex()!=0);
	return 0;
}