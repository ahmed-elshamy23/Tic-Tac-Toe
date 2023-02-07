#include <stdio.h>
#include <stdlib.h>
#include "game.h"

static unsigned char gameBoard[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
static unsigned char turnsFlag = 0, drawFlag = 0, position;

static boardState boardModificationState = OK;

void printBoard()
{
    printf("\n\n");
    for (unsigned char i = 0; i < 7; i += 3)
    {
        printf("\t\t\t\t\t %c | %c | %c \n", gameBoard[i], gameBoard[i + 1], gameBoard[i + 2]);
        if (i != 6)
            printf("\t\t\t\t\t-----------\n");
    }
}

void AcceptInputs(player *p1, player *p2)
{
    printf("Player 1 name: ");
    fflush(stdin);
    scanf("%[^\n]s", p1->name);
    printf("Player 2 name: ");
    fflush(stdin);
    scanf("%[^\n]s", p2->name);
}

void initializeGame(player *p1, player *p2)
{
    AcceptInputs(p1, p2);
    p1->score = 0;
    p2->score = 0;
    p1->symbol = 'x';
    p2->symbol = 'o';
}

boardState modifyBoard(unsigned char position, player p)
{
    if (gameBoard[position - 1] != '-')
        return BUSY_CELL;
    else
        gameBoard[position - 1] = p.symbol;
    return OK;
}

gameState checkGameEnd(unsigned char *winner)
{
    unsigned short int sumRows[3] = {0}, sumColumns[3] = {0}, sumDiagonal[2] = {0};
    for (unsigned char i = 0; i < 7; i += 3)
    {
        sumRows[i / 3] = gameBoard[i] + gameBoard[i + 1] + gameBoard[i + 2];
        switch (sumRows[i])
        {
        case 360:
            *winner = 1;
            return NO_DRAW;
        case 333:
            *winner = 2;
            return NO_DRAW;
        }
    }
    for (unsigned char i = 0; i < 3; i++)
    {
        sumColumns[i] = gameBoard[i] + gameBoard[i + 3] + gameBoard[i + 6];
        switch (sumColumns[i])
        {
        case 360:
            *winner = 1;
            return NO_DRAW;
        case 333:
            *winner = 2;
            return NO_DRAW;
        }
    }
    sumDiagonal[0] = gameBoard[0] + gameBoard[4] + gameBoard[8];
    sumDiagonal[1] = gameBoard[2] + gameBoard[4] + gameBoard[6];
    switch (sumDiagonal[0])
    {
    case 360:
        *winner = 1;
        return NO_DRAW;
    case 333:
        *winner = 2;
        return NO_DRAW;
    }
    switch (sumDiagonal[1])
    {
    case 360:
        *winner = 1;
        return NO_DRAW;
    case 333:
        *winner = 2;
        return NO_DRAW;
    }
    for (unsigned char i = 0; i < 9; i++)
        if (gameBoard[i] == '-')
            return NOT_FINISHED;
    return DRAW;
}

void continueGame(player *p)
{
    printf("Player %d (%s):\nEnter position: ", (p->symbol == 'x') ? 1 : 2, p->name);
    do
    {
        fflush(stdin);
        scanf("%d", &position);
        boardModificationState = modifyBoard(position, *p);
        if (position < 0 || position > 9)
            printf("\nYou entered an invalid position.\nEnter another position: ");
        else if (boardModificationState != OK)
            printf("\nThis position is already taken.\nEnter another position: ");
    } while (boardModificationState != OK || position < 0 || position > 9);
}

void resetBoard()
{
    for (unsigned char i = 0; i < 9; i++)
        gameBoard[i] = '-';
}