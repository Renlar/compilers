#ifndef COMP_FUN
#define COMP_FUN

#include <stdbool.h>

#include "string.h"
#include "type.h"

typedef struct fun {
  str name;
  Type ret;
  Type arg;
} fun;
typedef fun* Fun;

const int sizeof_var;

Fun fun_new(str name, Type ret, Type par);

void fun_destroy(Fun fun);

const str fun_name(Fun fun);

const str fun_symbol(Fun fun);

Type fun_ret_type(Fun fun);

Type fun_arg_type(Fun fun);

bool fun_eq(Fun a, Fun b);

bool fun_name_eq(Fun a, Fun b);

bool fun_ret_type_eq(Fun fun, Type type);

bool fun_arg_type_eq(Fun fun, Type type);

bool fun_takes_args(Fun fun, Type args);

str fun_to_str(Fun fun);

#endif//COMP_VAR
