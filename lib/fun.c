#include "fun.h"

#include <stdlib.h>

const int sizeof_fun = sizeof(struct fun);

Fun fun_new(str name, Type ret, Type arg) {
  Fun fun = malloc(sizeof_fun);
  fun->name = str_new(name);
  fun->ret = ret;
  fun->arg = arg;
  return fun;
}

void fun_destroy(Fun fun) {
  type_destroy(fun_arg_type(fun));
  type_destroy(fun_ret_type(fun));
  str_destroy(fun_name(fun));
  free(fun);
}

str fun_name(Fun fun) {
  if (fun == NULL) {
    fprintf(stderr, "FUN_ERROR: fun_name: received NULL argument, fun.\n");
    return NULL;
  }
  return fun->name;
}

str fun_symbol(Fun fun) {
  if (fun == NULL) {
    fprintf(stderr, "FUN_ERROR: fun_symbol: received NULL argument, fun.\n");
    return NULL;
  }
  return fun->name;
}

Type fun_ret_type(Fun fun) {
  if (fun == NULL) {
    fprintf(stderr, "FUN_ERROR: fun_ret_type: received NULL argument, fun.\n");
    return NULL;
  }
  return fun->ret;
}

Type fun_arg_type(Fun fun) {
  if (fun == NULL) {
    fprintf(stderr, "FUN_ERROR: fun_arg_type: received NULL argument, fun.\n");
    return NULL;
  }
  return fun->arg;
}

bool fun_eq(Fun a, Fun b) {
  return fun_name_eq(a, b) &&
         fun_ret_type_eq(a, fun_ret_type(b)) &&
         fun_arg_type_eq(a, fun_arg_type(b));
}

bool fun_name_eq(Fun a, Fun b) {
  return !strcmp(fun_symbol(a), fun_symbol(b));
}

bool fun_ret_type_eq(Fun fun, Type type) {
  return type_eq(fun_ret_type(fun), type);
}

bool fun_arg_type_eq(Fun fun, Type type) {
  return type_eq(fun_arg_type(fun), type);
}
