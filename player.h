#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "linkedlist.h"

#define SPEED 1
#define DEFAULT_BOARD 8

typedef enum _TILE {
    EMPTY, 
    SNAKE, 
    APPLE
} TILE;

typedef struct _Game {
    unsigned int score, level;
    TILE** board;
    unsigned int board_size;
} Game;

typedef enum _DIRECTION {
    NOT_MOVING,
    UP,
    DOWN,
    RIGHT,
    LEFT
} DIRECTION;

typedef struct _Position {
    int x, y;
} Position;

typedef struct _Snake {
    LinkedList* parts;
    DIRECTION direction;
} Snake;

Game* game_init(unsigned int size);
void game_destroy(Game* game);

Snake* snake_init(Game* game);
int snake_reset(Game* game, Snake* snake);
void snake_destroy(Snake* snake);

int game_update(Game* game, Snake* snake);

#endif
