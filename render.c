#include "render.h"


void init_view(View* view)
{
    // Attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }
    view->window  = SDL_CreateWindow("Snake",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     DEFAULT_WINDOW_SIZE, DEFAULT_WINDOW_SIZE, 0);
	if (!view->window)
	{
		printf("Error Creating Window: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

    // Create renderer which sets up graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    view->renderer = SDL_CreateRenderer(view->window, -1, render_flags);
    if (!view->renderer)
    {
        printf("Error Creating Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(view->window);
        SDL_Quit();
        return;
    }
    view->time = 0;
    view->w = DEFAULT_WINDOW_SIZE;
    view->h = DEFAULT_WINDOW_SIZE;
}


void term_view(View* view)
{
    SDL_DestroyRenderer(view->renderer);
	SDL_DestroyWindow(view->window);
	SDL_Quit();
    free(view);
}

void draw_game(SDL_Renderer* renderer, Game* game) {
    Uint8 r, g, b;
    for (int i = 0; i < game->board_size; i++) {
        for (int j = 0; j < game->board_size; j++) {
            SDL_Rect tile = (SDL_Rect){.x = j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            switch (game->board[i][j]) {
                case EMPTY:
                    r = 0;
                    g = 0;
                    b = 0;
                    break;
                case SNAKE:
                    r = 255;
                    g = 255;
                    b = 255;
                    break;
                case APPLE:
                    r = 255;
                    g = 0;
                    b = 0;
                    break;
            }
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

