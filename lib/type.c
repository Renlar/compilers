#include "type.h"

#include <stdbool.h>

#include "list.h"

///////Private///////
const int sizeof_type = sizeof(struct type);
///////End Private///////

//TODO: improve type error checking on construction.
Type type_new(TYPE_BASE base, List sub) {
  Type type = malloc(sizeof_type);
  type->base = base;
  type->sub = sub;
  if ((base != T_LIST && base != T_TUPLE && base != T_REF) && sub != NULL) {
    fprintf(stderr, "TYPE_BASE_WARNING: found %s with subtypes, expected LIST or TUPLE.\n", btype_to_str(base));
  }
  if (base == T_REF) {
    if (list_size(sub) > 1) {
      fprintf(stderr, "TYPE_BASE_WARNING: Found base type REF with more than a single subtype.\n");
    }
  }
  if (base == T_LIST) {
    if (!type_list_valid(type)) {
      fprintf(stderr, "TYPE_BASE_WARNING: Found base type LIST with multiple subtypes, Expected single subtype.\n");
    }
  }
  return type;
}


Type type_clone(Type type) {
  if (type != NULL) {
    return type_new(type_base(type), list_clone(type_sub(type), (Anom (*)(Anom))type_clone));
  }
  return NULL;
}


void type_destroy(Type t) {
  if (t != NULL) {
    if (type_sub(t) != NULL) {
    list_for_each(type_sub(t), (void (*)(Anom))type_destroy);
    list_destroy(type_sub(t));
    }
    free(t);
  }
}


TYPE_BASE type_base(Type type) {
  if (type == NULL) {
    fprintf(stderr, "TYPE_BASE_WARNING: type_base: received NULL argument, type.\n");
    return T_ERROR;
  }
  return type->base;
}


List type_sub(Type type) {
  if (type == NULL) {
    fprintf(stderr, "TYPE_BASE_WARNING: type_sub: received NULL argument, type.\n");
    return NULL;
  }
  return type->sub;
}

bool type_eq(Type t1, Type t2) {
  if (t1 == t2) {
    return true;
  } else if (t1 == NULL || t2 == NULL) {
    return false;
  }
  return type_base(t1) == type_base(t2) && list_equal(type_sub(t1), type_sub(t2), (bool (*)(Anom, Anom))type_eq);
}


//TODO: add special handling for lists and tuples.
Type type_upcast(Type t1, Type t2) {
  if (t1 == NULL || t2 == NULL) {
    fprintf(stderr, "TYPE_BASE_CAST_WARNING: type_upcast: received NULL type.\n");
    return NULL;
  }
  
  TYPE_BASE bt = upcast(type_base(t1), type_base(t2));
  List sub = list_for_each_pair(type_sub(t1), type_sub(t2), (Anom (*)(Anom, Anom))type_upcast);
  
  bool eq(Type a, Type b) {
    if (a != NULL) {
      return type_base(a) == T_ERROR;
    }
    return a == NULL;
  }
  
  if (bt != T_ERROR && !list_find(sub, (bool (*)(Anom, Anom))eq, NULL) && !list_find(sub, (bool (*)(Anom, Anom))eq, NULL)) {
    return type_new(bt, sub);
  } else {
    fprintf(stderr, "TYPE_BASE_CAST_WARNING: Upcast failure on %s, %s Incompatable types.", btype_to_str(type_base(t1)), btype_to_str(type_base(t2)));
    type_destroy(type_new(bt, sub));
    return type_new(T_ERROR, NULL);
  }
}

bool void_list(Type t) {
  if (t == NULL) {
    return false;
  }
  List sub = type_sub(t);
  while (sub != NULL) {
    Type subtype = list_head(sub);
    if (subtype == NULL) {
      return false;
    }
    if (type_base(subtype) == T_INT || type_base(subtype) == T_REAL || type_base(subtype) == T_BOOL) {
      return true;
    }
    sub = type_sub(subtype);
  }
  return false;
}

// TODO: fix discrepencies between this method and project2 specs for checking variable declarations 
Type type_assign_cast(Type lhs, Type rhs, int line) {
  Type ret;
  if (lhs == NULL && rhs == NULL) {
    fprintf(stderr, "TYPE_BASE_CAST_WARNING: type_assign_cast: received NULL types.\n");
    ret = NULL;
  } else if (lhs == NULL || rhs == NULL) {
    fprintf(stderr, "TYPE_BASE_CAST_WARNING: type_assign_cast: received NULL and non-NULL type.\n");
    if (lhs) {
      ret = lhs;
    } else {
      ret = rhs;
      }
  }
  if (lhs != NULL && type_base(lhs) != T_LIST) {
    ret = lhs;
    if (!type_eq(lhs, rhs)) {
      fprintf(stderr, "ERROR: near line: %u TYpe mismatch on variable declaration.", line);
    }
  } else if (void_list(lhs)) {
    if (void_list(rhs)) {
      ret = lhs;
      fprintf(stderr, "ERROR: near line: %u Unknown basic type for List, creating null list.", line);
    } else {
      ret = rhs;
    }
  }
  return ret;
}


bool can_assign_cast(TYPE_BASE lhs, TYPE_BASE rhs) {
  return ( downcast(lhs, rhs) == lhs || upcast(lhs, rhs) == lhs );
}


bool can_upcast(TYPE_BASE t1, TYPE_BASE t2) {
  return (bool) upcast(t1, t2);
}


bool can_downcast(TYPE_BASE t1, TYPE_BASE t2) {
  return (bool) downcast(t1, t2);
}


TYPE_BASE upcast(TYPE_BASE t1, TYPE_BASE t2) {
  if (!t1 || !t2) {
    return T_ERROR;
  } else if (t1 > t2) {
    return t1;
  } else if (t1 < t2) {
    return t2;
  }
  return t1;
}


TYPE_BASE downcast(TYPE_BASE t1, TYPE_BASE t2) {
  if (!t1 || !t2) {
    return T_ERROR;
  } else if (t1 == t2) {
    return t1;
  } else if (t1 == T_BOOL || t2 == T_BOOL) {
    return T_BOOL;
  } else if ( ( t1 == T_REAL && t2 == T_INT ) || ( t1 == T_INT && t2 == T_REAL ) ) {
    return T_INT;
  }
  return T_ERROR;
}


const str btype_to_str(TYPE_BASE t) {
  return TYPE_BASE_STR[t];
}


//TODO: check this method for errors.
bool type_list_valid(Type type) {
  if (type == NULL) {
    return false;
  }
  
  if (type_base(type) == T_LIST) {
    if (type_sub(type) != NULL) {
      if (list_head(type_sub(type)) != NULL) {
        
        TYPE_BASE init = type_base((Type) list_head(type_sub(type)));
        bool correct = true;
        
        void eq(Type t) {
          if (t == NULL && init != T_ERROR) {
            correct = false;
          } else if (correct != false) {
            correct = (type_base(t) == init);
          }
        }
        
        list_for_each(type_sub(type), (void (*)(Anom))eq);
        return correct;
      }
    }
    return true;
  }
  return false;
}


//TODO: improve implementation to print out all type information.
str type_to_str(Type type) {
  return (str) btype_to_str(type_base(type));
}


bool type_list_type_defined(Type type) {
  if (type == NULL) {
    return false;
  }
  List sub = type_sub(type);
  while (sub != NULL) {
    if (type_base(list_head(sub)) == T_REAL || type_base(list_head(sub)) == T_INT || type_base(list_head(sub)) == T_BOOL) {
      return true;
    }
  }
  return false;
}
