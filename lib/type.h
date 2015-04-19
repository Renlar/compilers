#ifndef COMP_TYPE
#define COMP_TYPE

#include <stdlib.h>

#include "string.h"
#include "list.h"

enum TYPE {ERROR = 0, BOOL = 1, INT = 10, REAL = 11, LIST = 20, TUPLE = 21}

typedef struct type {
  TYPE base;
  List sub;
} type;
typedef type* Type;

const int sizeof_type = sizeof(struct type);

List typelist;

/*
 * @arg name the name for the new type.  
 */
Type type_new(TYPE t, List sub);

/*
 * Free all memeory associated with a type.
 */
void type_destroy(Type t);

/*
 * Performs a ml centered type comparison.  Compatable types may be the same or
 * one may be cast to the other.
 * @return true if types are compatable false otherwise.
 */
bool type_compat(Type t1, Type t2);


#endif//COMP_TYPE
