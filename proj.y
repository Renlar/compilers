%token ERROR
%token INT ID REAL BOOL INT_T REAL_T LIST_T S_COL BOOL_T
%token DREF NOT REF IF THEN ELSE WHILE DO HD TL VAL
%token LPAR RPAR LBRK RBRK NIL COL COM END FUN IN LET LIST 
%left  PLUS MINUS MULT DIV EQ GT LT GEQ LEQ NEQ AND NOT OR DREF MOD INTDIV
%right L_CC ASSIGN NEG

%{
 /* put your c declarations here */
#define YYDEBUG 1
%}

%%
start : exp S_COL start | epsilon
exp : if | while | let | fundec | and | dec | assign
/* expressions */
and : and AND and | or
or : or OR or | comp
comp : comp comp_op comp | concat
concat : concat L_CC concat | add
add : add add_op add | mult
mult : mult mult_op mult | paren
paren : LPAR repexp RPAR | list
list : LBRK elements RBRK | LBRK RBRK | NIL | val
val : ID | INT | REAL | NEG INT | NEG REAL | BOOL | fun_call
fun_call : id tuple | id exp | ID tuple | ID exp 
id : HD | DREF | NOT | TL | REF
tuple : LPAR elements RPAR | LPAR RPAR
elements : and COM elements | and
/* block */
assign : ID ASSIGN exp
if : IF exp THEN exp ELSE exp
while : WHILE exp DO exp
let : LET repexp IN repexp END
repexp : exp S_COL repexp | exp | exp S_COL
dec : VAL ID tvar EQ exp
/*types*/
tvar : COL type | epsilon
type : basictype listtype | basictype | listtype
basictype : REAL_T ref | INT_T ref | BOOL_T ref
listtype : LIST_T ref listtype | LIST_T ref
ref : REF ref | epsilon
/* functions */
fundec : FUN ID funargs EQ exp
funargs : LPAR decargs RPAR | LPAR RPAR | argdef
decargs : argdef COM decargs | argdef
argdef : ID tvar
/* misc */
comp_op : EQ | LT | GT | GEQ | LEQ | NEQ 
add_op : PLUS | MINUS
mult_op : MULT | DIV | INTDIV | MOD
epsilon : /* epsilon */
%%
    #include "./lex.yy.c"
