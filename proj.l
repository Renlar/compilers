%pointer
%option noyywrap
%option yylineno

%{
  /* put C declarations here*/
%}

%%
[0-9]*"."[0-9]+ {return REAL;}
[0-9]+ { return INT; }

"int" { return INT_T; }
"real" {return REAL_T;}
"list" {return LIST_T;}
"bool" {return BOOL_T;}

"+"  { return PLUS; }
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
"div" {return INTDIV;}
"mod" {return MOD;}
"~" {return NEG;}

":=" {return ASSIGN;}
"::" {return L_CC;}

"=" {return EQ;}
">" {return GT;}
"<" {return LT;}
">=" {return GEQ;}
"<=" {return LEQ;}
"<>" {return NEQ;}

"and" {return AND;}
"not" {return NOT;}
"or" {return OR;}
"!" {return DREF;}

"fun" {return FUN;}
"let" {return LET;}
"in" {return IN;}
"end" {return END;}
"val" {return VAL;}
"ref" {return REF;}

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"while" {return WHILE;}
"do" {return DO;}
"hd" {return HD;}
"tl" {return TL;}
"nil" {return NIL;}

[_a-z][_a-zA-Z0-9]* {return ID;}

"," {return COM;}
";" {return S_COL;}
":" {return COL;}
"(" {return LPAR;}
")" {return RPAR;}
"[" {return LBRK;}
"]" {return RBRK;}

[ \t\n\r]+   {}
\(\*(\*[^\)]|\)|[^\*])*\*\) {} //ignore comments.

%%
