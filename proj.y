%token INT ID REAL BOOL INT_T REAL_T LIST_T S_COL BOOL_T
%token NOT REF IF THEN ELSE WHILE DO HD TL VAL
%token LPAR RPAR LBRK RBRK NIL COL COM END FUN IN LET 
%left  PLUS MINUS MULT DIV EQ GT LT GEQ LEQ NEQ AND NOT OR DREF MOD INTDIV
%right L_CC ASSIGN NEG

%{
 /* put your c declarations here */
 
#include <stdio.h>
#include <iostream>
#include "operator.hpp"
#include "ast.hpp"
#define YYDEBUG 1
#define YYSTYPE int
extern int yylineno;
extern char* yytext;
%}

%%
start :
            exp S_COL start {std::cout << $1.add_parent_right(SEMICOLON, $3).to_string();}
          | epsilon
exp :
            if      {$$ = $1}
          | while   {$$ = $1}
          | let     {$$ = $1}
          | fundec  {$$ = $1}
          | or      {$$ = $1}
          | dec     {$$ = $1}
          | assign  {$$ = $1}
          
/* expressions */
or :
            and OR or
          | and
and :
            comp AND and
          | comp
comp :
            concat comp_op comp
          | concat
concat :
            add L_CC concat
          | add
add :
            mult add_op add
          | mult
mult :
            paren mult_op mult
          | paren
paren :
            LPAR repexp RPAR
          | val
val :
            id_d
          | INT
          | REAL
          | NEG INT
          | NEG REAL
          | BOOL
          | fun_call
          | list
list :
            LBRK exp elements RBRK
          | LBRK RBRK
          | NIL
fun_call :
            id val
          | id tuple
          | id_d val
          | id_d tuple
id :
            HD
          | DREF
          | NOT
          | TL
          | REF

id_d:   ID

tuple :
            LPAR repexp elements RPAR
          | LPAR RPAR
elements :
            COM repexp elements
          | epsilon
          
/* block */
assign :    
            id_d ASSIGN exp
if :
            IF exp THEN exp  ELSE exp
while :
            WHILE exp DO exp
let :
            LET repexp IN repexp END
repexp :
            exp S_COL repexp
          | exp
          | exp S_COL
dec :
            VAL id_d tvar EQ exp

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
            FUN id_d funargs EQ exp
funargs :
            LPAR decargs RPAR
          | LPAR RPAR
          | argdef
decargs :
            argdef COM decargs
          | argdef
argdef :    
            id_d tvar
            
/* misc //may need to insert into parent rules to simplify type checking.*/
comp_op :
          EQ | LT
        | GT | GEQ
        | LEQ | NEQ
add_op :
          PLUS | MINUS
mult_op : 
          MULT | DIV
        | INTDIV | MOD
epsilon : /* epsilon */
%%

    #include "./lex.yy.c"
