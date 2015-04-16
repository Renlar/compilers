#ifndef COMP_VAR
#define COMP_VAR

#include <stdbool.h>

typedef struct var {
    bool isFunction;
    str name;
    Type type;
} var;
typedef var* Var;

int sizeof_var = sizeof(struct var);

Var new_var(str name, Type type, bool isFunction) {
    Var var = malloc(sizeof_var);
    var->name = name;
    var->type = type;
    var->isFunction = isFunction;
    return var;
}

str var_name(Var var) {
    return var->name;
}

Type var_type(Var var) {
    return var->type;
}

bool var_isFunc(Var var){
    return var->isFunction;
}

#endif//COMP_VAR