#ifndef COMP_TYPECHECK
#define COMP_TYPECHECK

#include <string.h>
#include <stdbool.h>

#include "string.h"
#include "list.h"
#include "type.h"
#include "var.h"
#include "scope.h"

// The following two declairations must be kept in sync otherwise Output will
// be incorrect and segfaults could result.
typedef enum OP 
    {
      OP_AND, OP_OR,
      OP_EQ, OP_LT, OP_GT, OP_LEQ, OP_GEQ, OP_NEQ,
      OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_INTDIV, OP_MOD
    } OP;
static const str OP_STR[] = 
    {
      "and\0", "or\0",
      "=\0", "<\0", ">\0", "<=\0", ">=\0", "<>\0", 
      "+\0", "-\0", "*\0", "/\0", "div\0", "mod\0"
    };

str op_to_str(OP op);

void typecheck_init();

void typecheck_destroy();


//============================================================================//
//=============================Typecheck functions============================//
//============================================================================//

Type typecheck_bool(Type t1,Type t2, int line);

Type typecheck_arith(Type t1, OP op, Type t2, int line);

Type typecheck_concat(Type t1, Type t2, int line);

Type typecheck_list(List types, int line);

Type typecheck_id_access(str name, int line);

Type typecheck_const(TYPE_BASE base, int line);

Type typecheck_fun_call(str name, Type args, int line);

void typecheck_fun_dec(str name, Type args, Type ret, int line);

Type typecheck_tuple(List types, int line);

List typecheck_elements(Type type, List typelist, int line);

Type typecheck_assign(str id, Type type, int line);

Type typecheck_if(Type cond, Type b_then, Type b_else, int line);

Type typecheck_while(Type cond, Type b_while, int line);

Type typecheck_let(Type b_in, int line);

Type typecheck_dec(str id, Type type, Type b_eq, int line);

Type typecheck_type_ref(Type sub_ref, int line);

Type typecheck_type_basic(TYPE_BASE basic, Type ref, int line);

Type typecheck_type_basic_list(Type base, Type list, int line);

Type typecheck_add_var(str name, Type type, int line);

//============================================================================//
//==============================Scoping functions=============================//
//============================================================================//

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
 * Add a variable to the current scope
 */
void add_var(Var var, int line);

/*
 * Get the the var by name if it is in scope.
 * @symbol the name of the varialble to search for.
 * @return NULL if no var found with given name in the current or parent scopes.
 */
Var get_var(str symbol);

#endif//COMP_TYPECHECK