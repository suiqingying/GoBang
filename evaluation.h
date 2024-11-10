#include "draw.h"
#include "judge.h"

#define ALIVE_5 1000000
#define ALIVE_4 10000
#define ALIVE_3 1000
#define ALIVE_2 100
#define ALIVE_1 10
#define BLOCK_4 1000
#define BLOCK_3 100
#define BLOCK_2 10

typedef struct node{
    int x, y, color;
} node;

typedef struct Status {
    int _ALIVE_5;
    int _ALIVE_4;
    int _ALIVE_3;
    int _ALIVE_2;
    int _ALIVE_1;
    int _BLOCK_4;
    int _BLOCK_3;
    int _BLOCK_2;
} Status;

int GetWholeScore(int color);
int GetSingleScore(node p);
Status GetStatus(node p);