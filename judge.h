#include "draw.h"

bool judge(int x, int y, int player, int game_mode);

bool isWin(int x, int y, int player);
bool isInBounds(int x, int y);
bool isBoardFull();

int BanMove (int x, int y);
int Reban(int x, int y, int direction, int num, int fl);