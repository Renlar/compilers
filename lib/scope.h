#ifndef COMP_SCOPE
#define COMP_SCOPE

struct scope {
    struct scope parent;
    str name;
    List vars;
    List types;
}
typedef Scope struct scope*;

int sizeof_scope = sizeof(struct scope);

Scope new_scope(str name, Scope parent) {
    Scope scope = malloc(sizeof_scope);
    scope->parent = parent;
    scope->name = name;
    scope->vars = new_list();
    scope->types = new_list());
    return scope;
}


#endif//COMP_SCOPE
