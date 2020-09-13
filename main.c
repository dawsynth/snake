#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "render.h"
#include "linkedlist.h"
#include "player.h"


int main(void)
{
    char title[100];
    Game *game = malloc(sizeof(Game));
    gameInit(game);

    struct node *playerHead = NULL;
    playerHead = nodeCreate(&(SDL_Rect) {.x = 0, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT});

    GameData *gameData = malloc(sizeof(GameData));
    Apple *apple = malloc(sizeof(Apple));

    playerInit(game, &playerHead, gameData, 0, 0);
    appleInit(game, apple);
    SDL_Event event;

    int closeRequested = 0;

    while (!closeRequested)
    {
        SDL_RenderClear(game->renderer);
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
                            if (gameData->direction == DOWN && gameData->score > 0) break;
                            else gameData->direction = UP;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            if (gameData->direction == UP && gameData->score > 0) break;
                            else gameData->direction = DOWN;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            if (gameData->direction == RIGHT && gameData->score > 0) break;
                            else gameData->direction = LEFT; 
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            if (gameData->direction == LEFT && gameData->score > 0) break;
                            else gameData->direction = RIGHT;
                            break;
                        case SDL_SCANCODE_1:
                            gameResize(game, &playerHead, gameData, apple, 100, 100);
                            break;
                        case SDL_SCANCODE_2:
                            gameResize(game, &playerHead, gameData, apple, 200, 200); 
                            break;
                        case SDL_SCANCODE_3:
                            gameResize(game, &playerHead, gameData, apple, 300, 300); 
                            break;
                        case SDL_SCANCODE_4:
                            gameResize(game, &playerHead, gameData, apple, 400, 400); 
                            break;
                        case SDL_SCANCODE_5:
                            gameResize(game, &playerHead, gameData, apple, 500, 500); 
                            break;
                        case SDL_SCANCODE_6:
                            gameResize(game, &playerHead, gameData, apple, 600, 600); 
                            break;
                        case SDL_SCANCODE_7:
                            gameResize(game, &playerHead, gameData, apple, 700, 700); 
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
        game->time = SDL_GetTicks();
        if (gameData->headMoved + gameData->limit < game->time)
        {
            playerMove(game, &playerHead, gameData);
            playerCollide(game, &playerHead, gameData);
            gameData->headMoved = game->time;
        }
        playerRender(game, playerHead);
        appleRender(game, apple, playerHead, gameData);
        sprintf(title, "SNAKE ------Score: %d  Level: %d------", gameData->score, gameData->level);
        SDL_SetWindowTitle(game->window, title);
        SDL_RenderPresent(game->renderer);
    }

    // Clean up clean up everybody clean up
    gameTerm(&game);
    nodesFree(&playerHead, 1);
    free(gameData);
    free(apple);
	return 0;
}

