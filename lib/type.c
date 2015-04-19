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
    printf("TYPE_ERROR: found %s with subtypes, expected LIST or TUPLE.\n", btype_to_str(base));
  }
  if (base == LIST) {
    if (!valid_list(type)) {
      printf("TYPE_SUBTYPE_ERROR: root type: LIST.  Expected single subtype, found multiple.\n");
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

//TODO: finish type_upcast and type_downcast.
Type type_upcast(Type t1, Type t2) {
  if (t1 == NULL || t2 == NULL) {
    printf("TYPE_CAST_ERROR: type_upcast: received NULL type.\n");
    return NULL;
  }
   Type c = new_type()
   if (upcast(type_base(t1), type_base(t2))) {
     
   }
}


Type type_downcast(Type t1, Type t2) {
  if (t1 == NULL || t2 == NULL) {
    printf("TYPE_CAST_ERROR: type_downcast: received NULL type.\n");
    return NULL;
  }
  if (t1->sub && t2->sub) {
    List sub = list_for_each_pair(type_sub(sub), type_sub(t2), type_downcast);
  } else {
    printf("TYPE_CAST_WARNING: type_downcast: complex types are incompatable due to missing subtypes.\n");
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
