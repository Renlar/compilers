#include "var.h"

#include <stdlib.h>

Var new_var(str name, Type type, bool isFunction) {
  Var var = malloc(sizeof_var);
  var->name = name;
  var->type = type;
  var->isFunction = isFunction;
  return var;
}

str var_name(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_name: received NULL argument, var.");
    return NULL;
  }
  return var->name;
}

str var_symbol(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_symbol: received NULL argument, var.");
    return NULL;
  }
  return var->name;
}

Type var_type(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_type: received NULL argument, var.");
    return NULL;
  }
  return var->type;
}

bool var_is_func(Var var){
  if (var == NULL) {
    printf("VAR_ERROR: var_is_func: received NULL argument, var.");
    return NULL;
  }
  return var->isFunction;
}

bool var_eq(Var a, Var b) {
  bool name = var_name_eq(a, b);
  bool type = var_type_eq(a, b);
  return name && type;
}

bool var_name_eq(Var a, Var b) {
  return !strcmp(var_symbol(a), var_symbol(b));
}

bool var_type_eq(Var a, Var b) {
  return type_eq(var_type(a), var_type(b));
}