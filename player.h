#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL2/SDL.h>
#include "render.h"
#include "linkedlist.h"

#define SPEED 1

enum DIRECTION {NOT_MOVING, UP, DOWN, RIGHT, LEFT};

typedef struct {
    int direction, score, limit, level;
    unsigned long int headMoved;
} GameData;

typedef struct {
    int x, y;
} Apple;

void playerInit(Game *game, struct node **playerHead, GameData *gameData, int hx, int hy);
void playerMove(Game *game, struct node **playerHead, GameData *gameData);
void playerCollide(Game *game, struct node **playerHead, GameData *gameData);
void playerRender(Game *game, struct node *playerHead);
void playerGrow(Game *game, struct node *playerHead, GameData *gameData);

void appleInit(Game *game, Apple *apple);
void appleRender(Game *game, Apple *apple, struct node *playerHead, GameData *gameData);

void gameResize(Game *game, struct node **playerHead, GameData *gameData, Apple *apple, int w, int h);
#endif
