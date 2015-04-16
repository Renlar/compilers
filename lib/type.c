#include "type.h"
#include "list.h"

Type new_type(str name) {
    Type type = malloc(sizeof_type);
    type->name = name;
    type->sub = NULL;
    Type added = add_type(type);
    if (added != type) {
        free(type);
        type = added;
    }
    return type;
}

Type new_atype() {
    Type type = malloc(sizeof_type);
    type->name = atype_name();
    type->sub = NULL;
    if (added != type) {
        free(type);
        type = added;
    }
    return type;
}

bool type_equal(Type t1, Type t2) {
    if (t1 == t2 || !strcmp(t1->name, t2->name)) {
        return true;
    } else if (t1 == NULL || t2 == NULL) {
        return false;
    } else {
        return list_equal(t1->sub, t2->sub, type_equal);
    }
}

Type get_type(str name) {
    bool eq(Type type, str name) {
        return !strcmp(type->name, name);
    }
    return (Type) list_find(typelist, eq, name);
}


str new_atype_name() {
    static unsigned int atype_count = 0;
    unsigned int c = atype_count;
    int size = 6;
    while (c > 0) {
        c = c / 10;
        size++;
    }
    str atype_name = malloc(size);
    *atype_name = "anonT"
    c = atype_count;
    for (int i = 5; i < size-2; i++) {
        *(atype_name + i) = c % 10;
        c = c / 10;
    }
    *(atype_name + size - 1) = '\0'
    
    atype_count++;
    return atype_name;
}

Type add_type(Type type) {
    Type found = list_find(typelist, type_equal, type);
    if(!found) {
        list_append(typelist, type);
    }
    return found;
}

Type 
