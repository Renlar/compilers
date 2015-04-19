#ifndef COMP_TYPECHECK
#define COMP_TYPECHECK

#include <string.h>
#include <stdbool.h>

#include "string.h"
#include "list.h"
#include "type.h"
#include "var.h"
#include "scope.h"

Scope current = NULL;

/*
 * Get the current scope depth.
 */
int get_scope_depth() {
  return scope_depth(current);
}

/*
 * Push a new scope onto the stack.
 */
void push_scope(str name) {
  if (current == NULL) {
    printf("SCOPE_WARNING: push_scope: Current scope is null. Pusing %s as global scope.", name);
  }
  current = scope_new(name, current);
}

/*
 * Pop the current scope off the stack.
 */
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

/*
 * Add a variable to the current scope
 */
void add_var(Var var) {
  if (current == NULL) {
    printf("SCOPE_ERROR: add_var: FALTAL current scope is null.  Did you forget to push a global scope first?");
    return;
  }
  scope_add_var(current, var);
}

/*
 * Get the the var by name if it is in scope.
 * @symbol the name of the varialble to search for.
 * @return NULL if no var found with given name in the current or parent scopes.
 */
Var get_var(str symbol) {
  return scope_find_var(current, symbol);
}

#endif//COMP_TYPECHECK