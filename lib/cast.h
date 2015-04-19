#ifndef COMP_CAST
#define COMP_CAST

#include <stdbool.h>
#include "type.h"
#include "graph.h"


/*
 * Initializes the cast manager must be called before any other methods in
 * this header are otherwise they will not do anything.
 */
void setup_casting();

/*
 * Creates the specified upcast in the cast list.
 * @arg up, the type to upcast to.
 * @arg down, the type to upcast from.
 */
void add_upcast(Type up, Type down);

/*
 * Creates the specified upcast in the cast list.
 * @arg up, the type to downcast from.
 * @arg down, the type to downcast to..
 */
void add_downcast(Type up, Type down);

/*
 * Adds a root level type to the type graph.  Root types are attached to the 
 * NULL node in the middle of the graph and are used as a base for type casting.
 * @arg root, the root level type to add to the graph.
 */
void compattype_add_root(Type root);

/*
 * Compute the upcast between the two given types, @t1 and @t2
 * @arg t1 
 * @arg t2
 * @return the parent type if a path exists between the two types, else returns
 *         NULL.  Note if both types can be found from the other the cast path
 *         taken between the two types will be the one with the fewest hops.
 */
Type upcast(Type t1, Type t2);

/*
 * Find the downcast between types @t1 and @t1
 * @arg t1
 * @arg t2
 * @return the child type if a cast between the given types exists, else return 
 *         NULL.  Note if both types can be found from the other the cast path
 *         taken between the two types will be the one with the fewest hops.
 */
Type downcast(Type t1, Type t2);

/*
 * Generate the down or upcast as required to perform the assignment to a
 * variable of type @lhs.
 * @arg lhs 
 * @arg rhs 
 * @return the type to cast the rhs to in order to store it in the lhs.
 */
Type assignment_cast(Type lhs, Type rhs);

#endif//COMP_CAST
