#include "draw.h"
#include "evaluation.h"

#define maxDepth 2
#define MAX_SCORE 50000000
#define MAXLENGTH 15


typedef struct POINTS {
    node pos[MAXLENGTH];
} POINTS;

extern int step;
extern int alpha, beta;
extern node pos;
extern POINTS P;


int MinMax(int depth, int color, int alpha, int beta);
POINTS GetPoints(int color);

