#ifndef COMP_TYPECHECK
#define COMP_TYPECHECK

#include <string.h>
#include <stdbool.h>

#include "type.h"
#include "list.h"
#include "ngraph.h"
#include "scope.h"
#include "var.h"
#include "ngraph.h"
#include "string.h"



/*
 * Get the current scope depth.
 */
int get_scope_depth();

/*
 * Push a new scope onto the stack.
 */
void scope_push(str name);

/*
 * Pop the current scope off the stack.
 */
void scope_pop();

/*
 * Get the name of the current scope
 */
str scope_name();

/*
 * Add a variable to the current scope.
 */
void scope_add_var(str type, str var);

/*
 * Add a variable by 
 */
void scope_add_var(Type type, str var);

/*
 * Get the the var by name if it is in scope.
 * @symbol the name of the varialble to search for.
 * @return NULL if no var found with given name in the current or parent scopes.
 */
Var get_var(str symbol);

/*
 * Get the var by the given name if it exists in the given scope
 * @scope the scope to search for the desired varialbe
 * @symbol the name of the variable we are looking for.
 * @return NULL if no var found with the given sumbol.
 */
Var scope_get_var(str symbol, Scope scope);

/*
 * Get the Type 
 * @symbol the name of the type to search for.
 * @return the Type if it exists, NULL otherwise.
 */
Type scope_type_get(str symbol);

/*
 * Add the given type to the current scope.
 * @type the type to add.
 */
void scope_add_type(Type type);

/*
 * Add the given type by name to the scope if it exists in the global type list.
 * Does nothing if the type does not exist in the global list.
 * @type the name of the type to search for.  
 */
void scope_add_type(str type);


/*
 * Add a new type to the global list.  Ignored if the type already exists.
 */
void add_type(Type type);

/*
 * 
 */
Type contains_type(Type type);
Type contains_type(str type);



//Private
TypeList compatlist(Type type);

#endif//COMP_TYPECHECK