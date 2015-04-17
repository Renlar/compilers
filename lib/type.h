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

const int sizeof_type = sizeof(struct type);

List typelist;

/*
 * @arg name the name for the new type.  
 */
Type new_type(str name);

/*
 * @return a new anonomous type.
 */
Type new_atype();

/*
 * Performs a shallow comparison of two types.  First compares pointers then
 * names.  Does not consider structure unless the types are anonomous.
 * @return true if types are equal false otherwise.
 */
bool type_equal(Type t1, Type t2);

void 

#endif//COMP_TYPE
