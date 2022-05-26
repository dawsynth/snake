#include "linkedlist.h"

Node* create_node(void* data) {
    Node* result = malloc(sizeof(Node));
    result->data = data;
    result->next = NULL;
    return result;
}

LinkedList* create_l_list(Node* head, Node* tail) {
    LinkedList* result = malloc(sizeof(LinkedList));

    result->head = head;
    result->tail = tail;
    result->size = 0;

    if (result->head != NULL || result->tail != NULL) {
        if (result->head != NULL && result->tail != NULL) {
            result->size += 2;
        } else if (result->tail != NULL) {
            result->size += 1;
            result->head = result->tail;
            result->tail = NULL;
        } else if (result->head != NULL) {
            result->size += 1;
        }
        result->head->next = result->tail;
    }

    if (result->head == result->tail && result->head != NULL) {
        result->head->next = NULL;
        result->tail = NULL;
        result->size = 1;
    }

    return result;
}

int l_list_insert_end(LinkedList* list, Node* to_insert) {
    int result = -1;
    if (to_insert != NULL) {
        if (list->head != NULL) {
            if (list->tail != NULL) {
                list->tail->next = to_insert;
            } else {
                list->head->next = to_insert;
            }
            list->tail = to_insert;
            to_insert->next = NULL;
        } else {
            list->head = to_insert;
        }
        list->size += 1;
        result = 0;
    }
    return result;
}

int l_list_insert_head(LinkedList* list, Node* to_insert) {
    int result = -1;
    if (to_insert != NULL) {
        to_insert->next = list->head;
        list->head = to_insert;
        list->size += 1;
        result = 0;
    }
    return result;
}

void destroy_l_list(LinkedList* list) {
    Node* tmp;
    while (list->head != NULL) {
        tmp = list->head;
        list->head = list->head->next;
        free(tmp->data);
        free(tmp);
    }
    free(list);
}

void empty_l_list(LinkedList* list) {
    Node* tmp;
    while (list->head != NULL) {
        tmp = list->head;
        list->head = list->head->next;
        free(tmp->data);
        free(tmp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

