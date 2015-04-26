#include "typecheck.h"

#include <stdio.h>

/////Private/////
Scope current = NULL;

void typecheck_init_lang_defs();
/////End Private/////

str op_to_str(OP op) {
  return OP_STR[op];
}

void typecheck_init() {
  current = scope_new("Global", NULL);
  typecheck_init_lang_defs();
}

void typecheck_init_lang_defs() {
  
}

void typecheck_destroy() {
  while (current != NULL) {
    Scope next = scope_parent(current);
    scope_destroy(current);
    current = next;
  }
}

//============================================================================//
//=============================Typecheck functions============================//
//============================================================================//

Type typecheck_arith(Type t1, OP op, Type t2, int line) {
  TYPE_BASE b;
  // Optimistic typing ignores type params when necessary to prevent type errors
  // from propigating as much as is feasable it is still possible the next
  // expression requires an int when the default is real here.
  if (op == OP_AND || op == OP_OR) {
    b = T_BOOL;
  } else if (op == OP_INTDIV || op == OP_MOD) {
    b = T_INT;
  } else {
    if (type_base(t1) == T_REAL || type_base(t1) == T_INT) {
      b = type_base(t1);
    } else if (type_base(t2) == T_REAL || type_base(t2) == T_INT) {
      b = type_base(t2);
    } else {
      b = T_REAL;
    }
  }
  if (type_base(t1) != b || type_base(t2) != b) {
    fprintf(stderr, "TYPE_ERROR: line: %u, expected: (%s %s %s), received: (%s %s %s).\n",
            line, btype_to_str(b), op_to_str(op), btype_to_str(b),
            btype_to_str(type_base(t1)), op_to_str(op), btype_to_str(type_base(t2)));
  }
  type_destroy(t1);
  type_destroy(t2);
  return type_new(b, NULL);
}

Type typecheck_concat(Type t1, Type t2, int line) {
  if (type_base(t1) != T_LIST && type_base(t2) != T_LIST){
    fprintf(stderr, "", line);
  }
  if (type_base(t2) != T_LIST || type_base(t2) != ) {
    
  }
}

Type typecheck_list(List types, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_list Unimplemented.\n");
  return type_new(T_ERROR, NULL);
  
}

Type typecheck_id_access(str name, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_id_access Unimplemented.\n");
  return type_new(T_ERROR, NULL);
  
}

Type typecheck_const(TYPE_BASE base, int line) {
  return type_new(base, NULL);
}

Type typecheck_fun_call(str name, Type args, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_fun_call Unimplemented.\n");
  return type_new(T_ERROR, NULL);
  
}

void typecheck_fun_dec(str name, Type args, Type ret, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_concat Unimplemented.\n");
}

Type typecheck_tuple(List types, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_tuple Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

List typecheck_elements(Type type, List typelist, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_elements Unimplemented.\n");
  return list_new();
}

Type typecheck_assign(str id, Type type, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_assign Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_if(Type cond, Type b_then, Type b_else, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_if Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_while(Type cond, Type b_while, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_while Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_let(Type b_in, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_let Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_dec(str id, Type type, Type b_eq, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_dec Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_type_ref(Type sub_ref, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_type_ref Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_type_basic(TYPE_BASE basic, Type ref, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_type_basic Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}

Type typecheck_type_basic_list(Type base, Type list, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_type_basic_list Unimplemented.\n");
  return type_new(T_ERROR, NULL);
  
}

Type typecheck_add_var(str name, Type type, int line) {
  fprintf(stderr, "IMPLEMENTATION ERROR: typecheck_add_var Unimplemented.\n");
  return type_new(T_ERROR, NULL);
}


//============================================================================//
//==============================Scoping functions=============================//
//============================================================================//

int get_scope_depth() {
  return scope_depth(current);
}

void push_scope(str name) {
  if (current == NULL) {
    printf("SCOPE_WARNING: push_scope: Current scope is null. Pusing %s as global scope.", name);
  }
  current = scope_new(name, current);
}

void pop_scope() {
  if (current == NULL) {
    printf("SCOPE_ERROR: pop_scope: FALTAL current scope is null.  Did you forget to push a global scope first?");
    return;
  }
  if (scope_parent(current) == NULL) {
    printf("SCOPE_ERROR: pop_scope: called when only global scope remains. Cowardly, Refusing to pop global scope.");
    return;
  }
  Scope prev = current;
  current = scope_parent(current);
  scope_destroy(prev);
}

void add_var(Var var) {
  if (current == NULL) {
    printf("SCOPE_ERROR: add_var: FALTAL current scope is null.  Did you forget to push a global scope first?");
    return;
  }
  scope_add_var(current, var);
}

Var get_var(str symbol) {
  return scope_find_var(current, symbol);
}