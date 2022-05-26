#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>

typedef struct _Node {
    void* data;
    struct _Node* next;
} Node;

typedef struct _LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

Node* create_node(void* data);
LinkedList* create_l_list(Node* head, Node* tail);
int l_list_insert_end(LinkedList* list, Node* to_insert);
int l_list_insert_head(LinkedList* list, Node* to_insert);
void empty_l_list(LinkedList* list);
void destroy_l_list(LinkedList* list);

#endif

