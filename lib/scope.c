

Scope new_scope(str name, Scope parent) {
    Scope scope = malloc(sizeof_scope);
    scope->parent = parent;
    scope->name = name;
    scope->vars = new_list();
    scope->types = new_list());
    return scope;
}

Scope scope_parent(Scope scope) {
    return scope->parent;
}

/*
 * Get the current scope depth.
 */
int scope_depth(Scope scope) {
    int depth = -1;
    while( scope != NULL ) {
        scope = scope_parent(scope);
        depth++;
    }
    return depth;
}
