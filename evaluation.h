#include "draw.h"

#define Value_Right_5 50000
#define Value_Living_4 4320
#define Value_Rush_4 720
#define Value_Living_3 720
#define Value_Rush_3 100
#define Value_Living_2 120
#define Value_Rush_2 20

#define Sef_Value_Living_4 100000
#define Rival_Value_Living_4 10000000
#define Sef_Value_Rush_4 720
#define Rival_Value_Rush_4 1000000
#define Sef_Value_Living_3 720
#define Rival_Value_Living_3 50000
#define Sef_Value_Rush_3 480
#define Rival_Value_Rush_3 720
#define Sef_Value_Living_2 480
#define Rival_Value_Living_2 480
#define Sef_Value_Rush_2 20
#define Rival_Value_Rush_2 100

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
extern double ttt;
extern int cnt;

void GetSingleScore(int x, int y, int color);
int GetWholeScore(int color);

bool judge(int x, int y, int player);
bool Onlyjudge(int x, int y);

bool isWin(int x, int y, int player);
bool isInBounds(int x, int y);
bool isBoardFull();

extern Status Value_Board[BOARD_SIZE][BOARD_SIZE][2];
extern int value[BOARD_SIZE][BOARD_SIZE][2], TotalValue[BOARD_SIZE][BOARD_SIZE];
bool judge_next(int x, int y, int color);
void GetStatus(int x, int y, int color);
bool Noban(int x, int y, int direction, int num, int fl);