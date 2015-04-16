#ifndef COMP_TYPE
#define COMP_TYPE

#include <stdlib.h>

#include "string.h"
#include "list.h"

typedef struct type {
    str name;
    List sub;
} type;
typedef type* Type;

int sizeof_type = sizeof(struct type);

List typelist;

Type new_type(str name);

/*
 * Returns a new atype 
 */
Type new_atype();

/*
 * Does a shallow comparison of two types.  First compares pointers then names.
 * @return true if types are equal false otherwise.  Warning does a strucure
 * comparison if the type names differ.
 */
bool type_equal(Type t1, Type t2);


/*
 * Generates the an unused anonomous type name and returns it as a str.
 * @return a new anonomous type name.
 */
str new_atype_name();

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
 * at the end of compiling.
 */
void remove_type(Type type);

void 

#endif//COMP_TYPE
