#include "var.h"

#include <stdlib.h>

const int sizeof_var = sizeof(struct var);

Var var_new(str name, Type type) {
  Var var = malloc(sizeof_var);
  var->name = str_new(name);
  var->type = type;
  return var;
}

void var_destroy(Var var) {
  type_destroy(var_type(var));
  str_destroy(var_name(var));
  free(var);
}

const str var_name(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_name: received NULL argument, var.\n");
    return NULL;
  }
  return var->name;
}

const str var_symbol(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_symbol: received NULL argument, var.\n");
    return NULL;
  }
  return var->name;
}

Type var_type(Var var) {
  if (var == NULL) {
    printf("VAR_ERROR: var_type: received NULL argument, var.\n");
    return NULL;
  }
  return var->type;
}

bool var_eq(Var a, Var b) {
  return var_type_eq(a, b) && var_name_eq(a, b);
}

bool var_name_eq(Var a, Var b) {
  return !strcmp(var_symbol(a), var_symbol(b));
}

bool var_type_eq(Var a, Var b) {
  return type_eq(var_type(a), var_type(b));
}

str var_to_str(Var var) {
  str result = str_new("Var (Name: ");
  result = str_concat_clean_head(result, var_name(var));
  result = str_concat_clean_head(result, "Type: ");
  result = str_concat_clean(result, type_to_str(var_type(var)));
  result = str_concat_clean_head(result, ") ");
  return result;
}