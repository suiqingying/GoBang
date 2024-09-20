#include "draw.h"

#define maxDepth 4
#define MAX_SCORE 5000000

extern const int dx[];
extern const int dy[];

bool isInBounds(int x, int y);
bool isBoardFull();
void MinMax(int depth, int color, int x, int y);
void GetPoints(int color);