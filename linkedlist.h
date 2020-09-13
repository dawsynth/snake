#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stdlib.h>
#include <SDL2/SDL.h>

struct node{
    SDL_Rect bodyPart;
    struct node *next;
    struct node *prev;
};

void nodeInsertEnd(struct node **head, struct node *toInsert);
void nodeInsertHead(struct node **head, struct node *toInsert);
struct node *nodeCreate(SDL_Rect *bodyPart);
void nodesFree(struct node **head, int leaveHead);

#endif

