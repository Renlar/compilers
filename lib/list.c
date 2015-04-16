#include <stdlib.h>
 
#include "list.h"
 
List list_new()
{
  List list = malloc(sizeof_list);
  list->length = 0;
  list->head = list->tail = NULL;
  return list;
}

ListNode new_listnode(Void data, ListNode next) {
  ListNode node = malloc(sizeof_listnode);
  node->data = data;
  node->next = next;
  return node;
}

void destroy_list(List list)
{
  ListNode current;
  while(list->head != NULL) {
    current = list->head;
    list->head = current->next;
    free(current);
  }
}

void list_prepend(List list, Void element)
{
  ListNode node = new_listnode(element, list->head);
  list->head = node;
 
  if(!list->tail) {
    list->tail = list->head;
  }
 
  list->length++;
}

void list_insert(List list, Void element, int pos) {
  ListNode pre = list_get_node(list, pos);
  ListNode node = new_listnode(element, pre->next);
  pre->next = node;
  
  list->length++;
}
 
void list_append(List list, Void element)
{
  ListNode node = new_listnode(element, NULL);
  if (list == NULL) {
    return;
  }
  if(list->length == 0) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
 
  list->length++;
}
 
void list_for_each(List list, void (*fun)(Void))
{
  if (fun == NULL || list == NULL) {
    return;
  }
 
  ListNode node = list->head;
  while(node != NULL) {
    (*fun)(node->data);
    node = node->next;
  }
}
 
Void list_head(list *list)
{
  if (list == NULL) {
    return NULL;
  }
  if (list->head != NULL) {
    return list->head->data;
  }
  return NULL;
}
 
Void list_tail(List list)
{
  if (list == NULL) {
    return NULL;
  }
  if (list->tail != NULL) {
    return list->tail->data;
  }
  return NULL;
}
 
int list_size(List list)
{
  if (list == NULL) {
    return 0;
  }
  return list->length;
}

Void list_get(List list, int pos) {
  if (list == NULL || pos < 0) {
    return NULL;
  }
  return list_get_node(list, pos)->data;
}

Void list_find(List list, bool (*eq)(Void, Void), Void element) {
  if (list == NULL) {
    return NULL;
  }
  ListNode cur = list->head;
  while (cur != NULL) {
    if ((*eq)(element, cur->data)) {
      return cur->data;
    }
    cur = cur->next;
  }
  return NULL;
}

bool list_equal(List l1, List l2, bool (*eq)(Void, Void)) {
  if (l1 == l2) {
    return true;
  } else if (l1 == NULL || l2 == NULL) {
    return false;
  }
  
  ListNode cur1 = l1->head;
  ListNode cur2 = l2->head;
  
  while (cur1 != NULL && cur2 != NULL) {
    if (!(*eq)(cur1->data, cur2->data)) {
      return false;
    }
  }
  if ((cur1 == NULL && cur2 != NULL) ||
      (cur1 != NULL && cur2 == NULL)) {
    return false;
  }
  return true;
}

//Private
ListNode list_get_node(List list, int pos) {
  ListNode cur = list->head;
  if (cur == NULL) {
    return NULL;
  }
  
  for (int i = 0; i < pos; i++) {
    cur = cur->next;
    if (cur == NULL) {
      return NULL;
    }
  }
  return cur;
}