#include "linkedlist.h"

void nodeInsertEnd(struct node **head, struct node *toInsert)
{
    toInsert->next = *head;
    if ((*head)->prev != NULL)
    {
        toInsert->prev = (*head)->prev;
        (*head)->prev->next = toInsert;
    }
    else 
    {
        toInsert->prev = *head;
        (*head)->next = toInsert;
    }
    (*head)->prev = toInsert;
    return;
}
void nodeInsertHead(struct node **head, struct node *toInsert)
{
    toInsert->next = *head;
    if ((*head)->prev != NULL)
    {
        toInsert->prev = (*head)->prev;
        (*head)->prev->next = toInsert;
    }
    else toInsert->prev = *head;
    (*head)->prev = toInsert;
    *head = toInsert;
    return;
}
struct node *nodeCreate(SDL_Rect *bodyPart)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->bodyPart = *bodyPart;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void nodesFree(struct node **head, int leaveHead)
{
    struct node *tmp = NULL;
    if ((*head)->prev != NULL)
    {
        struct node *tail = (*head)->prev;
        for (tmp = tail; tail != *head; tmp = tail)
        {
            tail = tmp->prev;
            free(tmp);
        }
    }
    if (!leaveHead) free(*head);
    else if (leaveHead) 
    {
        (*head)->next = NULL;
        (*head)->prev = NULL;
    }
    return; 
}

