#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "render.h"
#include "player.h"


int main(void)
{
    char title[100];
    Game game;
    gameInit(&game);

    Player player;
    Apple apple;
    playerInit(&game, &player, 0, 0);
    appleInit(&game, &apple);
    SDL_Event event;

    int closeRequested = 0;

    while (!closeRequested)
    {
        SDL_RenderClear(game.renderer);
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
                            if (player.direction == 1 && player.score > 0) break;
                            else player.direction = 2;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            if (player.direction == 2 && player.score > 0) break;
                            else player.direction = 1;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            if (player.direction == 3 && player.score > 0) break;
                            else player.direction = 4; 
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            if (player.direction == 4 && player.score > 0) break;
                            else player.direction = 3;
                            break;
                        case SDL_SCANCODE_1:
                            gameResize(&game, &player, &apple, 100, 100);
                            break;
                        case SDL_SCANCODE_2:
                            gameResize(&game, &player, &apple, 200, 200); 
                            break;
                        case SDL_SCANCODE_3:
                            gameResize(&game, &player, &apple, 300, 300); 
                            break;
                        case SDL_SCANCODE_4:
                            gameResize(&game, &player, &apple, 400, 400); 
                            break;
                        case SDL_SCANCODE_5:
                            gameResize(&game, &player, &apple, 500, 500); 
                            break;
                        case SDL_SCANCODE_6:
                            gameResize(&game, &player, &apple, 600, 600); 
                            break;
                        case SDL_SCANCODE_7:
                            gameResize(&game, &player, &apple, 700, 700); 
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
        game.time = SDL_GetTicks();
        renderPlayer(&game, &player);
        renderApple(&game, &apple, &player);
        sprintf(title, "SNAKE ------Score: %d  Level: %d------", player.score, player.level);
        SDL_SetWindowTitle(game.window, title); 
        SDL_RenderPresent(game.renderer);
    }

    // Clean up clean up everybody clean up
    gameTerm(&game);
	return 0;
}

