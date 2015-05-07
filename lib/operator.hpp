#ifndef COMP_OPERATOR
#define COMP_OPERATOR


/**
 * Defines the list of operators for use in expressions.
 */

typedef enum OPERATOR
{ // FUN, WHILE COMMA END IN THEN ELSE DO
  
  WHILE, FUN, COMMA, END, IN, THEN, ELSE, DO,
  
  
  IF, LET, VAL,  //blocks
  ASSIGN,
  AND, OR,
  EQ, LT, GT, LEQ, GEQ, NEQ,
  PLUS, MINUS, MULT, DIV, INTDIV, MOD, NEG,
  FUNCALL,
  LIST_BEGIN, TUPLE_BEGIN,  LIST_END, TUPLE_END,
  CONCAT
} OPERATOR;

static const std::string OPERATOR_STRING[] = 
{
  "while ", "fun ", ", ", "end ", "in ", "then ", "else ", "do ",
  
  
  "if ", "let ", "val ", 
  ":= ",
  "and ", "or ",
  "= ", "< ", "> ", "<= ", ">= ", "<> ",
  "+ ", "- ", "* ", "/ ", "div ", "mod ", "~ ",
  "",  //empty on purpose, simplifies printing optimized source code.
  "[ ", "( " , "] ", ") ",
  ":: "
};

static const unsigned short OPERAND_COUNT[] = 
{
  0, 1, 1, 0, 0, 0, 0, 0,
  
  
  0, 0, 1, 
  2,
  2, 2,
  2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 2,
  1,
  1, 1,  0, 0,
  2
};


#endif//COMP_OPERATOR
