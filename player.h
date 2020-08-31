#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "render.h"

#define SPEED 1

typedef struct {
    int hx, hy;
    int direction;
    int score, limit, level;
    unsigned long int headMoved;
    SDL_Rect body[6000];
} Player;

typedef struct {
    int x, y;
} Apple;

void playerInit(Game *game, Player *player, int x, int y);
void appleInit(Game *game, Apple *apple);
void renderPlayer(Game *game, Player *player);
void growPlayer(Game *game, Player *player);
void renderApple(Game *game, Apple *apple, Player *player);
void gameResize(Game *game, Player *player, Apple *apple, int w, int h);
#endif
