#ifndef COMP_SCOPE
#define COMP_SCOPE

#include "var.h"
#include "type.h"

typedef struct scope {
    struct scope *parent;
    str name;
    List vars;
} scope;

typedef scope* Scope;

const int sizeof_scope = sizeof(scope);

/*
 * @arg name the name for the new scope used mostly for debugging.
 * @arg parent the scope to set as the parent of the new scope.  Can be null.
 * @return the newly created scope.
 */
Scope scope_new(str name, Scope parent);

/*
 * @arg scope the scope to get the parent of.
 * @return the parent of @scope.
 */
Scope scope_parent(Scope scope);

/*
 * @arg scope the scope to get the name of.
 * @return the name of @arg scope or empty string if @scope is null.
 */
str scope_name(Scope scope);

/*
 * @arg scope the scope to get the varlist for.
 * @return the list of variables which are defined in @scope, ignores parents.
 */
List scope_vars(Scope scope);

/*
 * Get the var if it exists in the passed in scope.  Does not search parent
 * scopes.
 * @arg scope the scope to search for a variable with @symbol
 * @arg symbol the variable name to search for in @scope
 * @return the varialbe if it is found, NULL otherwise.
 */
Var scope_get_var(Scope scope, str symbol);

/*
 * Get the var by the given name if it exists in the given scope or any parent
 * scope.
 * @arg scope the Scope to start searching for the desired varialbe
 * @arg symbol the name of the variable to search for.
 * @return NULL if no var found with the given sumbol.
 */
Var scope_find_var(Scope scope, str symbol);

/*
 * Get the var if it exists in the passed in scope.  Does not search parent
 * scopes.
 * @arg scope the scope to search for a variable with @symbol
 * @arg symbol the variable name to search for in @scope
 * @return true if @symbol exists in @scope
 */
bool scope_has_var(Scope scope, str symbol);

/*
 * Get the var by the given name if it exists in the given scope or any parent
 * scope.
 * @arg scope the Scope to start searching for the desired varialbe
 * @arg symbol the name of the variable to search for.
 * @return true if @symbol is currently in scope.
 */
bool scope_var_exists(Scope scope, str symbol);

/*
 * @arg scope the Scope to add the variable to.
 * @arg var the variable to add to the scope.  Loggs error if the @var already
 *      exists.
 */
void scope_add_var(Scope scope, Var var);

/*
 * @arg scope the Scope to the the parent of
 * @arg parent the Scope to set as teh parent of @scope
 */
void scope_set_parent(Scope scope, Scope parent);

/*
 * Get the depth of the current scope.
 * @arg the scope to find the depth of.
 * @return 0 if the scope is the global scope or -1 if @scope is NULL.
 */
int scope_depth(Scope scope);


#endif//COMP_SCOPE
