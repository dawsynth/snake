#include "player.h"

const Uint8 backgroundColor[3] = {27, 27, 29};
const Uint8 snakeColor[3] = {231, 171, 87};
const Uint8 appleColor[3] = {240, 132, 46};

void playerInit(Game *game, struct node **playerHead, GameData *gameData, int hx, int hy)
{
    if ((*playerHead)->next != NULL) nodesFree(playerHead, 1);
    (*playerHead)->bodyPart.x = hx;
    (*playerHead)->bodyPart.y = hy;
    gameData->direction = NOT_MOVING;
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

void playerMove(Game *game, struct node **playerHead, GameData *gameData)
{
    struct node *tmp = NULL;
    int sx = (*playerHead)->bodyPart.x;
    int sy = (*playerHead)->bodyPart.y;
    switch (gameData->direction)
    {
        case NOT_MOVING:
            break;
        case UP:
            (*playerHead)->bodyPart.y -= (SPEED * TILE_HEIGHT);
            break;
        case DOWN:
            (*playerHead)->bodyPart.y += (SPEED * TILE_HEIGHT);
            break;
        case RIGHT:
            (*playerHead)->bodyPart.x += (SPEED * TILE_WIDTH);
            break;
        case LEFT:
            (*playerHead)->bodyPart.x -= (SPEED * TILE_WIDTH);
            break;
    }
    if ((*playerHead)->next != NULL)
    {
        for (tmp = (*playerHead)->next; ; tmp = tmp->next)
        {
            tmp->bodyPart.x = tmp->bodyPart.x + sx;
            sx = tmp->bodyPart.x - sx;
            tmp->bodyPart.x = tmp->bodyPart.x - sx;
            tmp->bodyPart.y = tmp->bodyPart.y + sy;
            sy = tmp->bodyPart.y - sy;
            tmp->bodyPart.y = tmp->bodyPart.y - sy;
            if (tmp->next == *playerHead) break;
        }
    }
    tmp = NULL;
    free(tmp);
    return;
}

void playerCollide(Game *game, struct node **playerHead, GameData *gameData)
{
    struct node *tmp = NULL;
    if (gameData->direction != NOT_MOVING)
    {
        if (((*playerHead)->bodyPart.x == -TILE_WIDTH && gameData->direction == LEFT) || ((*playerHead)->bodyPart.x == (game->w) && gameData->direction == RIGHT))
        {
            playerInit(game, playerHead, gameData, 0, 0);
        }
        if (((*playerHead)->bodyPart.y == -TILE_HEIGHT && gameData->direction == UP) || ((*playerHead)->bodyPart.y == (game->h) && gameData->direction == DOWN))
        {
            playerInit(game, playerHead, gameData, 0, 0);
        }
        for (tmp = (*playerHead)->next; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->bodyPart.x == (*playerHead)->bodyPart.x && tmp->bodyPart.y == (*playerHead)->bodyPart.y)
            {
                playerInit(game, playerHead, gameData, 0, 0);
            }
            if (tmp->next == NULL || tmp->next == *playerHead) break;
            continue;
        }
    }
    tmp = NULL;
    free(tmp);
    return;
}

void playerRender(Game *game, struct node *playerHead)
{
    struct node *tmp = NULL;
    SDL_SetRenderDrawColor(game->renderer, snakeColor[0], snakeColor[1], snakeColor[2], SDL_ALPHA_OPAQUE);
    for (tmp = playerHead; ; tmp = tmp->next)
    {
        SDL_RenderFillRect(game->renderer, &tmp->bodyPart);
        if (tmp->next == NULL || tmp->next == playerHead) break;
        continue;
    }
    SDL_SetRenderDrawColor(game->renderer, backgroundColor[0], backgroundColor[1], backgroundColor[2], SDL_ALPHA_OPAQUE);
    tmp = NULL;
    free(tmp);
    return;
}

void playerGrow(Game *game, struct node *playerHead, GameData *gameData)
{
    if (playerHead->prev != NULL) 
    {
        nodeInsertEnd(&playerHead, nodeCreate(&(SDL_Rect) {.x = playerHead->prev->bodyPart.x, .y = playerHead->prev->bodyPart.y, .w = TILE_WIDTH, .h = TILE_HEIGHT}));
    }
    else 
    {
        nodeInsertEnd(&playerHead, nodeCreate(&(SDL_Rect) {.x = playerHead->bodyPart.x, .y = playerHead->bodyPart.y, .w = TILE_WIDTH, .h = TILE_HEIGHT}));
    }
    if((gameData->score % (((game->w / TILE_WIDTH) * (game->h / TILE_HEIGHT)) / 100)) == 0) gameData->limit -= 1, gameData->level += 1;
    return;
}

void appleRender(Game *game, Apple *apple, struct node *playerHead, GameData *gameData)
{
    SDL_Rect appleDestRec;
    if(apple->x * TILE_WIDTH == playerHead->bodyPart.x && apple->y * TILE_HEIGHT == playerHead->bodyPart.y)
    {
        gameData->score += 1;
        playerGrow(game, playerHead, gameData);
        apple->x = (rand() % (game->w / TILE_WIDTH));
        apple->y = (rand() % (game->h / TILE_HEIGHT));
    }
    appleDestRec.w = TILE_WIDTH;
    appleDestRec.h = TILE_HEIGHT;
    appleDestRec.x = apple->x * TILE_WIDTH;
    appleDestRec.y = apple->y * TILE_HEIGHT;
    SDL_SetRenderDrawColor(game->renderer, appleColor[0], appleColor[1], appleColor[2], SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(game->renderer, &appleDestRec);
    SDL_SetRenderDrawColor(game->renderer, backgroundColor[0], backgroundColor[1], backgroundColor[2], SDL_ALPHA_OPAQUE);
    return;
}

void gameResize(Game *game, struct node **playerHead, GameData *gameData, Apple *apple, int w, int h)
{
    SDL_SetWindowSize(game->window, w, h);
    game->w = w, game->h = h;
    playerInit(game, playerHead, gameData, 0, 0);
    appleInit(game, apple);
    return;
}

