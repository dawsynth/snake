#include "player.h"

static void apple_gen(Game* game) {
    unsigned int x, y;
    do {
        x = rand() % game->board_size;
        y = rand() % game->board_size;
    } while (game->board[x][y] != SNAKE);
    game->board[x][y] = APPLE;
}

Game* game_init(unsigned int size) {
    Game* result = malloc(sizeof(Game));
    if (result == NULL) {
        return NULL;
    }

    result->score = 0;
    result->level = 0;
    result->board_size = (size < DEFAULT_BOARD) ? DEFAULT_BOARD : size;

    result->board = (TILE**)malloc(result->board_size * sizeof(TILE*));
    if (result->board == NULL) {
        return NULL;
    }

    for (int i = 0; i < result->board_size; i++) {
        result->board[i] = (TILE *)malloc(result->board_size * sizeof(TILE));
        if (result->board[i] == NULL) {
            return NULL;
        }
    }

    for (int i = 0; i < result->board_size; i++) {
        for (int j = 0; j < result->board_size; j++) {
            result->board[i][j] = EMPTY;
        }
    }

    do {
        apple_gen(result);
    } while (result->board[0][0] != APPLE);

    return result;
}

void game_destroy(Game* game) {
    for (int i = 0; i < game->board_size; i++) {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}

Snake* snake_init(Game* game) {
    Snake* result = malloc(sizeof(Snake));
    if (result == NULL) {
        return NULL;
    }
    Position* head_pos = calloc(1, sizeof(Position));
    if (head_pos == NULL) {
        return NULL;
    }
    head_pos->x = 0;
    head_pos->y = 0;
    Node* head_node = create_node((void*)(head_pos));
    if (head_node == NULL) {
        return NULL;
    }
    result->parts = create_l_list(head_node, NULL);
    if (result->parts == NULL) {
        return NULL;
    }
    result->direction = NOT_MOVING;

    game->board[0][0] = SNAKE;

    return result;
}

int snake_reset(Game* game, Snake* snake) {
    empty_l_list(snake->parts);

    Position* head_pos = calloc(1, sizeof(Position));
    if (head_pos == NULL) {
        return -1;
    }
    head_pos->x = 0;
    head_pos->y = 0;

    Node* head_node = create_node((void*)(head_pos));
    if (head_node == NULL) {
        return -1;
    }

    int result = l_list_insert_head(snake->parts, head_node);
    if (result < 0) {
        return -1;
    }
    snake->direction = NOT_MOVING;

    for (int i = 0; i < game->board_size; i++) {
        for (int j = 0; j < game->board_size; j++) {
            game->board[i][j] = (i == j && i == 0) ? SNAKE : EMPTY;
        }
    }

    return 0;
}

void snake_destroy(Snake* snake) {
    destroy_l_list(snake->parts);
    free(snake);
}


static void snake_slither(Game* game, Snake* snake) {
    Node* tmp = NULL;
    int nx, ox = ((Position *)(snake->parts->head->data))->x;
    int ny, oy = ((Position *)(snake->parts->head->data))->y;
    switch (snake->direction) {
        case NOT_MOVING:
            break;
        case UP:
            ny -= SPEED;
            break;
        case DOWN:
            ny += SPEED;
            ((Position *)(snake->parts->head->data))->y += SPEED;
            break;
        case RIGHT:
            nx += SPEED;
            ((Position *)(snake->parts->head->data))->x += SPEED;
            break;
        case LEFT:
            nx -= SPEED;
            ((Position *)(snake->parts->head->data))->x -= SPEED;
            break;
    }

    if (nx > game->board_size || nx < 0) {
        snake_reset(game, snake);
        return;
    }

    if (ny > game->board_size || ny < 0) {
        snake_reset(game, snake);
        return;
    }

    if (game->board[ny][nx] == SNAKE) {
        snake_reset(game, snake);
        return;
    }
    ((Position *)(snake->parts->head->data))->x = nx;
    ((Position *)(snake->parts->head->data))->y = ny;

    if (snake->parts->tail != NULL) {
        for (tmp = snake->parts->head->next; ; tmp = tmp->next) {
            ((Position*)(tmp->data))->x = ((Position*)(tmp->data))->x + ox;
            ox = ((Position*)(tmp->data))->x - ox;
            ((Position*)(tmp->data))->x = ((Position*)(tmp->data))->x - ox;
            ((Position*)(tmp->data))->y = ((Position*)(tmp->data))->y + oy;
            oy = ((Position*)(tmp->data))->y - oy;
            ((Position*)(tmp->data))->y = ((Position*)(tmp->data))->y - oy;
            if (tmp->next == NULL) break;
        }
        tmp = NULL;
    }

    for (tmp = snake->parts->head; tmp != NULL; tmp = tmp->next) {
        int x = ((Position *)(tmp->data))->x;
        int y = ((Position *)(tmp->data))->y;
        if (x < game->board_size && x >= 0 && y < game->board_size && y >= 0) {
            game->board[y][x] = SNAKE;
        }
    }
}

int game_update(Game* game, Snake* snake) {
    snake_slither(game, snake);
    if (game->board[((Position *)(snake->parts->head->data))->y][((Position *)(snake->parts->head->data))->x] == APPLE) {
        Position* new_tail = calloc(1, sizeof(Position));
        if (new_tail == NULL) {
            return -1;
        }
        if (snake->parts->tail != NULL) {
            new_tail->x = ((Position *)(snake->parts->tail->data))->x;
            new_tail->y = ((Position *)(snake->parts->tail->data))->y;
        } else {
            new_tail->x = ((Position *)(snake->parts->head->data))->x;
            new_tail->y = ((Position *)(snake->parts->head->data))->y;
        }
        Node* new_node = create_node((void*)(new_tail));
        if (new_node == NULL) {
            return -1;
        }
        int result = l_list_insert_end(snake->parts, new_node);
        if (result < 0) {
            return -1;
        }
        game->score += 1;
    }
}

