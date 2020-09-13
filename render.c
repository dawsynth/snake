#include "render.h"


void gameInit(Game *game)
{
    // Attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }
    game->window  = SDL_CreateWindow("Snake",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
	if (!game->window)
	{
		printf("Error Creating Window: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

    // Create renderer which sets up graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    game->renderer = SDL_CreateRenderer(game->window, -1, render_flags);
    if (!game->renderer)
    {
        printf("Error Creating Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        return;
    }
    game->time = 0;
    game->w = DEFAULT_WINDOW_WIDTH;
    game->h = DEFAULT_WINDOW_HEIGHT;
    return;
}


void gameTerm(Game **game)
{
    SDL_DestroyRenderer((*game)->renderer);
	SDL_DestroyWindow((*game)->window);
	SDL_Quit();    
    free(*game);
}

