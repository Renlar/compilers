#ifndef COMP_LIST
#define COMP_LIST

#include <stdbool.h>

#include "anom.h"

struct list;

typedef struct list_node {
  Anom data;
  struct list_node* next;
  struct list_node* prev;
  struct list* list;
} list_node;
typedef list_node* ListNode;

const int sizeof_listnode = sizeof(list_node);

typedef struct list {
  int length;
  ListNode head;
  ListNode tail;
} list;
typedef list* List;

const int sizeof_list = sizeof(list);

List list_new();

/*
 * Return the number of elements in this list.
 */
int list_size(List list);

/*
 * Destroy the passed in list.
 * WARNING: Does not delete any of the data stored in the list this must be
 *          done separately with a call to
 *          list_for_each(list, data_destroy_function)
 * @arg list the List to free the allocated memory of.
 */
void list_destroy(List list);
 
/*
 * Insert the given data element at the beginning of the list.
 */
void list_prepend(List list, Anom element);

/*
 * Insert the given data element at position, pos, in the list
 */
void list_insert(List list, Anom element, int pos);

/*
 * Add the given element to the end of the list.
 */
void list_append(List list, Anom element);

/*
 * Adds all elements in append to the end of list.  
 */
void list_append_list(List list, List append);

/*
 * Deletes the given element from the passed in list.  
 */
void list_remove(List list, Anom element);

/*
 * Removes an element from the list.  Does not delete data.
 * @arg list the list to delete an element from.
 * @arg pos the position of the element to remove from the list.
 */
void list_remove_pos(List list, int pos);

/*
 * Return the data stored in the head of this list.
 * @arg list the list to operate on
 * @return the element stored in the first node in the list.
 */
Anom list_head(List list);

/*
 * Place the head of this list in the guillotine.  Off with his head!
 * @arg list the list to behead.
 */
void list_behead(List list);

/*
 * Return the data stored in the tail of this list.
 */
Anom list_tail(List list);

/*
 * Remove the tail element from the list.  Need to keep the snakes in check.
 * @arg list the list to cut the tail off of.
 */
void list_shorten(List list);

/*
 * Get the element at the given position in the list
 */
Anom list_get(List list, int pos);

//TODO: change find method to return a position instead of a pointer to data.

/*
 * Find an element in the list matching the given element matching using the
 * given equaltiy function.
 */
Anom list_find(List list, bool (*eq)(Anom, Anom), Anom element);

/*
 * Compare two lists using the given equality function for the elements.
 */
bool list_equal(List l1, List l2, bool (*eq)(Anom, Anom));

/*
 * Apply the provided function to every data entry in the list.
 * @list the list to operate on.
 * @op the function to apply to the contents of the list.
 */
void list_for_each(List list, void (*op)(Anom));

List list_for_each_pair(List list1, List list2, Anom (*op)(Anom, Anom));

//str list_to_string(List list, str (*element_to_str)(Anom));


#endif//COMPLISTs
