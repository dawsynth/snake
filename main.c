#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "render.h"
#include "linkedlist.h"
#include "player.h"


int main(void)
{
    time_t t;
    srand((unsigned) time(&t));
    char title[100];
    Uint32 last_moved = 0;
    View* view = malloc(sizeof(View));
    init_view(view);

    Game *game = game_init(DEFAULT_BOARD);
    Snake* snake = snake_init(game);

    SDL_Event event;

    int closeRequested = 0;

    while (!closeRequested)
    {
        SDL_RenderClear(view->renderer);
        // Process all the events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    closeRequested = 1;
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
                            closeRequested = 1;
                        default:
                            break;
                    }
                    break;
            }
        }
        // Draw Image to Window
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

    // Clean up clean up everybody clean up
    term_view(view);
    game_destroy(game);
    snake_destroy(snake);
	return 0;
}

