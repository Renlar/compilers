#ifndef COMP_LIST
#define COMP_LIST

#include <stdbool.h>

#include "void.h"

typedef struct list_node {
  Void data;
  struct list_node* next;
} list_node;
typedef list_node* ListNode;

int sizeof_listnode = sizeof(list_node);

typedef struct list {
  int length;
  ListNode head;
  ListNode tail;
} list;
typedef list* List;

int sizeof_list = sizeof(list);

List new_list();
ListNode new_listnode(Void data, ListNode next);
void list_destroy(List list);
 
/*
 * Insert the given data element at the beginning of the list.
 */
void list_prepend(List list, Void element);

/*
 * Insert the given data element at position, pos, in the list
 */
void list_insert(List list, Void element, int pos); 

/*
 * Add the given element to the end of the list.
 */
void list_append(List list, Void element);

/*
 * Return the number of elements in this list.
 */
int list_size(List list);
/*
 * Get the element at the given position in the list
 */
Void list_get(List list, int pos);

/*
 * Find an element in the list matching the given element matching using the
 * given equaltiy function.
 */
Void list_find(List list, bool (*eq)(Void, Void), Void element);

/*
 * Compare two lists using the given equality function for the elements.
 */
bool list_equal(List l1, List l2, bool (*eq)(Void, Void));
/*
 * Apply the provided function to ever element in the list.
 */
void list_for_each(List list, void (*fun)(Void));
/*
 * Return the data stored in the head of this list.
 */
Void list_head(List list);
/*
 * Return the data stored in the tail of this list.
 */
Void list_tail(List list);

//Private
/*
* Return the ListNode at the given position in the list.
*/
ListNode list_get_node(List list, int pos);
 
#endif//COMPLIST
