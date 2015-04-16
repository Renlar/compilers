#ifndef COMP_CAST
#define COMP_CAST


/*
 *
 */
void add_upcast(Type up, Type down);
void add_downcast(Type up, Type down);
void compattype_add_root(Type root);
Type upcast(Type t1, Type t2);
bool downcast(Type lhs, Type rhs);

#endif//COMP_CAST
