#include "search.h"

int GetPoints(PTR_To_Point Points, int color, bool flag, bool *flag_if_win, PTR_To_Point Bisha, bool *flag_will_lose, PTR_To_Point Bidang)
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
    for (int i = 0; i < BOARD_SIZE; i++)
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
                    int ag_color = 3 - color;
                    if ((ag_color == WHITE || Onlyjudge(i, j)) && Value_Board[i][j][ag_color - 1].Right_5)
                    {
                        Bidang->x = i;
                        Bidang->y = j;
                        *flag_will_lose = true;
                    }
                    Points[index].x = i;
                    Points[index].y = j;
                    if (flag)
                    {
                        
                        GetSingleScore(i, j, color);
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

int Find_base_point(int color)
{

    PTR_To_Point Points;
    Points = (PTR_To_Point)malloc(sizeof(Point) * 225);
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;
    int n = GetPoints(Points, color, NO_NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);
    if (flag_if_win)
    {
        return MAX_SCORE / 2;
    }
    if (flag_will_lose)
    {
        board[Bidang.x][Bidang.y] = color;
        int score = GetWholeScore(color);
        board[Bidang.x][Bidang.y] = 0;
        return score;
    }
    int i;
    int score = -MAX_SCORE;
    for (i = 0; i < n; i++)
    {
        board[Points[i].x][Points[i].y] = color;
        int tmp = GetWholeScore(color);
        board[Points[i].x][Points[i].y] = 0;
        if (tmp > score)
        {
            score = tmp;
        }
    }
    free(Points);
    return score;
}
int MinMax(int color, PTR_To_Point pos, int depth, int alpha, int beta, int MAXDEPTH)
{
    if (depth == 0)
    {
        int value = Find_base_point(color);
        return value;
    }
    PTR_To_Point Points = (PTR_To_Point)malloc(sizeof(Point) * 225);
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;
    int n = GetPoints(Points, color, NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);
    if (flag_if_win)
    {
        if (depth == MAXDEPTH)
        {
            pos->x = Bisha.x;
            pos->y = Bisha.y;
        }
        return MAX_SCORE / 2;
    }
    int LENGTH = 15;
    if (MAXDEPTH == 8)
    {
        switch (depth)
        {
        case 8:
            LENGTH = 12;
            break;
        case 7:
            LENGTH = 10;
            break;
        case 6:
            LENGTH = 10;
            break;
        case 5:
            LENGTH = 7;
            break;
        case 4:
            LENGTH = 7;
            break;
        case 3:
            LENGTH = 7;
            break;
        case 2:
            LENGTH = 7;
            break;
        case 1:
            LENGTH = 7;
            break;
        default:
            printf("error");
            break;
        }
    }
    if (n < LENGTH)
    {
        LENGTH = n;
    }
    mergesort(Points, 0, n - 1);
    for (int i = 0; i < LENGTH; i++)
    {
        board[Points[i].x][Points[i].y] = color;
        int score = -MinMax(3 - color, pos, depth - 1, -beta, -alpha, MAXDEPTH);
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