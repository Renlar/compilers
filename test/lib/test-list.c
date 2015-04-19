#include </home/ubuntu/workspace/lib/list.h>
#include </home/ubuntu/workspace/lib/string.h>

#include <stdio.h>

void main()
{
    printf("-----Test Start-----\n");
    printf("---List---\n");
    List mainList = list_new();
    
    printf("New Node Test (append, prepend, and inset):\n");
    int a = 2;
    list_append(mainList, &a);
    int b = 9;
    list_prepend(mainList, &b);
    
    int c = 8;
    list_insert(mainList, &c, 1);
    int d = 9;
    list_insert(mainList, &a, 5);
    list_insert(mainList, &d, -1);
    printf("Behead the snake:\n");
    list_behead(mainList);
    
    if (list_head(mainList) == &c) {
        printf("Successfully decapitated.\n");
    }
    
    List appendList = list_new();
    list_append(appendList, &a);
    list_append(appendList, &b);
    
    printf("Test List Append List:\n");
    list_append_list(mainList, appendList);
    int* tail = list_tail(mainList);
    if(tail != &b){
        printf("Append List failed.  Tail element should have pointing to b");
    }
    int* head = list_head(mainList);
    if(head != &b){
        printf("Append List failed.  Tail element should have pointing to b");
    }
    
    printf("---List---\n");
    printf("-----Test End-----\n");
}