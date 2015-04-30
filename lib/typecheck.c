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

//TODO: initialized language constants, like hd and tl.
void typecheck_init_lang_defs() {
  scope_add_fun(current, fun_new("not", type_new(T_BOOL, NULL), type_new(T_BOOL, NULL)));
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
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_arith input: %s %s %s line: %u\n", type_to_str(t1), op_to_str(op), type_to_str(t2), line);
  #endif
  TYPE_BASE b;
  // Optimistic typing ignores type params when necessary to prevent type errors
  // from propigating as much as is feasable it is still possible the next
  // expression requires an int when the default is real here.
  if (op == OP_AND || op == OP_OR) {
    b = T_BOOL;
  } else if (op == OP_INTDIV || op == OP_MOD) {
    b = T_INT;
  } else if (OP_EQ <= op && op <= OP_NEQ) {
    if (type_base(t1) != type_base(t2)) {
      fprintf(stderr, "ERROR: Type Mismatch near line: %u, expected: (%s %s %s), received: (%s %s %s).\n",
              line, btype_to_str(b), op_to_str(op), btype_to_str(b),
              btype_to_str(type_base(t1)), op_to_str(op), btype_to_str(type_base(t2)));
    }
    //type_destroy(t1);
    //type_destroy(t2);
    return type_new(T_BOOL, NULL);
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
    fprintf(stderr, "ERROR: Type Mismatch near line: %u, expected: (%s %s %s), received: (%s %s %s).\n",
            line, btype_to_str(b), op_to_str(op), btype_to_str(b),
            btype_to_str(type_base(t1)), op_to_str(op), btype_to_str(type_base(t2)));
  }
  //type_destroy(t1);
  //type_destroy(t2);
  return type_new(b, NULL);
}

//TODO: method should be checked thourally against spec rules 6
//TODO: ADD checks for VOID type and error on it.
Type typecheck_concat(Type t1, Type t2, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_concat input: %s :: %s, line: %u\n", type_to_str(t1), type_to_str(t2), line);
  #endif
  Type list;
  Type concat;
  // Simple comparison, types currently must be exactly the same to create a
  // list from them.
  if (type_base(t1) != T_LIST && type_base(t2) != T_LIST && type_eq(t1, t2)) {
    List sub = list_new();  list_append(sub, t1);
    list = type_new(T_LIST, sub);
    concat = t2;
  } else if (type_base(t1) == T_LIST) {
    list = t1;
    concat = t2;
    // Check to ensure concat is done below. 
  } else if (type_base(t2) == T_LIST) {
    list = t2;
    concat = t1;
    // Check to ensure concat is done below. 
  } else {
    fprintf(stderr, "ERROR: Type Mismatch near line %u, expected list :: list, list :: element, element :: list, or type_1 :: type_1, received: %s :: %s\n",
            line, type_to_str(t1), type_to_str(t2));
    //type_destroy(t1);
    //type_destroy(t2);
    // Prevent errors from propigating as much as possible return a nil list so
    // it is compatable with as much as possible.
    return type_new(T_LIST, NULL);
  }
  
  if (type_base(concat) == T_LIST) {
    if (type_eq(list_head(type_sub(list)), list_head(type_sub(concat)))) {
      list_append_list(type_sub(list), type_sub(concat));
    }
  } else if (type_eq(list_head(type_sub(list)), concat)) {
    // TODO: analize if the following statement is the correct way to handle a
    // list type or if the following should be destroyed instead.
    // Store the second eqivalent type for comparison purposes?
    list_append(type_sub(list), concat);  //TODO: analyze if this tatement is correct.
  } else if (list_size(type_sub(list)) == 0) {
    list_append(type_sub(list), concat);  //TODO: Should error on empty list according to requirement 6;
  }
  return list;
}


Type typecheck_list(List types, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_list input: types: %s, line: %u\n", list_to_str(types, (str (*)(Anom))type_to_str), line);
  #endif
  bool same = true;
  Type first = NULL;
  
  //Start nested function op
  void op(Type t) {
    if (first == NULL) {
      first = t;
      return;
    }
    if (type_base(first) != type_base(t)) {
      same = false;
    }
  }
  //end nested function op
  
  list_for_each(types, (void (*)(Anom))op);
  if (!same) {
    fprintf(stderr, "ERROR: near line: %u, list constructor passed list of incompatable types.\n", line);
  }
  List sub = list_new();
  if (list_head(types) != NULL) {
    list_append(sub, list_head(types));
  }
  return type_new(T_LIST, sub);
}


