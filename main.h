#include "draw.h"
#include <stdbool.h>

const int dx[] = { 1, 0, 1, 1 };
const int dy[] = { 0, 1, 1, -1 };

extern int step, player, mycolor;
extern bool running;

void TwoPlayerBattle();
void HumanVsAI();
void move();
void AImove();
bool isInBounds(int x, int y);
bool isWin(int x, int y, int player);
bool isBoardFull();
int evaluate();

void pause()
{
    printf("Press Enter key to continue...");
    while (getchar() != '\n')
        ;
    getchar();
}