#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "render.h"
#include "linkedlist.h"
#include "player.h"

char title[100];
Uint32 last_moved = 0;
View* view;
Game* game;
Snake* snake;
SDL_Event event;
int close_requested = 0;

void update_frame() {
    SDL_RenderClear(view->renderer);
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        if (snake->direction == DOWN && game->score > 0) break;
                        else snake->direction = UP;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        if (snake->direction == UP && game->score > 0) break;
                        else snake->direction = DOWN;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        if (snake->direction == RIGHT && game->score > 0) break;
                        else snake->direction = LEFT; 
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        if (snake->direction == LEFT && game->score > 0) break;
                        else snake->direction = RIGHT;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        close_requested = 1;
                    default:
                        break;
                }
                break;
        }
    }
    view->time = SDL_GetTicks();
    if (last_moved + 100 <= view->time)
    {
        game_update(game, snake);
        last_moved = view->time;
    }
    draw_game(view->renderer, game);
    sprintf(title, "SNAKE ------Score: %d  Level: %d------", game->score, game->level);
    SDL_SetWindowTitle(view->window, title);
    SDL_RenderPresent(view->renderer);
}


int main(void)
{
    time_t t;
    srand((unsigned) time(&t));
    view = malloc(sizeof(View));
    init_view(view);

    game = game_init(DEFAULT_BOARD);
    snake = snake_init(game);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(update_frame, 0, 1);
    #else
    while (!close_requested)
    {
        update_frame();
    }
    #endif

    term_view(view);
    game_destroy(game);
    snake_destroy(snake);
	return 0;
}

