#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "player.h"

#define TILE_SIZE 10
#define DEFAULT_WINDOW_SIZE (TILE_SIZE * DEFAULT_BOARD)

typedef struct _View {
    SDL_Window* window;
    SDL_Renderer* renderer;
    unsigned long int time;
    int w, h;
} View;

void init_view(View* view);
void term_view(View* view);

void draw_game(SDL_Renderer* renderer, Game* game);

#endif
