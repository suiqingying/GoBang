#include "draw.h"

#define maxDepth 4

extern const int dx[];
extern const int dy[];

typedef struct node
{
    int x, y, color;
} node;

extern node pos;

bool isInBounds(int x, int y);
bool isBoardFull();
void MinMax(int depth, int color, int alpha, int beta);
