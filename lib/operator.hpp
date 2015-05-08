#ifndef COMP_OPERATOR
#define COMP_OPERATOR


/**
 * Defines the list of operators for use in expressions.
 */

typedef enum OPERATOR
{// FUN, WHILE COMMA
  IF, THEN, ELSE, WHILE, DO, LET, IN, END, VAL, FUN, //blocks
  ASSIGN,
  AND, OR,
  EQ, LT, GT, LEQ, GEQ, NEQ,
  PLUS, MINUS, MULT, DIV, INTDIV, MOD, NEG,
  FUNCALL,
  LIST_BEGIN, TUPLE_BEGIN, COMMA, LIST_END, TUPLE_END,
  CONCAT
} OPERATOR;

static const std::string OPERATOR_STRING[] = 
{
  "if ", "then ", "else ", "while ", "do ", "let ", "in ", "end ", "val ", "fun ",
  ":= ",
  "and ", "or ",
  "= ", "< ", "> ", "<= ", ">= ", "<> ",
  "+ ", "- ", "* ", "/ ", "div ", "mod ", "~ ",
  "",  //empty on purpose, simplifies printing optimized source code.
  "[ ", "( ", ", ", "] ", ") ",
  ":: "
};

static const unsigned short OPERAND_COUNT[] = 
{
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
  2,
  2, 2,
  2, 2, 2, 2, 2, 1,
  2, 2, 2, 2, 2, 2, 2,
  1,
  1, 1, 1, 0, 0,
  2
};


#endif//COMP_OPERATOR
