#include "draw.h"

#define maxDepth 2
#define MAX_SCORE 50000000

extern const int dx[];
extern const int dy[];

typedef struct node{
    int x, y, color;
} node;

extern int alpha, beta;
extern node pos;

bool isInBounds(int x, int y);
bool isBoardFull();
int MinMax(int depth, int color, int alpha, int beta);
