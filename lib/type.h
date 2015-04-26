#ifndef COMP_TYPE
#define COMP_TYPE

#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "list.h"

//The following two lines must be kept in sync otherwise messages will be 
//incorrect and segfaults could result.
typedef enum TYPE_BASE {T_ERROR, T_REF, T_BOOL, T_INT, T_REAL, T_LIST, T_TUPLE} TYPE_BASE;
static const str TYPE_BASE_STR[] = {"ERROR", "BOOL", "INT", "REAL", "LIST", "TUPLE", "UNKNOWN"};

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


bool type_eq(const Type t1, const Type t2);


Type type_upcast(const Type t1, const Type t2);


bool type_assign_cast(const Type lhs, const Type rhs);


bool can_assign_cast(TYPE_BASE lhs, TYPE_BASE rhs);


bool can_upcast(TYPE_BASE t1, TYPE_BASE t2);


bool can_downcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE upcast(TYPE_BASE t1, TYPE_BASE t2);


TYPE_BASE downcast(TYPE_BASE t1, TYPE_BASE t2);


const str btype_to_str(TYPE_BASE t);


bool type_list_valid(const Type type);


#endif//COMP_TYPE
