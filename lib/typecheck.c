#include "typecheck.h"

//Global data to store types and vars.
TypeList typelist = new_typelist();
CompatType comapttype = new_compattype();
Scope current = new_scope("global", NULL);


int get_stack_depth() {
    Scope cur = current;
    int depth = 0;
    while (cur->parent != NULL) {
        cur = cur->parent;
        depth++;
    }
    return depth;
}

void scope_push(str name) {
    Scope newscope = new_scope(name, current);
    current = newscope;
}

void scope_pop() { 
    if (current->parent != NULL) {
        current = current->parent;
    }
}

str scope_name() {
    return current->name;
}

void scope_add_var(str type, str var) {
    current->list
}

void scope_add_var(Type type, str var);
Var scope_get_var(str var);
Var scope_get_var(str var, Scope scope);
Type scope_type_get(str symbol);
void scope_add_type();



bool type_comp(Type t1, type t2);
bool type_dcomp(Type t1, Type t2);

void add_type(Type type);
Type contains_type(Type type);
Type contains_type(str type);


void add_upcast(Type up, Type down);
void add_downcast(Type up, Type down);
void compattype_add_root(Type root);
Type upcast(Type t1, Type t2);
bool downcast(Type lhs, Type rhs);


//Private
TypeList compatlist(Type type);


Type get_type(str name) {
    bool eq(Type type, str name) {
        return !strcmp(type->name, name);
    }
    return (Type) list_find(typelist, eq, name);
}

Type add_type(Type type) {
    Type found = list_find(typelist, type_equal, type);
    if(!found) {
        list_append(typelist, type);
    }
    return found;
}

void remove_type(Type type) {
    
}