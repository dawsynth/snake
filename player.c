#include "player.h"


void playerInit(Game *game, Player *player, int hx, int hy)
{
    player->hx = hx;
    player->hy = hy;
    player->direction = 0;
    player->score = 0;
    player->limit = 100;
    player->level = 0;
    if(game->time == 0) player->headMoved = 0;
    player->body[0].x = hx;
    player->body[0].y = hy;
    player->body[0].w = TILE_WIDTH;
    player->body[0].h = TILE_HEIGHT;
    game->time = 0;
    return;
}

void appleInit(Game *game, Apple *apple)
{
    apple->x = (rand() % (game->w / TILE_WIDTH));
    apple->y = (rand() % (game->h / TILE_HEIGHT));
    return;
}


void renderPlayer(Game *game, Player *player)
{
    int sx, sy;
    if((player->headMoved + player->limit) < game->time)
    {
        switch(player->direction)
        {
            case 1: // Down
                player->hy += SPEED;
                break;
            case 2: // Up
                player->hy -= SPEED;
                break;
            case 3: // Right
                player->hx += SPEED;
                break;
            case 4: // Left
                player->hx -= SPEED;
                break;
            case 0:
            default:
                break;
        }
        player->headMoved = game->time;
        sx = player->hx * TILE_WIDTH;
        sy = player->hy * TILE_HEIGHT;
        if (((player->hy * TILE_HEIGHT == game->h) || (player->hy * TILE_HEIGHT < 0)) && (player->direction != 0))
        {
            playerInit(game, player, 0, 0);
        }
        if (((player->hx * TILE_WIDTH == game->w) || (player->hx * TILE_WIDTH < 0)) && (player->direction != 0))
        {
            playerInit(game, player, 0, 0);
        }
        for(int i = 0; i <= player->score; i++)
        {
            sx = sx + player->body[i].x;
            player->body[i].x = sx - player->body[i].x;
            sx = sx - player->body[i].x;
            sy = sy + player->body[i].y;
            player->body[i].y = sy - player->body[i].y;
            sy = sy - player->body[i].y;
            if( (i != 0) && ((player->body[0].x == player->body[i].x) && (player->body[0].y == player->body[i].y)))
            {
                playerInit(game, player, 0, 0); break;
            }
        }
    }
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRects(game->renderer, player->body, (player->score + 1));
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    return;
}

void growPlayer(Game *game, Player *player)
{
    player->body[player->score] = player->body[player->score - 1];
    if((player->score % (((game->w / TILE_WIDTH) * (game->h / TILE_HEIGHT)) / 100)) == 0) player->limit -= 1, player->level += 1;
    return;
}

void renderApple(Game *game, Apple *apple, Player *player)
{
    SDL_Rect appleDestRec;
    if(apple->x == player->hx && apple->y == player->hy)
    {
        player->score += 1;
        growPlayer(game, player);
        apple->x = (rand() % (game->w / TILE_WIDTH));
        apple->y = (rand() % (game->h / TILE_HEIGHT));
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

void gameResize(Game *game, Player *player, Apple *apple, int w, int h)
{
    SDL_SetWindowSize(game->window, w, h);
    game->w = w, game->h = h;
    playerInit(game, player, 0, 0);
    appleInit(game, apple);
    return;
}

