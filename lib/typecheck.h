#ifndef COMP_TYPECHECK
#define COMP_TYPECHECK

#include <string.h>
#include <stdbool.h>

#include "string.h"
#include "list.h"
#include "type.h"
#include "var.h"
#include "scope.h"

Scope current;

/*
 * Get the current scope depth.
 */
int get_scope_depth();

/*
 * Push a new scope onto the stack.
 */
void push_scope(str name);

/*
 * Pop the current scope off the stack.
 */
void pop_scope();

/*
 * Add a variable to the current scope
 */
void add_var(Var var);

/*
 * Get the the var by name if it is in scope.
 * @symbol the name of the varialble to search for.
 * @return NULL if no var found with given name in the current or parent scopes.
 */
Var get_var(str symbol);

#endif//COMP_TYPECHECK