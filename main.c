#include <stdio.h>
#include <stdlib.h>
#include "game.h"

static unsigned char winner = 0, turnsFlag = 0;

int main()
{
    unsigned char answer;
    gameState state = NOT_FINISHED;
    player p1, p2;
    system("cls");
    initializeGame(&p1, &p2);
    do
    {
        winner = 0;
        turnsFlag = 0;
        resetBoard();
        do
        {
            system("cls");
            printBoard();
            if (turnsFlag % 2 == 0)
                continueGame(&p1);
            else
                continueGame(&p2);
            turnsFlag++;
            state = checkGameEnd(&winner);
        } while (state == NOT_FINISHED);
        system("cls");
        printBoard();
        if (state == NO_DRAW)
        {
            if (winner == 1)
            {
                printf("\nPlayer 1 (%s) wins\n\n", p1.name);
                p1.score++;
            }
            else
            {
                printf("\nPlayer 2 (%s) wins\n\n", p2.name);
                p2.score++;
            }
        }
        else
            printf("********DRAW********\n\n");
        system("pause");
        printf("\n%s: %d\n%s: %d\n\n", p1.name, p1.score, p2.name, p2.score);
        printf("Another game (y/n)? ");
        fflush(stdin);
        scanf("%c", &answer);
    } while (answer != 'n');
    system("pause");
    return 0;
}