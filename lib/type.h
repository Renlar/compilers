#ifndef COMP_TYPE
#define COMP_TYPE

#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "list.h"

typedef enum {
  T_ERROR = 0,
  T_REF = 1,
  T_BOOL = 10, 
  T_INT = 20, 
  T_REAL = 21, 
  T_LIST = 30, 
  T_TUPLE = 31
} TYPE_BASE;

typedef struct type {
  TYPE_BASE base;
  List sub;
} type;

typedef type* Type;


const int sizeof_type;


Type type_new(TYPE_BASE base, List sub);


void type_destroy(Type t);


TYPE_BASE type_base(Type type);


List type_sub(Type type);


bool type_eq(Type t1, Type t2);


Type type_upcast(Type t1, Type t2);


bool type_assign_cast(Type lhs, Type rhs);


bool can_assign_cast(TYPE_BASE lhs, TYPE_BASE rhs);


bool can_upcast(TYPE_BASE t1, TYPE_BASE t2);


bool can_downcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE upcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE downcast(TYPE_BASE t1, TYPE_BASE t2);


str btype_to_str(TYPE_BASE t);


bool type_list_valid(Type type);


#endif//COMP_TYPE
