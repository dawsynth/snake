#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


#define DEFAULT_WINDOW_WIDTH (400)
#define DEFAULT_WINDOW_HEIGHT (400)
#define TILE_WIDTH 10
#define TILE_HEIGHT 10
#define SCALAR 2


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned long int time;
    int w, h;
} Game;


void gameInit(Game *game);
void gameTerm(Game *game);
SDL_Texture *loadTexture(Game *game, const char *file);
#endif
