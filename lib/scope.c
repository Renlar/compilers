#include "scope.h"

Scope new_scope(str name, Scope parent) {
    Scope scope = malloc(sizeof_scope);
    scope->parent = parent;
    scope->name = name;
    scope->vars = new_list();
    scope->types = new_list();
    return scope;
}

Scope scope_parent(Scope scope) {
    return scope->parent;
}

str scope_name(Scope scope) {
    return scope->name;
}

Var scope_find_var(Scope scope, str symbol) {
    list_find
}

bool scope_has_var(Scope scope, str symbol) {
    
}

void scope_add_var(Scope scope, Var var) {
    
}

int scope_depth(Scope scope) {
    int depth = -1;
    while( scope != NULL ) {
        scope = scope_parent(scope);
        depth++;
    }
    return depth;
}
