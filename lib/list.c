#include <stdlib.h>
 
#include "list.h"
 
///////Private///////
ListNode listnode_new(Anom dat, ListNode prev, ListNode next, List list);
/*
 * Links both node1 and node2 to eath other.  
 * Links node1's next to node2 and node2's previous to node1.  
 */
void link_nodes(LinkNode node1, LinkNode node2);

/*
 * Links the previous node to the next node and frees teh current node.
 */
void listnode_destroy(ListNode node);

/*
 * @arg list the list to navigate.
 * @arg pos the position of the desired element.
 * @return the ListNode at @pos if its exists NULL otherwise.
 */
ListNode list_get_node(List list, int pos);

/*
 * 
 */
void list_for_each_node(List list, void (*op)(ListNode node));

///////End Private///////

List list_new() {
  List list = malloc(sizeof_list);
  list->length = 0;
  list->head = list->tail = NULL;
  return list;
}


ListNode listnode_new(Anom data, ListNode prev, ListNode next, List list) {
  ListNode node = malloc(sizeof_listnode);
  node->data = data;
  link_nodes(prev, node);
  link_nodes(node, next);
  node->list = list;
  
  if (list) {
    if(!list->head) {
      list->head = node;
    }
    if(!list->tail) {
      list->tail = list->head;
    }
  }

  return node;
}


void link_nodes(LinkNode node1, LinkNode node2){
  if(node1 != NULL){
    node1->next = node2;
  }
  if(node2 != NULL){
    node2->prev = node1;
  }
}


void list_destroy(List list) {
  if (list != NULL) {
    ListNode current;
    void op(ListNode node) {
      free(node);
    }
    list_for_each_node(list, op);
  }
}


void listnode_destroy(ListNode node) {
  if (node != NULL) {
    link_nodes(node->prev, node->next);
    if (node->list != NULL) {
      if (node->list->head == node) {
        node->list->head = node->next;
      }
      if (node->list->tail == node) {
        node->list->tail = node->prev;
      }
    }
    free(node);
  }
}


void list_prepend(List list, Anom element) {
  if (list != NULL) {
    ListNode node = listnode_new(element, NULL, list->head, list);
    list->length++;
  }
}


void list_insert(List list, Anom element, int pos) {
  if (list != NULL) {
    if (pos < 0) {
      list_prepend(list, element);
    } else if (pos >= list_size(list)) {
      list_append(list, element);
    } else {
      ListNode pre = list_get_node(list, pos);
      if (pre == NULL) {
        listnode_new(element, NULL, NULL, list);
      } else {
        listnode_new(element, pre, pre->next, list);
      }
    }
    list->length++;
  }
}


void list_append(List list, Anom element) {
  if (list != NULL) {
    ListNode node = listnode_new(element, list->tail, NULL, list);
    list->length++;
  }
}


void list_append_list(List list, List append) {
  if (list != NULL && append != NULL) {
    void op(ListNode node) {
      list_append(list, node->data);
    }
    list_for_each(append, op);
  }
}


void list_remove(List list, Anom element) {
  if (list != NULL && element != NULL) {
    bool eq(Anom e1, Anom e2) {
      return e1 == e2;
    }
    Node node = list_find_node(list, eq, element);
    if (node != NULL) {
      listnode_destroy(node);
      list->length--;
    }
  }
}


void list_remove_pos(List list, int pos) {
  if (list != NULL && pos > -1) {
    ListNode node = list_get_node(list, pos);
    if (node != NULL) {
      listnode_destroy(node);
      list->length--;
    }
  }
}


void list_for_each(List list, void (*op)(Anom)) {
  void fun(ListNode node) {
    (*op)(node->data);
  }
  list_for_each_node(list, fun);
}


void list_for_each_node(List list, void (*op)(ListNode node)) {
  if (list != NULL) {
    ListNode node = list->head;
    while (node != NULL) {
      (*op)(node);
      node = node->next;
    }
  }
}


/*List list_for_each_pair(List list, List list, Anom (*op)(Anom)) {
  Anom fun(ListNode node1, ListNode node2) {
    return (*op)(node1->data, node2->data);
  }
  return list_for_each_pair_node(list, fun);
}


void list_for_each_pair_node(List list1, List list2, void (*op)(ListNode node)) {
  if (list1 != NULL) {
    ListNode node1 = list1->head, node2 = list2->head;
    
    while (node != NULL) {
      (*op)(node1, node2);
      if (node1 != NULL) {
        node1 = node1->next;
      }
      if (node2 != NULL) {
        node2 = node2->next;
      }
    }
  }
}*/


Anom list_head(List list) {
  if (list != NULL && list->head != NULL) {
    return list->head->data;
  }
  return NULL;
}


void list_behead(List list) {
  if (list != NULL && list->head != NULL) {
    listnode_destroy(node);
    list->length--;
  }
}


Anom list_tail(List list) {
  if (list == NULL && list->tail != NULL) {
    return list->tail->data;
  }
  return NULL;
}


void list_shorten(List list) {
  if (list != NULL && list->tail != NULL) {
    listnode_destroy(list->tail);
    list->length--;
  }
}


int list_size(List list) {
  if (list != NULL) {
    return list->length;
  }
  return 0;
}


Anom list_get(List list, int pos) {
  if (list != NULL && pos > -1) {
    ListNode node = list_get_node(list, pos);
    if (node != NULL) {
      return node->data;
    }
  }
  return NULL;
}


Anom list_find(List list, bool (*eq)(Anom, Anom), Anom element) {
  ListNode node = list_find_node(list, eq, element);
  if (node != NULL) {
    return node->data;
  }
  return NULL;
}


ListNode list_find_node(List list, bool (*eq)(Anom, Anom), Anom element) {
  if (list != NULL) {
    ListNode cur = list->head;
    while (cur != NULL) {
      if ((*eq)(element, cur->data)) {
        return cur;
      }
      cur = cur->next;
    }
  }
  return cur;
}


bool list_equal(List l1, List l2, bool (*eq)(Anom, Anom)) {
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
    return cur;
  }
  
  for (int i = 0; i < pos; i++) {
    if (cur == NULL) {
      break;
    }
    cur = cur->next
  }
  return cur;
}

/*str list_to_string(List list, str (*element_to_str)(Anom)) {
  
}*/