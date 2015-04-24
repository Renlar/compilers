#include "typecheck.h"

Scope current = NULL;

int get_scope_depth() {
  return scope_depth(current);
}

void push_scope(str name) {
  if (current == NULL) {
    printf("SCOPE_WARNING: push_scope: Current scope is null. Pusing %s as global scope.", name);
  }
  current = scope_new(name, current);
}

void pop_scope() {
  if (current == NULL) {
    printf("SCOPE_ERROR: pop_scope: FALTAL current scope is null.  Did you forget to push a global scope first?");
    return;
  }
  if (scope_parent(current) == NULL) {
    printf("SCOPE_ERROR: pop_scope: called when only global scope remains. Cowardly, Refusing to pop global scope.");
    return;
  }
  Scope prev = current;
  current = scope_parent(current);
  scope_destroy(prev);
}

void add_var(Var var) {
  if (current == NULL) {
    printf("SCOPE_ERROR: add_var: FALTAL current scope is null.  Did you forget to push a global scope first?");
    return;
  }
  scope_add_var(current, var);
}

Var get_var(str symbol) {
  return scope_find_var(current, symbol);
}