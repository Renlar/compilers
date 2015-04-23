#ifndef COMP_TYPE_BASE
#define COMP_TYPE_BASE

#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "list.h"

typedef enum {
  ERROR = 0, 
  BOOL = 1, 
  INT = 10, 
  REAL = 11, 
  LIST = 20, 
  TUPLE = 21
} TYPE_BASE;

typedef struct type {
  TYPE_BASE base;
  List sub;
} type;

typedef type* Type;


const int sizeof_type = sizeof(struct type);


Type type_new(TYPE_BASE base, List sub);


void type_destroy(Type t);


TYPE_BASE type_base(Type type);


List type_sub(Type type);


Type type_upcast(Type t1, Type t2);


bool type_assign_cast(Type lhs, Type rhs);


bool can_assign_cast(TYPE_BASE lhs, TYPE_BASE rhs);


bool can_upcast(TYPE_BASE t1, TYPE_BASE t2);


bool can_downcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE upcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE downcast(TYPE_BASE t1, TYPE_BASE t2);


str btype_to_str(TYPE_BASE t);


bool valid_list(Type type);


#endif//COMP_TYPE_BASE