Type typecheck_id_access(str name, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_id_access input: name: %s, line: %u\n", name, line);
  #endif
  Type ret;
  Var var = scope_find_var(current, name);
  Fun fun = scope_find_fun(current, name);
  if (var) {
    ret = type_clone(var_type(var));
    if (type_base(var_type(var)) == T_LIST && !type_base_defined(var_type(var))) {
      fprintf(stderr, "ERROR; line: %u, List variable, %s, used which has undefined base type\n",
              line, name);
    }
  } else if (fun) { 
    if (type_assign_cast(fun_ret_type(fun), type_new(T_VOID, NULL), line)) {
      ret = type_clone(fun_ret_type(fun));
    } else {
      fprintf(stderr, "ERROR: line: %u Function, %s requires arguments, %s, given VOID.\n",
              line, name, type_to_str(fun_arg_type(fun)));
      ret = type_new(T_ERROR, NULL);
    }
  } else {
    fprintf(stderr, "ERROR: line: %u, Access of Undefined identifier, %s\n", line, name);
    ret = type_new(T_ERROR, NULL);
  }
  return ret;
}


Type typecheck_const(TYPE_BASE base, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_const input: basetype: %s, line: %u\n", btype_to_str(base), line);
  #endif
  return type_new(base, NULL);
}


Type typecheck_fun_call(str name, Type args, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_fun_call input: name: %s, args: %s, line: %u\n", name, type_to_str(args), line);
  #endif
  if (!strcmp(name, "hd") || !strcmp(name, "tl")) {
    if (type_base(args) != T_LIST) {
      fprintf(stderr, "ERROR: near line: %u, function %s received: %s, expected: LIST\n", line, name, type_to_str(args));
      return args;
    } else if (!strcmp(name, "hd")) {
      return list_head(type_sub(args));
    } else {
      return args;
    }
  } else if (!strcmp(name, "!")) {
    if (type_base(args) == T_REF) {
      return list_head(type_sub(args));
    } else {
      fprintf(stderr, "ERROR: near line: %u function %s received type, %s, expected REF\n", line, name, type_to_str(args));
      return args;
    }
  } else if (!strcmp(name, "ref")) {
    List sub = list_new();
    list_append(sub, args);
    return type_new(T_REF, sub);
  }
  Fun fun = scope_find_fun(current, name);
  if (fun == NULL) {
    fprintf(stderr, "ERROR: near line: %u, Implicit declaration of function, %s(%s)\n", line, name, type_to_str(args));
  } else if (!type_assign_cast(fun_arg_type(fun), args, line)) {
    fprintf(stderr, "ERROR: line: %u Argument type mismatch for function, %s, Expected: %s, Received: %s\n",
            line, name, type_to_str(fun_arg_type(fun)), type_to_str(args));
  }
  return type_clone(fun_ret_type(fun));
}


void typecheck_fun_dec(str name, Type args, Type ret, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_fun_dec input: name: %s, args: %s, ret: %s, line: %u\n", name, type_to_str(args), type_to_str(ret), line);
  #endif
  if (scope_get_fun(current, name)) {
    fprintf(stderr, "ERROR: line %u Redeclaration of identifier %s\n", line, name);
    return;
  }
  Fun fun = fun_new(name, ret, args);
  scope_add_fun(current, fun);
}

//TODO: check this method again for any error checking or type filtering that should be added.
//TODO: ADD checks for VOID type and error on it.
Type typecheck_tuple(List types, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_tuple input: types: %s, line: %u\n", list_to_str(types, (str (*)(Anom))type_to_str), line);
  #endif
  return type_new(T_TUPLE, types);
}

//TODO: check this method again for any error checking/ type filtering that should be added.
//TODO: ADD checks for VOID type and error on it.
List typecheck_elements(Type type, List typelist, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_elements input: type: %s, typelist: %s, line: %u\n", type_to_str(type), list_to_str(typelist, (str (*)(Anom))type_to_str), line);
  #endif
  list_prepend(typelist, type);
  return typelist;
}


Type typecheck_assign(str id, Type type, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_fun_call input: id: %s, type: %s, line: %u\n", id, type_to_str(type), line);
  #endif
  Var var = get_var(id);
  if (var == NULL) {
    fprintf(stderr, "ERROR: Undefined identifier, line: %u,  Attempted to assign a value of type, %s, to identifier, \'%s\', which is not defined in the current scope.\n",
            line, type_to_str(type), id);
  } else if (!type_assign_cast(var_type(var), type, line)) {
    fprintf(stderr, "ERROR: Variable Assignment Type Mismatch near line: %u, Identifier, %s, of type: %s, Received: %s\n",
            line, id, type_to_str(var_type(var)), type_to_str(type));
  }
  //type_destroy(type);
  return type_new(T_VOID, NULL);
}


Type typecheck_if(Type cond, Type b_then, Type b_else, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_if input: Type cond: %s, Type b_then: %s, Type b_else: %s, line: %u\n", type_to_str(cond), type_to_str(b_then), type_to_str(b_else), line);
  #endif
  if (type_base(cond) != T_BOOL) {
    fprintf(stderr, "ERROR: Type Mismatch near line: %u, Expected: if %s,  Received: if %s\n",
            line, btype_to_str(T_BOOL), type_to_str(cond));
  }
  if (!type_eq(b_then, b_else)) {
    fprintf(stderr, "ERROR: Type Mismatch near line: %u, Missmatched return type for if block. Expected: then and else types to match, Received: then %s else %s\n",
            line, type_to_str(b_then), type_to_str(b_else));
  }
  //type_destroy(cond);
  //type_destroy(b_else);
  return b_then;
}


