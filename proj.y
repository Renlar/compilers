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
#define YYSTYPE Type
extern int yylineno;
extern str yytext;
str yytprev;
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
            and OR or {$$ = typecheck_arith($1, OP_OR, $2, yylineno);}
          | and       {$$ = $1;}
and :
            comp AND and {$$ = typecheck_arith($1, OP_AND, $2, yylineno);}
          | comp      {$$ = $1;}
comp :
            concat comp_op comp {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | concat    {$$ = $1;}
concat :
            add L_CC concat {$$ = typecheck_concat($1, $2, yylineno);}
          | add       {$$ = $1;}
add :
            mult add_op add {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | mult      {$$ = $1;}
mult :
            paren mult_op mult {$$ = typecheck_arith($1, (OP)$2, $3, yylineno);}
          | paren     {$$ = $1;}
paren :
            {push_scope("Begin paren");} LPAR repexp RPAR {pop_scope(); $$ = $1;}
          | list      {$$ = $1;}
list :
            LBRK elements RBRK {$$ = typecheck_list($1, yylineno);}
          | LBRK RBRK {$$ = typecheck_list(NULL, yylineno);}
          | NIL {$$ = typecheck_list(NULL, yylineno);}
          | val {$$ = $1;}
val :
            ID        {$$ = typecheck_id_access(yytext, yylineno);}
          | INT       {$$ = typecheck_const(T_INT, yylineno);}
          | REAL      {$$ = typecheck_const(T_REAL, yylineno);}
          | NEG INT   {$$ = typecheck_const(T_INT, yylineno);}
          | NEG REAL  {$$ = typecheck_const(T_REAL, yylineno);}
          | BOOL      {$$ = typecheck_const(T_BOOL, yylineno);}
          | fun_call  {$$ = $1;}
fun_call :
            id tuple  {$$ = typecheck_fun_call($1, $2, yylineno);}
          | id exp    {$$ = typecheck_fun_call($1, $2, yylineno);}
          | ID tuple  {$$ = typecheck_fun_call(yytext, $2, yylineno);}
          | ID exp    {$$ = typecheck_fun_call(yytext, $2, yylineno);}
id :
            HD        {$$ = yytext;}
          | DREF      {$$ = yytext;}
          | NOT       {$$ = yytext;}
          | TL        {$$ = yytext;}
          | REF       {$$ = yytext;}
tuple :
            LPAR elements RPAR        {$$ = typecheck_tuple($1, yylineno);}
          | LPAR RPAR                 {$$ = typecheck_tuple(NULL, yylineno);}
elements :
            and COM elements          {$$ = typecheck_elements($1, $2, yylineno);}
          | and                       {List list = list_new(); list_append(list, $1); $$ = list;}
          
/* block */
assign :    
            assign_d exp             {$$ = typecheck_assign($1, $2, yylineno);}
assign_d:
            ID {$$ = yytext;} ASSIGN
if :
            {push_scope("If");} IF exp THEN {push_scope("Then");} exp {pop_scope();}  ELSE {push_scope("Else");} exp {pop_scope(); pop_scope(); $$ = typecheck_if($1, $2, $3, yylineno);}
while :
            {push_scope("While");} WHILE exp DO exp {pop_scope(); $$ = typecheck_while($1, $2, yylineno);}
let :
            {push_scope("Let");} LET repexp IN repexp END  {pop_scope(); $$ = typecheck_let($2, yylineno);}
repexp :
            exp S_COL repexp {$$ = $2;}
          | exp {$$ = $1;}
          | exp S_COL {$$ = $1;}
dec :
            dec_d tvar EQ {push_scope("Var Dec");} exp {pop_scope(); $$ = typecheck_dec($1, $2, $3, yylineno);}

dec_d:
            VAL ID {$$ = yytext;}

/*types*/
tvar :
            COL type {$$ = $1;}
          | epsilon {$$ = NULL;}
type :
            basictype listtype {$$ = typecheck_type_basic_list($1, $2, yylineno);}
          | basictype {$$ = $1;}
          | listtype {$$ = $1;}
basictype :
            REAL_T ref {$$ = typecheck_type_basic(T_REAL, $1, yylineno);}
          | INT_T ref {$$ = typecheck_type_basic(T_INT, $1, yylineno);}
          | BOOL_T ref {$$ = typecheck_type_basic(T_BOOL, $1, yylineno);}
listtype :
            LIST_T ref listtype {typecheck_type_basic(T_LIST, $1, yylineno);}
          | LIST_T ref {$$ = typecheck_type_basic(T_LIST, $1, yylineno);}
ref :
            REF ref {$$ = typecheck_type_ref($1, yylineno);}
          | epsilon {$$ = NULL;}
/* functions */
fundec :
            fundec_d {push_scope($1);} funargs EQ exp { pop_scope(); typecheck_fun_dec($1, $2, $3, yylineno); }
fundec_d:
            FUN ID {$$ = yytext;}
funargs :
            LPAR decargs RPAR {$$ = $1;}
          | LPAR RPAR {$$ = NULL;}
          | argdef {$$ = $1;}
decargs :
            argdef COM decargs {list_prepend($2, $1); $$ = $2;}
          | argdef {List list = list_new(); list_append(list, $1); $$ = list;}
argdef :    
            ID {yytprev = yytext;} tvar {$$ = typecheck_add_var(yytprev, $1, yylineno);}
            
/* misc //may need to insert into parent rules to simplify type checking.*/
comp_op :
          EQ {$$ = (Type)OP_EQ;} | LT {$$ = (Type)OP_LT;}
        | GT {$$ = (Type)OP_GT;} | GEQ {$$ = (Type)OP_GEQ;}
        | LEQ {$$ = (Type)OP_LEQ;}| NEQ {$$ = (Type)OP_NEQ;}
add_op :
          PLUS {$$ = (Type)OP_PLUS;} | MINUS {$$ = (Type)OP_MINUS;}
mult_op : 
          MULT {$$ = (Type)OP_MULT;} | DIV {$$ = (Type)OP_DIV;}
        | INTDIV {$$ = (Type)OP_INTDIV;} | MOD {$$ = (Type)OP_MOD;}
epsilon : /* epsilon */
%%

    #include "./lex.yy.c"
