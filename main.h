#include "draw.h"
#include "search.h"


extern int game_mode;
extern int step, player, mycolor;
extern bool running;

void TwoPlayerBattle();
void HumanVsAI();
void move();
void AImove();
void pause();

bool isWin(int x, int y, int player);