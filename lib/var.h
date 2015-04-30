#ifndef COMP_VAR
#define COMP_VAR

#include <stdbool.h>

#include "string.h"
#include "type.h"

typedef struct var {
  str name;
  Type type;
} var;
typedef var* Var;

const int sizeof_var;

Var var_new(str name, Type type);

void var_destroy(Var var);

const str var_name(Var var);

const str var_symbol(Var var);

Type var_type(Var var);

bool var_eq(Var a, Var b);

bool var_name_eq(Var a, Var b);

bool var_type_eq(Var a, Var b);

str var_to_str(Var var);

#endif//COMP_VAR