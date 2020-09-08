#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "render.h"

#define SPEED 1


struct node{
    SDL_Rect bodyPart;
    struct node* next;
    struct node* prev;
};
typedef struct node PlayerNode;

typedef struct {
    int direction, score, limit, level;
    unsigned long int headMoved;
} GameData;

typedef struct {
    int x, y;
} Apple;

void playerInit(Game *game, PlayerNode *playerHead, GameData *gameData, int hx, int hy);
void appleInit(Game *game, Apple *apple);
void renderPlayer(Game *game, PlayerNode *playerHead, GameData *gameData);
void growPlayer(Game *game, PlayerNode *playerHead, GameData *gameData);
void renderApple(Game *game, Apple *apple, PlayerNode *playerHead, GameData *gameData);
void gameResize(Game *game, PlayerNode *playerHead, GameData *gameData, Apple *apple, int w, int h);
#endif
