#ifndef COMP_VAR
#define COMP_VAR

#include <stdbool.h>

#include "string.h"
#include "type.h"

typedef struct var {
  bool isFunction;
  str name;
  Type type;
} var;
typedef var* Var;

const int sizeof_var = sizeof(struct var);

Var new_var(str name, Type type, bool isFunction);

str var_name(Var var);

str var_symbol(Var var);

Type var_type(Var var);

bool var_is_func(Var var);

bool var_eq(Var a, Var b);

bool var_name_eq(Var a, Var b);

bool var_type_eq(Var a, Var b);

#endif//COMP_VAR