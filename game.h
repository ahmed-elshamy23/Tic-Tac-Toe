#ifndef GAME_H
#define GAME_H

#define BOARD_ROW_START 0
#define BOARD_ROW_END 3

typedef struct player
{
    unsigned char name[20];
    unsigned char symbol;
    unsigned int score;
} player;

typedef enum gameState
{
    DRAW,
    NO_DRAW,
    NOT_FINISHED
} gameState;

typedef enum boardState
{
    OK,
    BUSY_CELL
} boardState;

void printBoard();

void AcceptInputs(player *p1, player *p2);

void initializeGame(player *p1, player *p2);

boardState modifyBoard(unsigned char position, player p);

gameState checkGameEnd(unsigned char *winner);

void continueGame(player *p);

void resetBoard();

#endif