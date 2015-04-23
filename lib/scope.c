#include "scope.h"

Scope scope_new(str name, Scope parent) {
  Scope scope = malloc(sizeof_scope);
  scope->parent = parent;
  scope->name = str_new(name);
  scope->vars = list_new();
  return scope;
}

Scope scope_parent(Scope scope) {
  if (scope != NULL) {
    return scope->parent;
  }
  printf("SCOPE_VAR_WARNING: scope_parent: received NULL argument, scope.\n");
  return NULL;
}

str scope_name(Scope scope) {
  if (scope != NULL) {
    return scope->name;
  }
  printf("SCOPE_VAR_WARNING: scope_name: received NULL argument, scope.\n");
  return NULL;  //TODO: return empty string instead?
}

List scope_vars(Scope scope) {
  if (scope != NULL) {
    return scope_vars(scope);
  }
  printf("SCOPE_VAR_WARNING: scope_vars: received NULL argument, scope.\n");
  return NULL;
}

Var scope_get_var(Scope scope, str symbol) {
  if (scope == NULL || symbol == NULL) {
    printf("SCOPE_VAR_WARNING: scope_get_var: received NULL argument, scope and/or symbol.\n");
    return NULL;
  }
  bool eq(Var var, str symbol) {
    if (var != NULL) {
      return (bool) !strcmp(var_name(var), symbol);
    }
  }
  return (Var)list_find(scope_vars(scope), eq, symbol);
}

Var scope_find_var(Scope scope, str symbol) {
  Var var = NULL;
  while (!var && scope) {
    var = scope_get_var(scope, symbol);
    scope = scope_parent(scope);
  }
  return var;
}

bool scope_has_var(Scope scope, str symbol) {
  return scope_get_var(scope, symbol) != NULL;
}

bool scope_var_exists(Scope scope, str symbol) {
  return scope_find_var(scope, symbol) != NULL;
}

void scope_add_var(Scope scope, Var var) {
  if (scope != NULL || var != NULL) {
    if (scope_has_var(scope, var_symbol(var))) {
      printf("SCOPE_VAR_WARNING: scope_add_var: var %s already defined in the current scope.\n", var_symbol(var));
    } else {
      list_append(scope_vars(scope), var);
    }
  } else {
    printf("SCOPE_VAR_WARNING: scope_add_var: received NULL argument, scope and/or var.\n");
  }
}

int scope_depth(Scope scope) {
  int depth = -1;
  while( scope != NULL ) {
    scope = scope_parent(scope);
    depth++;
  }
  if (depth == -1) {
    printf("SCOPE_VAR_WARNING: scope_depth: received NULL argument, scope.\n");
  }
  return depth;
}
