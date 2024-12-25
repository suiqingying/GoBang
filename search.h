#include "evaluation.h"

extern int DEPTH;

#define MAX_SCORE 10000000

#define NEED_VALUE 1
#define NO_NEED_VALUE 0



typedef struct{
    int x, y, color;
    int score;
} Point, *PTR_To_Point;

int GetPoints(PTR_To_Point Points, int color, bool flag, bool *flag_if_win, PTR_To_Point Bisha, bool *flag_will_lose, PTR_To_Point Bidang);
void merge(PTR_To_Point s, int l, int r);
void mergesort(PTR_To_Point s, int l, int r);
int Find_base_point(int color);
int MinMax(int color, PTR_To_Point pos, int depth, int a, int b, int MAXDEPTH);

