%token INT ID REAL BOOL INT_T REAL_T LIST_T S_COL BOOL_T
%token NOT REF IF THEN ELSE WHILE DO HD TL VAL
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
extern str yytext;
%}

%%
start :
            {typecheck_init();} exp S_COL start {typecheck_destroy();}
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
            and OR or {$$ = typecheck_arith($1, OP_OR, $3, yylineno);}
          | and       {$$ = $1;}
and :
            comp AND and {$$ = typecheck_arith($1, OP_AND, $3, yylineno);}
          | comp      {$$ = $1;}
comp :
            concat comp_op comp {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | concat    {$$ = $1;}
concat :
            add L_CC concat {$$ = typecheck_concat($1, $3, yylineno);}
          | add       {$$ = $1;}
add :
            mult add_op add {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | mult      {$$ = $1;}
mult :
            paren mult_op mult {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | paren     {$$ = $1;}
paren :
            {push_scope("Begin paren");} LPAR repexp RPAR {pop_scope(); $$ = $2;}
          | val      {$$ = $1;}
val :
            id_d      {$$ = typecheck_id_access($1, yylineno);}
          | INT       {$$ = typecheck_const(T_INT, yylineno);}
          | REAL      {$$ = typecheck_const(T_REAL, yylineno);}
          | NEG INT   {$$ = typecheck_const(T_INT, yylineno);}
          | NEG REAL  {$$ = typecheck_const(T_REAL, yylineno);}
          | BOOL      {$$ = typecheck_const(T_BOOL, yylineno);}
          | fun_call  {$$ = $1;}
          | list      {$$ = $1;}
list :
            LBRK exp elements RBRK {$$ = typecheck_list(typecheck_elements($2, $3, yylineno), yylineno);}
          | LBRK RBRK {$$ = typecheck_list(NULL, yylineno);}
          | NIL {$$ = typecheck_list(NULL, yylineno);}
fun_call :
            id val                {$$ = typecheck_fun_call($1, $2, yylineno);}
          | id tuple              {$$ = typecheck_fun_call($1, $2, yylineno);}
          | id_d val              {$$ = typecheck_fun_call($1, $2, yylineno);}
          | id_d tuple            {$$ = typecheck_fun_call($1, $2, yylineno);}
id :
            HD        {$$ = str_new(yytext);}
          | DREF      {$$ = str_new(yytext);}
          | NOT       {$$ = str_new(yytext);}
          | TL        {$$ = str_new(yytext);}
          | REF       {$$ = str_new(yytext);}

id_d:   ID {$$ = str_new(yytext);}

tuple :
            LPAR repexp elements RPAR        {$$ = typecheck_tuple(typecheck_elements($2, $3, yylineno), yylineno);}
          | LPAR RPAR                 {$$ = typecheck_tuple(NULL, yylineno);}
elements :
            COM repexp elements          {$$ = typecheck_elements($2, $3, yylineno);}
          | epsilon                   {$$ = list_new();}
          
/* block */
assign :    
            id_d ASSIGN exp             {$$ = typecheck_assign($1, $3, yylineno);}
if :
            {push_scope("If");} IF exp THEN {push_scope("Then");} exp {pop_scope();}  ELSE {push_scope("Else");} exp {pop_scope(); pop_scope(); $$ = typecheck_if($2, $4, $6, yylineno);}
while :
            {push_scope("While");} WHILE exp DO exp {pop_scope(); $$ = typecheck_while($2, $4, yylineno);}
let :
            {push_scope("Let");} LET repexp IN repexp END  {pop_scope(); $$ = typecheck_let($4, yylineno);}
repexp :
            exp S_COL repexp {$$ = $3;} 
          | exp {$$ = $1;}
          | exp S_COL {$$ = $1;}
dec :
            VAL id_d tvar EQ {push_scope("Var Dec");} exp {pop_scope(); $$ = typecheck_dec($2, $3, $5, yylineno);}

/*types*/
tvar :
            COL type {$$ = $2;}
          | epsilon {$$ = NULL;}
type :
            basictype listtype {$$ = typecheck_type_basic_list($1, $2, yylineno);}
          | basictype {$$ = $1;}
          | listtype {$$ = $1;}
basictype :
            REAL_T ref {$$ = typecheck_type_basic(T_REAL, $2, yylineno);}
          | INT_T ref {$$ = typecheck_type_basic(T_INT, $2, yylineno);}
          | BOOL_T ref {$$ = typecheck_type_basic(T_BOOL, $2, yylineno);}
listtype :
            LIST_T ref listtype {typecheck_type_basic(T_LIST, $2, yylineno);}
          | LIST_T ref {$$ = typecheck_type_basic(T_LIST, $2, yylineno);}
ref :
            REF ref {$$ = typecheck_type_ref($2, yylineno);}
          | epsilon {$$ = NULL;}

/* functions */
fundec :
            FUN id_d {push_scope("Fun dec");} funargs EQ exp { pop_scope(); typecheck_fun_dec($2, $3, $5, yylineno); }
funargs :
            LPAR decargs RPAR {$$ = type_new(T_TUPLE, $2);}
          | LPAR RPAR {$$ = NULL;}
          | argdef {$$ = $1;}
decargs :
            argdef COM decargs {list_prepend($3, $1); $$ = $3;}
          | argdef {List list = list_new(); list_append(list, $1); $$ = list;}
argdef :    
            id_d tvar {$$ = typecheck_add_var($1, $2, yylineno);}
            
/* misc //may need to insert into parent rules to simplify type checking.*/
comp_op :
          EQ {$$ = (Anom)OP_EQ;} | LT {$$ = (Anom)OP_LT;}
        | GT {$$ = (Anom)OP_GT;} | GEQ {$$ = (Anom)OP_GEQ;}
        | LEQ {$$ = (Anom)OP_LEQ;}| NEQ {$$ = (Anom)OP_NEQ;}
add_op :
          PLUS {$$ = (Anom)OP_PLUS;} | MINUS {$$ = (Anom)OP_MINUS;}
mult_op : 
          MULT {$$ = (Anom)OP_MULT;} | DIV {$$ = (Anom)OP_DIV;}
        | INTDIV {$$ = (Anom)OP_INTDIV;} | MOD {$$ = (Anom)OP_MOD;}
epsilon : /* epsilon */
%%

    #include "./lex.yy.c"
