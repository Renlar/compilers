#ifndef COMP_SCOPE
#define COMP_SCOPE

#include "var.h"
#include "type.h"

typedef struct scope {
    struct scope parent;
    str name;
    List vars;
    List types;
} scope;

typedef scope* Scope;

const int sizeof_scope = sizeof(scope);

/*
 * @arg name the name for the new scope used mostly for debugging.
 * @arg parent the scope to set as the parent of the new scope.  Can be null.
 * @return the newly created scope.
 */
Scope new_scope(str name, Scope parent);

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
 * @return the list of variables which were defined in @scope.
 */
//List scope_varlist(Scope scope);

/*
 * Get the var by the given name if it exists in the given scope
 * @arg scope the Scope to search for the desired varialbe
 * @arg symbol the name of the variable we are looking for.
 * @return NULL if no var found with the given sumbol.
 */
Var scope_find_var(Scope scope, str symbol);

/*
 * @arg scope the Scope to search for a variable with @symbol.
 * @arg symbol the name of the variable to search for.
 * @return true if @symbol exists in @scope
 */
bool scope_has_var(Scope scope, str symbol);

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
 * Adds a type to the current scope.  This is only necessary if the type is not
 * used in a parent scope.  Warning: Types will be deleted along with vars when
 * the scope is deleted do not store them persistantly elsewhere.
 * @arg scope the scope to add @type to.
 * @arg type the type to add to @scope.
 */
void scope_add_type(Scope scope, Type type);

/*
 * Get the depth of the current scope.
 * @arg the scope to find the depth of.
 * @return 0 if the scope is the global scope or -1 if @scope is NULL.
 */
int scope_depth(Scope scope);


#endif//COMP_SCOPE
