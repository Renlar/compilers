#include "type.h"

#include <stdbool.h>

#include "list.h"

///////Private///////

///////End Private///////


Type type_new(TYPE_BASE base, List sub) {
  Type type = malloc(sizeof_type);
  type->base = base;
  type->sub = sub;
  if ((base != LIST || base != TUPLE) && sub != NULL) {
    printf("TYPE_BASE_ERROR: found %s with subtypes, expected LIST or TUPLE.\n", btype_to_str(base));
  }
  if (base == LIST) {
    if (!valid_list(type)) {
      printf("TYPE_BASE_SUBTYPE_BASE_ERROR: root type: LIST.  Expected single subtype, found multiple.\n");
    }
  }
  return type;
}


void type_destroy(Type t) {
  if (t != NULL) {
    if (type_sub(t) != NULL) {
    list_for_each(type_sub(t), (void (*)(void *))type_destroy);
    list_destroy(type_sub(t));
    }
    free(t);
  }
}


TYPE_BASE type_base(Type type) {
  if (type == NULL) {
    printf("TYPE_BASE_ERROR: type_base: received NULL argument, type.");
    return ERROR;
  }
  return type->base;
}


List type_sub(Type type) {
  if (type == NULL) {
    printf("TYPE_BASE_ERROR: type_sub: received NULL argument, type.");
    return NULL;
  }
  return type->sub;
}


//TODO: add special handling for lists and tuples.
Type type_upcast(Type t1, Type t2) {
  if (t1 == NULL || t2 == NULL) {
    printf("TYPE_BASE_CAST_ERROR: type_upcast: received NULL type.\n");
    return NULL;
  }
  
  TYPE_BASE bt = upcast(type_base(t1), type_base(t2));
  List sub = list_for_each_pair(type_sub(t1), type_sub(t2), type_upcast);
  
  bool eq(Type a, Type b) {
    if (a != NULL) {
      return type_base(a) == ERROR;
    }
    return a == NULL;
  }
  
  if (bt != ERROR && !list_find(sub, eq, NULL) && !list_find(sub, eq, NULL)) {
    return type_new(bt, sub);
  } else {
    printf("TYPE_BASE_CAST_ERROR: Upcast failure on %s, %s Incompatable types.", btype_to_str(type_base(t1)), btype_to_str(type_base(t2)));
    type_destroy(type_new(bt, sub));
    return type_new(ERROR, NULL);
  }
}


bool type_assign_cast(Type lhs, Type rhs) {
  if (lhs == NULL && rhs == NULL) {
    printf("TYPE_BASE_CAST_WARNING: type_assign_cast: received NULL types.\n");
    return true;
  } else if (lhs == NULL || rhs == NULL) {
    printf("TYPE_BASE_CAST_WARNING: type_assign_cast: received NULL and non NULL types.\n");
    return false;
  }
  bool eq(bool a, bool b) {
    return a == b;
  }
  bool sub_incompat = (bool) list_find(list_for_each_pair(type_sub(lhs), type_sub(rhs), type_assign_cast), eq, false);
  return (can_assign_cast(type_base(lhs), type_base(rhs)) && !sub_incompat);
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
    return ERROR;
  } else if (t1 > t2) {
    return t1;
  } else if (t1 < t2) {
    return t2;
  }
  return t1;
}


TYPE_BASE downcast(TYPE_BASE t1, TYPE_BASE t2) {
  if (!t1 || !t2) {
    return ERROR;
  } else if (t1 == t2) {
    return t1;
  } else if (t1 == BOOL || t2 == BOOL) {
    return BOOL;
  } else if (t1 == REAL && t2 == INT || t1 == INT && t2 == REAL) {
    return INT;
  }
  return ERROR;
}


str btype_to_str(TYPE_BASE t) {
  str r;
  if (t == ERROR) {
    r = str_new("ERROR");
  } else if (t == BOOL) {
    r = str_new("BOOL");
  } else if (t == INT) {
    r = str_new("INT");
  } else if (t == REAL) {
    r = str_new("REAL");
  } else if (t == LIST) {
    r = str_new("LIST");
  } else if (t == TUPLE) {
    r = str_new("TUPLE");
  } else {
    r = str_new("UNKNOWN");
  }
  return r;
}


//TODO: check this method for errors.
bool valid_list(Type type) {
  if (type == NULL) {
    return false;
  }
  
  if (type_base(type) == LIST) {
    if (type_sub(type) != NULL) {
      if (list_head(type_sub(type)) != NULL) {
        
        TYPE_BASE init = type_base((Type) list_head(type_sub(type)));
        bool correct = true;
        
        bool eq(Type t) {
          if (correct == false) {
            return;
          } else if (t == NULL) {
            correct = false;
          } else {
            correct = (type_base(t) == init);
          }
        }
        
        list_for_each(type_sub(type), eq);
        return correct;
      }
    }
    return true;
  }
  return false;
}