Type typecheck_while(Type cond, Type b_while, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_while input: Type cond: %s, Type b_while: %s, line: %u\n", type_to_str(cond), type_to_str(b_while), line);
  #endif
  if (type_base(cond) != T_BOOL) {
    fprintf(stderr, "ERROR: Type Mismatch near line: %u, Expected: if %s,  Received: if %s\n",
            line, btype_to_str(T_BOOL), type_to_str(cond));
  }
  return type_new(T_VOID, NULL);
}


Type typecheck_let(Type b_in, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_let input: Type b_in: %s, line: %u\n", type_to_str(b_in), line);
  #endif
  return b_in;
}


Type typecheck_dec(str id, Type type, Type b_eq, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_dec input: str id: %s, Type type: %s, Type b_eq: %s, line: %u\n", id, type_to_str(type), type_to_str(b_eq), line);
  #endif
  if ((type = type_assign_cast(type, b_eq, line))) {
    add_var(var_new(id, type), line);
  }
  return type_clone(type);
}


Type typecheck_type_ref(Type sub_ref, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_type_ref input: Type sub_ref: %s, line: %u\n", type_to_str(sub_ref) , line);
  #endif
  List list = list_new();
  if (sub_ref != NULL) {
    list_append(list, sub_ref);
  }
  return type_new(T_REF, list);
}


Type typecheck_type_basic(TYPE_BASE base, Type ref, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_type_basic input: TYPE_BASE base: %s, Type reg: %s, line: %u\n",  btype_to_str(base), type_to_str(ref), line);
  #endif
  Type ret;
  if (ref != NULL) {
    List sub = type_sub(ref);
    while (list_head(sub) != NULL) {
      sub = type_sub(list_head(sub));
    }
    list_append(sub, type_new(base, NULL));
    ret = ref;
  } else {
    ret = type_new(base, NULL);
  }
  return ret;
}

// TODO: double check logic
Type typecheck_type_basic_list(Type base, Type list, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_type_basic_list input: Type base: %s, Type list: %s, line: %u\n",  type_to_str(base), type_to_str(list), line);
  #endif
  Type ret;
  if (list != NULL) {
    ret = list;
    if (base != NULL) {
      List sub = type_sub(list);
      while (list_head(sub) != NULL) {
        if (type_sub(list_head(sub)) == NULL) {
          ((Type)list_head(sub))->sub = list_new();
        }
          sub = type_sub(list_head(sub));
      }
      list_append(sub, base);
    }
  } else if (base != NULL) {
    ret = base;
  }
  return ret;
}


Type typecheck_add_var(str name, Type type, int line) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: typecheck_add_var input: Str name: %s, Type type: %s, line: %u\n",  name, type_to_str(type), line);
  #endif
  add_var(var_new(name, type), line);
  return type;
}


//============================================================================//
//==============================Scoping functions=============================//
//============================================================================//

int get_scope_depth() {
  return scope_depth(current);
}


void push_scope(str name) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: push_scope: name: \"%s\"\n",  name);
    if (current == NULL) {
      fprintf(stderr, "SCOPE_WARNING: push_scope: Current scope is null. Pusing %s as global scope.\n", name);
    }
  #endif
  current = scope_new(name, current);
}


void pop_scope() {
  #ifdef DEBUG
    if (current == NULL) {
      fprintf(stderr, "SCOPE_ERROR: pop_scope: FALTAL current scope is null.  Did you forget to push a global scope first?\n");
      return;
    }
    if (scope_parent(current) == NULL) {
      fprintf(stderr, "SCOPE_ERROR: pop_scope: called when only global scope remains. Cowardly, Refusing to pop global scope.\n");
      return;
    }
    fprintf(stderr, "DEBUG: pop_scope: name: \"%s\"\n", scope_name(current));
  #endif
  
  Scope prev = current;
  current = scope_parent(current);
  scope_destroy(prev);
}

//TODO: add line based error reporting for existing variables.
void add_var(Var var, int line) {
  #ifdef DEFINE
    fprintf(stderr, "DEBUG: add_var input: Var: %s, line: %u\n",  var_to_str(var), name);
    if (current == NULL) {
      fprintf(stderr, "SCOPE_ERROR: add_var: FALTAL current scope is null.  Did you forget to push a global scope first?\n");
      return;
    }
  #endif
  if (scope_get_var(current, var_symbol(var)) || scope_get_fun(current, var_symbol(var))) {
    fprintf(stderr, "ERROR: line %u Redeclaration of identifier %s\n", line, var_symbol(var));
  }
  scope_add_var(current, var);
}


Var get_var(str symbol) {
  #ifdef DEBUG
    fprintf(stderr, "DEBUG: get_var input: Str symbol: %s\n",  symbol);
  #endif
  return scope_find_var(current, symbol);
}
