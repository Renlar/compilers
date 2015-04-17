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
void push_scope(str name);

/*
 * Pop the current scope off the stack.
 */
void pop_scope();


/*
 * Add a variable to the current scope.
 */
void add_var(str type, str var);

/*
 * Add a variable by 
 */
void add_var(Type type, str var);

/*
 * Get the the var by name if it is in scope.
 * @symbol the name of the varialble to search for.
 * @return NULL if no var found with given name in the current or parent scopes.
 */
Var get_var(str symbol);


/*
 * Get the Type 
 * @symbol the name of the type to search for.
 * @return the Type if it exists, NULL otherwise.
 */
Type get_scope_type(str symbol);


/*
 * Add the given type by name to the scope if it exists in the global type list.
 * Does nothing if the type does not exist in the global list.
 * @type the name of the type to search for.  
 */
void add_scope_type(str type);


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


/*
 * Finds the type with the given name and returns it.
 * @name the name to search for in the type list.
 * @return the type with a name matching the provided name.
 */
Type get_type(str name);

//Private
/*
 * Add the provided type to the type list returns the type as a pointer if it
 * already exists.  Warning, creating types with new already does this.
 */
Type add_type(Type type);

/*
 * Removes the given type from existance.  Warning if inproperly used will
 * create hanging pointers.  Generaly best to only use this function to clean up
 * at the end.
 */
void remove_type(Type type);

#endif//COMP_TYPECHECK