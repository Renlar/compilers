#include "scope.h"
#include "string.h"

const int sizeof_scope = sizeof(scope);

Scope scope_new(str name, Scope parent) {
  Scope scope = malloc(sizeof_scope);
  scope->parent = parent;
  scope->name = str_new(name);
  scope->vars = list_new();
  scope->funs = list_new();
  return scope;
}

void scope_destroy(Scope scope) {
  str_destroy(scope_name(scope));
  list_for_each(scope_vars(scope), (void (*)(Anom))var_destroy);
  list_for_each(scope_funs(scope), (void (*)(Anom))fun_destroy);
  free(scope);
}

Scope scope_parent(Scope scope) {
  if (scope != NULL) {
    return scope->parent;
  }
  fprintf(stderr, "SCOPE_VAR_WARNING: scope_parent: received NULL argument, scope.\n");
  return NULL;
}

str scope_name(Scope scope) {
  if (scope != NULL) {
    return scope->name;
  }
  fprintf(stderr, "SCOPE_VAR_WARNING: scope_name: received NULL argument, scope.\n");
  return NULL;  //TODO: return empty string instead?
}

List scope_vars(Scope scope) {
  if (scope != NULL) {
    return scope->vars;
  }
  fprintf(stderr, "SCOPE_VAR_WARNING: scope_vars: received NULL argument, scope.\n");
  return NULL;
}

Var scope_get_var(Scope scope, str symbol) {
  if (scope == NULL || symbol == NULL) {
    fprintf(stderr, "SCOPE_VAR_WARNING: scope_get_var: received NULL argument, scope and/or symbol.\n");
    return NULL;
  }
  bool eq(Var var, str symbol) {
    if (var != NULL) {
      return (bool) !strcmp(var_name(var), symbol);
    }
    return false;
  }
  return (Var)list_find(scope_vars(scope), (bool (*)(Anom, Anom))eq, symbol);
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
      fprintf(stderr, "SCOPE_VAR_WARNING: scope_add_var: var %s already defined in the current scope.\n", var_symbol(var));
    } else {
      list_append(scope_vars(scope), var);
    }
  } else {
    fprintf(stderr, "SCOPE_VAR_WARNING: scope_add_var: received NULL argument, scope and/or var.\n");
  }
}

List scope_funs(Scope scope) {
  if (scope != NULL) {
    return scope->funs;
  }
  fprintf(stderr, "SCOPE_VAR_WARNING: scope_funs: received NULL argument, scope.\n");
  return NULL;
}

Fun scope_get_fun(Scope scope, str symbol) {
  if (scope == NULL || symbol == NULL) {
    fprintf(stderr, "SCOPE_VAR_WARNING: scope_get_fun: received NULL argument, scope and/or symbol.\n");
    return NULL;
  }
  bool eq(Fun fun, str symbol) {
    if (fun != NULL) {
      str funname = fun_name(fun);
      if (funname != NULL) {
        return (bool) !strcmp(funname, symbol);
      }
    }
    return false;
  }
  return (Fun)list_find(scope_funs(scope), (bool (*)(Anom, Anom))eq, symbol);
}

Fun scope_find_fun(Scope scope, str symbol) {
  Fun fun = NULL;
  while (!fun && scope) {
    fun = scope_get_fun(scope, symbol);
    scope = scope_parent(scope);
  }
  return fun;
}

bool scope_has_fun(Scope scope, str symbol) {
  return scope_get_fun(scope, symbol) != NULL;
}

bool scope_fun_exists(Scope scope, str symbol) {
  return scope_find_fun(scope, symbol) != NULL;
}

void scope_add_fun(Scope scope, Fun fun) {
  if (scope != NULL || fun != NULL) {
    if (scope_has_fun(scope, fun_symbol(fun))) {
      fprintf(stderr, "SCOPE_VAR_WARNING: scope_add_fun: fun %s already defined in the current scope.\n", fun_symbol(fun));
    } else {
      list_append(scope_funs(scope), fun);
    }
  } else {
    fprintf(stderr, "SCOPE_VAR_WARNING: scope_add_fun: received NULL argument, scope and/or fun.\n");
  }
}

int scope_depth(Scope scope) {
  int depth = -1;
  while( scope != NULL ) {
    scope = scope_parent(scope);
    depth++;
  }
  if (depth == -1) {
    fprintf(stderr, "SCOPE_VAR_WARNING: scope_depth: received NULL argument, scope.\n");
  }
  return depth;
}
