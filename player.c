#include "player.h"

void playerInit(Game *game, PlayerNode *playerHead, GameData *gameData, int hx, int hy)
{
    PlayerNode *tmp = playerHead;
    tmp = tmp->prev;
    while (tmp != NULL)
    {
        if (tmp->next != NULL) free(tmp->next);
        tmp = tmp->prev;
    }
    playerHead->bodyPart.x = hx;
    playerHead->bodyPart.y = hy;
    playerHead->bodyPart.w = TILE_WIDTH;
    playerHead->bodyPart.h = TILE_HEIGHT;
    
    gameData->direction = 0;
    gameData->score = 0;
    gameData->limit = 100;
    gameData->level = 0;
    if(game->time == 0) gameData->headMoved = 0;
    return;
}

void appleInit(Game *game, Apple *apple)
{
    apple->x = (rand() % (game->w / TILE_WIDTH));
    apple->y = (rand() % (game->h / TILE_HEIGHT));
    return;
}


void renderPlayer(Game *game, PlayerNode *playerHead, GameData *gameData)
{
    int sx, sy;
    PlayerNode *tmp = playerHead;
    if((gameData->headMoved + gameData->limit) < game->time)
    {
        switch(gameData->direction)
        {
            case 1: // Down
                playerHead->bodyPart.y += SPEED * TILE_HEIGHT;
                break;
            case 2: // Up
                playerHead->bodyPart.y -= SPEED * TILE_HEIGHT;
                break;
            case 3: // Right
                playerHead->bodyPart.x += SPEED * TILE_WIDTH;
                break;
            case 4: // Left
                playerHead->bodyPart.x -= SPEED * TILE_WIDTH;
                break;
            case 0:
            default:
                break;
        }
        gameData->headMoved = game->time;
        sx = playerHead->bodyPart.x;
        sy = playerHead->bodyPart.y;
        tmp = playerHead->next;
        SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(game->renderer, &playerHead->bodyPart);
        if (((playerHead->bodyPart.y == game->h) || (playerHead->bodyPart.y < 0)) && (gameData->direction != 0))
        {
            playerInit(game, playerHead, gameData, 0, 0);
        }
        if (((playerHead->bodyPart.x == game->w) || (playerHead->bodyPart.x < 0)) && (gameData->direction != 0))
        {
            playerInit(game, playerHead, gameData, 0, 0);
        }
        while (tmp != playerHead)
        {
            sx = sx + tmp->bodyPart.x;
            tmp->bodyPart.x = sx - tmp->bodyPart.x;
            sx = sx - tmp->bodyPart.x;
            sy = sy + tmp->bodyPart.y;
            tmp->bodyPart.y = sy - tmp->bodyPart.y;
            sy = sy - tmp->bodyPart.y;
            if( (tmp != playerHead) && ((playerHead->bodyPart.x == tmp->bodyPart.x) && (playerHead->bodyPart.y == tmp->bodyPart.y)))
            {
                playerInit(game, playerHead, gameData, 0, 0); break;
            }
            SDL_RenderFillRect(game->renderer, &tmp->bodyPart);
            tmp = tmp->next;
        }
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    return;
}

void growPlayer(Game *game, PlayerNode *playerHead, GameData *gameData)
{
    PlayerNode *tmp = playerHead;
    PlayerNode *newBodyPart = malloc(sizeof(PlayerNode));
    while (tmp->next != playerHead)
    {
        tmp = tmp->next;
    }
    tmp->next = newBodyPart;
    newBodyPart->prev = tmp;
    newBodyPart->next = playerHead;
    newBodyPart->bodyPart = tmp->bodyPart;
    if((gameData->score % (((game->w / TILE_WIDTH) * (game->h / TILE_HEIGHT)) / 100)) == 0) gameData->limit -= 1, gameData->level += 1;
    return;
}

void renderApple(Game *game, Apple *apple, PlayerNode *playerHead, GameData *gameData)
{
    SDL_Rect appleDestRec;
    if(apple->x == playerHead->bodyPart.x && apple->y == playerHead->bodyPart.y)
    {
        gameData->score += 1;
        growPlayer(game, playerHead, gameData);
        apple->x = (rand() % (game->w));
        apple->y = (rand() % (game->h));
    }
    appleDestRec.w = TILE_WIDTH;
    appleDestRec.h = TILE_HEIGHT;
    appleDestRec.x = apple->x * TILE_WIDTH;
    appleDestRec.y = apple->y * TILE_HEIGHT;
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(game->renderer, &appleDestRec);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    return;
}

void gameResize(Game *game, PlayerNode *playerHead, GameData *gameData, Apple *apple, int w, int h)
{
    SDL_SetWindowSize(game->window, w, h);
    game->w = w, game->h = h;
    playerInit(game, playerHead, gameData, 0, 0);
    appleInit(game, apple);
    return;
}

