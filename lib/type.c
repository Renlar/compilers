#include "type.h"

#include <stdbool.h>

#include "list.h"

///////Private///////

///////End Private///////


Type new_type(TYPE base, List sub) {
  Type type = malloc(sizeof_type);
  type->base = base;
  type->sub = sub;
  if ((base != LIST || base != TUPLE) && sub != NULL) {
    printf("TYPE_ERROR: got %s with subtypes, expected LIST or TUPLE.", btype_to_str(base));
  }
  if (base == LIST) {
    if (!valid_list(type)) {
      printf("TYPE_SUBTYPE_ERROR: root type: LIST.  Expected single subtype, got multiple");
    }
  }
  Type added = add_type(type);
  if (added != type) {
    free(type);
    type = added;
  }
  return type;
}

void type_destroy(Type t) {
  if (t != NULL) {
    if (t->sub != NULL) {
    list_for_each(t->sub, type_destroy);
    list_destroy(t->sub);
    }
    free(t);
  }
}

Type type_upcast(Type t1, Type t2) {
   Type c = new_type()
   if (upcast(t1->base, t2->base)) {
     
   }
}

Type type_downcast(Type t1, Type t2) {
  if (t1 == NULL || t2 == NULL) {
    printf("TYPE_CAST_ERROR: downcast received NULL type.");
    return NULL;
  }
  if (t1->sub && t2->sub) {
    List sub = list_for_each_pair(t1->sub, t2->sub, type_downcast);
  } else {
    printf("TYPE_CAST_WARNING: complex types are incompatable due to missing subtypes");
    return NULL;
  }
  return new_type(downcast(t1->base, t2->base), sub);
}

bool can_upcast(TYPE t1, TYPE t2) {
  return (bool) upcast(TYPE t1, TYPE t2);
}

bool can_downcast(TYPE t1, TYPE t2) {
  return (bool) downcast(TYPE t1, TYPE t2);
}

TYPE upcast(TYPE t1, TYPE t2) {
  if (!t1 || !t2) {
    return ERROR;
  } else if (t1 > t2) {
    return t1;
  } else if (t1 < t2) {
    return t2;
  }
  return t1;
}

TYPE downcast(TYPE t1, TYPE t2) {
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

str btype_to_str(TYPE t) {
  if (t == ERROR) {
    return "ERROR";
  } else if (t == BOOL) {
    return "BOOL";
  } else if (t == INT) {
    return "INT";
  } else if (t == REAL) {
    return "REAL";
  } else if (t == LIST) {
    return "LIST";
  } else if (t == TUPLE) {
    return "TUPLE";
  }
  return "UNKNOWN";
}

//TODO: check this method.
bool valid_list(Type list) {
  if (list == NULL) {
    return false;
  }
  if (list->base == LIST) {
    if (list->sub != NULL) {
      if (list_head(list->sub) != NULL) {
        TYPE init = ((Type) list_head(list->sub))->base;
        bool correct = true;
        
        bool eq(Type t) {
          if (correct == false) {
            return;
          } else if (t == NULL) {
            correct = false;
          } else {
            correct = (t->base == init);
          }
        }
        
        list_for_each(list->sub, eq);
        return correct;
      }
    }
  }
}
