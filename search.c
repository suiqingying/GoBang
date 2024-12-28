#include "search.h"

int GetPoints(PTR_To_Point Points, int color, bool flag, bool *flag_if_win, PTR_To_Point Bisha)
{
    int index = 0;
    bool vis[BOARD_SIZE][BOARD_SIZE];
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j])
            {
                for (int x = i - 1; x <= i + 1; x++)
                    for (int y = j - 1; y <= j + 1; y++)
                    {
                        if (isInBounds(x, y) && board[x][y] == 0)
                        {
                            vis[x][y] = true;
                        }
                    }
            }
    for (int i = BOARD_SIZE - 1; i >= 0; i--)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (vis[i][j])
            {
                GetStatus(i, j, WHITE);
                GetStatus(i, j, BLACK);

                if (color == WHITE || Onlyjudge(i, j))
                {
                    if (Value_Board[i][j][color - 1].Right_5)
                    {
                        Bisha->x = i;
                        Bisha->y = j;
                        *flag_if_win = true;
                        return ++index;
                    }
                    Points[index].x = i;
                    Points[index].y = j;
                    if (flag)
                    {
                        GetSingleScore(i, j);
                        Points[index].score = TotalValue[i][j];
                    }
                    index++;
                }
            }
    return index;
}

Point b[225];

void merge(PTR_To_Point s, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1, tot = l;
    while (i <= mid && j <= r)
    {
        if (s[i].score >= s[j].score)
        {
            b[tot++] = s[i];
            i++;
        }
        else
        {
            b[tot++] = s[j];
            j++;
        }
    }
    while (i <= mid)
    {
        b[tot++] = s[i];
        i++;
    }
    while (j <= r)
    {
        b[tot++] = s[j];
        j++;
    }
    for (int i = l; i <= r; i++)
    {
        s[i] = b[i];
    }
    return;
}

void mergesort(PTR_To_Point s, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    mergesort(s, l, mid);
    mergesort(s, mid + 1, r);
    merge(s, l, r);
}

int MinMax(int color, PTR_To_Point pos, int depth, int alpha, int beta, int MAXDEPTH)
{
    ++cnt;
    if (depth == 0 || tot + 1 == BOARD_SIZE * BOARD_SIZE)
    {
        return GetWholeScore(color);
    }
    PTR_To_Point Points = (PTR_To_Point)malloc(sizeof(Point) * 225);
    bool flag_if_win = false;
    Point Bisha;
    int n = GetPoints(Points, color, NEED_VALUE, &flag_if_win, &Bisha);
    if (flag_if_win)
    {
        if (depth == MAXDEPTH)
        {
            pos->x = Bisha.x;
            pos->y = Bisha.y;
        }
        return Value_Right_5;
    }
    int LENGTH = 15;
    // switch (depth)
    // {
    // case 8:
    //     LENGTH = 15;
    //     break;
    // case 7:
    //     LENGTH = 12;
    //     break;
    // case 6:
    //     LENGTH = 12;
    //     break;
    // case 5:
    //     LENGTH = 8;
    //     break;
    // case 4:
    //     LENGTH = 8;
    //     break;
    // case 3:
    //     LENGTH = 8;
    //     break;
    // case 2:
    //     LENGTH = 8;
    //     break;
    // case 1:
    //     LENGTH = 8;
    //     break;
    // default:
    //     printf("error");
    //     break;
    // }
    if (n < LENGTH)
    {
        LENGTH = n;
    }
    mergesort(Points, 0, n - 1);
    // for (int i = 0; i < LENGTH; i++)
    // {
    //     printf("DEpth = %d, x = %c, y = %d, score = %d\n",depth, Points[i].x + 'A', 15 - Points[i].y, Points[i].score);
    // }
    for (int i = 0; i < LENGTH; i++)
    {
        board[Points[i].x][Points[i].y] = color;
        // printf("depth = %d, x = %c, y = %d\n", depth, Points[i].x + 'A',15 - Points[i].y);
        tot++;
        int score = -MinMax(3 - color, pos, depth - 1, -beta, -alpha, MAXDEPTH);
        tot--;
        board[Points[i].x][Points[i].y] = 0;
        if (score > alpha)
        {
            alpha = score;
            if (depth == MAXDEPTH)
            {
                pos->x = Points[i].x;
                pos->y = Points[i].y;
            }
        }
        if (alpha >= beta)
        {
            free(Points);
            return alpha;
        }
    }
    free(Points);
    return alpha;
}