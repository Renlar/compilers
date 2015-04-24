%token INT ID REAL BOOL INT_T REAL_T LIST_T S_COL BOOL_T
%token DREF NOT REF IF THEN ELSE WHILE DO HD TL VAL
%token LPAR RPAR LBRK RBRK NIL COL COM END FUN IN LET 
%left  PLUS MINUS MULT DIV EQ GT LT GEQ LEQ NEQ AND NOT OR DREF MOD INTDIV
%right L_CC ASSIGN NEG

%{
 /* put your c declarations here */
 
#include <stdio.h>
#include "lib/typecheck.h"

#define YYDEBUG 1
#define YYSTYPE Anom
extern int yylineno;
extern char* yytext;
/*void yyerror(const char* msg)
{
  char *p;
  fprintf(stderr, "Line %d : %s : %s \n",yylineno,msg, yytext);
}*/
%}

%%
start :
            exp S_COL start
          | epsilon
exp :
            if      {$$ = $1;}
          | while   {$$ = $1;}
          | let     {$$ = $1;}
          | fundec  {$$ = $1;}
          | or      {$$ = $1;}
          | dec     {$$ = $1;}
          | assign  {$$ = $1;}
/* expressions */
or :
            and OR or
          | and       {$$ = $1;}
and :
            comp AND and
          | comp      {$$ = $1;}
comp :
            concat comp_op comp
          | concat    {$$ = $1;}
concat :    
            add L_CC concat
          | add       {$$ = $1;}
add :       
            mult add_op add
          | mult      {$$ = $1;}
mult :      
            paren mult_op mult
          | paren     {$$ = $1;}
paren :     
            LPAR repexp RPAR
          | list      {$$ = $1;}
list :      
            LBRK elements RBRK
          | LBRK RBRK
          | NIL
          | val
val :       
            ID        {$$ = var_type(get_var(yytext));}
          | INT       {$$ = type_new(T_INT, NULL);}
          | REAL      {$$ = type_new(T_REAL, NULL);}
          | NEG INT   {$$ = type_new(T_INT, NULL);}
          | NEG REAL  {$$ = type_new(T_REAL, NULL);}
          | BOOL      {$$ = type_new(T_BOOL, NULL);}
          | fun_call  {$$ = $1;}
fun_call :  
            id tuple 
          | id exp
          | ID tuple
          | ID exp 
id :        
            HD
          | DREF
          | NOT
          | TL
          | REF
tuple :     
            LPAR elements RPAR
          | LPAR RPAR
elements :  
            and COM elements
          | and
/* block */
assign :    
            ID ASSIGN exp
if :        
            IF exp THEN exp ELSE exp
while :     
            WHILE exp DO exp
let :       
            LET repexp IN repexp END
repexp :    
            exp S_COL repexp
          | exp
          | exp S_COL
dec :       
            VAL ID tvar EQ exp
/*types*/
tvar :      
            COL type
          | epsilon
type :      
            basictype listtype
          | basictype
          | listtype
basictype : 
            REAL_T ref
          | INT_T ref
          | BOOL_T ref
listtype :  
            LIST_T ref listtype
          | LIST_T ref
ref :       
            REF ref
          | epsilon
/* functions */
fundec :    
            FUN ID funargs EQ exp
funargs :   
            LPAR decargs RPAR
          | LPAR RPAR
          | argdef
decargs :   
            argdef COM decargs
          | argdef
argdef :    
            ID tvar
/* misc //may need to insert into parent rules to simplify type checking.*/
comp_op : EQ | LT | GT | GEQ | LEQ | NEQ 
add_op : PLUS | MINUS
mult_op : MULT | DIV | INTDIV | MOD
epsilon : /* epsilon */
%%

    #include "./lex.yy.c"
