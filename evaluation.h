#include "draw.h"

#define Value_Right_5 50000
#define Value_Living_4 4320
#define Value_Rush_4 720
#define Value_Living_3 720
#define Value_Rush_3 100
#define Value_Living_2 120
#define Value_Rush_2 20

typedef struct Status {
    bool Too_long; //长连（对于黑棋而言）
    bool Right_5; //合法的5连
    int Living_4; //合法活四
    int Rush_4; //合法冲4
    int Living_3; //合法活3
    int Rush_3; //合法冲3
    int Living_2; //合法活2
    int Rush_2; //合法冲2
} Status;

typedef struct node{
    int x, y, color;
    int value[2];
    int TotalScore;
} node;

int GetWholeScore(int color);
int GetSingleScore(node p);

bool judge(int x, int y, int player, int game_mode);

bool isWin(int x, int y, int player);
bool isInBounds(int x, int y);
bool isBoardFull();

extern Status Value_Board[BOARD_SIZE][BOARD_SIZE][2];
bool judge_next(int x, int y, int color);
void GetStatus(int x, int y, int color);
bool Noban(int x, int y, int direction, int num, int fl);