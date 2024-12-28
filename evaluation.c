#include "evaluation.h"
Status Value_Board[BOARD_SIZE][BOARD_SIZE][2];

bool judge(int x, int y, int player)
{
    if (player == 2)
    {
        return true;
    }
    GetStatus(x, y, player);
    Status res = Value_Board[x][y][player - 1];
    // printf("Player %d move: %c %d %d %d %d %d\n", player, x + 'A', 15 - y, res.Living_3, res.Rush_3,res.Rush_4, res.Living_4);
    if (res.Right_5)
    {
        return true;
    }
    if (res.Too_long || res.Living_3 >= 2 || res.Living_4 + res.Rush_4 >= 2)
    {
        if (res.Too_long)
            printf("Too long ban!\n");
        if (res.Living_3 >= 2)
            printf("Double three ban!\n");
        if (res.Living_4 + res.Rush_4 >= 2)
            printf("Double four ban!\n");
        return false;
    }
    return true;
}

bool Onlyjudge(int x, int y)
{
    Status res = Value_Board[x][y][0];
    if (res.Right_5)
        return true;
    return !(res.Too_long || res.Living_3 >= 2 || res.Living_4 + res.Rush_4 >= 2);
}

bool isInBounds(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool isBoardFull()
{
    return tot == BOARD_SIZE * BOARD_SIZE;
}

bool isWin(int x, int y, int player)
{
    for (int i = 0; i < 4; i++)
    {
        int count = 1;
        for (int j = 1; j <= 4; j++)
        {
            int newX = x + dx[i] * j;
            int newY = y + dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        for (int j = 1; j <= 4; j++)
        {
            int newX = x - dx[i] * j;
            int newY = y - dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == player)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if ((player == 2 && count >= 5) || (player == 1 && count == 5))
        {
            return true;
        }
    }
    return false;
}

void GetStatus(int x, int y, int color)
{
    // ? 为3 - color 或 边界，_ 为空位，1 为color
    // printf("%c %d %d\n", x + 'A', 15 - y, color);
    int adjoin_same[8];
    int adjoin_empty[8];
    int gap_same[8];
    int gap_empty[8];
    int gap_gap_same[8];
    int newX, newY;
    Status res;
    memset(&res, 0, sizeof(res));
    for (int i = 0; i < 8; i++)
    {
        adjoin_same[i] = adjoin_empty[i] = gap_same[i] = gap_empty[i] = gap_gap_same[i] = 0;
    }

    for (newX = x + 1, newY = y; newX < BOARD_SIZE && board[newX][newY] == color; newX++, adjoin_same[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == 0; newX++, adjoin_empty[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == color; newX++, gap_same[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == 0; newX++, gap_empty[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == color; newX++, gap_gap_same[0]++)
        ;

    for (newY = y + 1, newX = x; newY < BOARD_SIZE && board[newX][newY] == color; newY++, adjoin_same[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == 0; newY++, adjoin_empty[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == color; newY++, gap_same[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == 0; newY++, gap_empty[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == color; newY++, gap_gap_same[1]++)
        ;

    for (newX = x + 1, newY = y + 1; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, adjoin_same[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == 0; newX++, newY++, adjoin_empty[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, gap_same[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == 0; newX++, newY++, gap_empty[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, gap_gap_same[2]++)
        ;

    for (newX = x + 1, newY = y - 1; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, adjoin_same[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == 0; newX++, newY--, adjoin_empty[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, gap_same[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == 0; newX++, newY--, gap_empty[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, gap_gap_same[3]++)
        ;

    for (newX = x - 1, newY = y; newX >= 0 && board[newX][newY] == color; newX--, adjoin_same[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == 0; newX--, adjoin_empty[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == color; newX--, gap_same[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == 0; newX--, gap_empty[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == color; newX--, gap_gap_same[4]++)
        ;

    for (newY = y - 1, newX = x; newY >= 0 && board[newX][newY] == color; newY--, adjoin_same[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == 0; newY--, adjoin_empty[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == color; newY--, gap_same[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == 0; newY--, gap_empty[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == color; newY--, gap_gap_same[5]++)
        ;

    for (newX = x - 1, newY = y - 1; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, adjoin_same[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == 0; newX--, newY--, adjoin_empty[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, gap_same[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == 0; newX--, newY--, gap_empty[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, gap_gap_same[6]++)
        ;

    for (newX = x - 1, newY = y + 1; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, adjoin_same[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == 0; newX--, newY++, adjoin_empty[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, gap_same[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == 0; newX--, newY++, gap_empty[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, gap_gap_same[7]++)
        ;

    // for (int i = 0; i < 4; i++) {
    //     newX = x + dx[i], newY = y + dy[i];
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], adjoin_same[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], gap_same[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], gap_gap_same[i]++);
    // }
    // for (int i = 0; i < 4; i++) {
    //     newX = x - dx[i], newY = y - dy[i];
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], adjoin_same[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], gap_same[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], gap_gap_same[i + 4]++);
    // }
    for (int i = 0; i < 4; i++)
    {
        bool flag = false;
        // printf("%d %d\n", adjoin_same[i], adjoin_same[i + 4]);
        if (adjoin_same[i] + adjoin_same[i + 4] == 4 || (adjoin_same[i] == 4 && adjoin_same[i + 4] == 4))
        {
            res.Right_5 = true;
            flag = true;
        } // 五连
        if (flag)
        {
            Value_Board[x][y][color - 1] = res;
            return;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        bool flag = false;
        if (adjoin_same[i] + adjoin_same[i + 4] >= 5)
        {
            if (color == BLACK)
            {
                res.Too_long = true;
            }
            else
            {
                res.Right_5 = true;
            }
            flag = true;
        } // 长连
        if (flag)
        {
            Value_Board[x][y][color - 1] = res;
            return;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (adjoin_same[i] + adjoin_same[i + 4] == 3)
        {
            int flag = 0;
            if (adjoin_empty[i] > 0)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                    flag++;
            } // 1111_
            if (adjoin_empty[i + 4] > 0)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                    flag++;
            } // _1111
            if (flag == 1)
                res.Rush_4 += 1;
            if (flag == 2)
                res.Living_4 += 1;
        } // 四连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 2)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 1)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 111_1
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 1_111
            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0));             // 右边有两个空位且不会形成长连
                bool flagR_2 = (adjoin_empty[i] == 1 && gap_same[i] == 0);                                      // 右边有恰好一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
                bool flagL_2 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0);
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Living_3 += 1;
                } //?_111__?, ?__111_?
                else if ((((flagR_2 && flagR_3) || (flagR_1 && !flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || (((flagL_2 && flagL_3) || (flagL_1 && !flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Rush_3 += 1;
                }
            }
        } // 三连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 1)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 2)
            {
                res.Rush_4 += 1;
                flag = true;
            } //?11_11?

            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2)
            {
                res.Rush_4 += 1;
                flag = true;
            } //?11_11?
            // 事实上这两处不需要禁手判断

            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 1);                                      // 一空一同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));               // 最右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有至少一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Living_3 += 1;
                    flag = true;
                } //?_11_1_?,//?_1_11_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Rush_3 += 1;
                    flag = true;
                }
            }
            if (!flag)
            {
                // 判断活2和冲2
                bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0));             // 右边至少有两个空位且不会形成长连
                bool flagR_2 = (adjoin_empty[i] > 3 || (adjoin_empty[i] == 3 && gap_same[i] == 0));             // 右边至少有三个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边至少有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
                bool flagL_2 = (adjoin_empty[i + 4] > 3 || (adjoin_empty[i + 4] == 3 && gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 2, color)) || (flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 2, color)))
                {
                    res.Living_2 += 1;
                }
                else if (flagR_1 && (flagR_2 || flagR_3) && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 2, color) || (flagL_1 && (flagL_2 || flagL_3) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 2, color)))
                {
                    res.Rush_2 += 1;
                }
            }
        } // 二连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 0)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 3)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?1_111?
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 3)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?111_1?
            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 2);                                      // 一空二同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));               // 右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Living_3 += 1;
                    flag = true;
                } //?_1_11_?, //?_11_1_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    res.Rush_3 += 1;
                    flag = true;
                }
            }
            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 1 && gap_empty[i] >= 1);                 // 一空一同色一空
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));               // 最右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有至少一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1 && gap_empty[i + 4] >= 1);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 3, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 3, color)))
                {
                    res.Living_2 += 1;
                }
                else if ((flagR_1 && (flagR_2 || flagR_3) && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 3, color)) || (flagL_1 && (flagL_2 || flagL_3) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 3, color)))
                    res.Rush_2 += 1;
            }
        } // 一连
    }
    Value_Board[x][y][color - 1] = res;
    //   printf("Player %d move: %d %c %d %d %d\n", color, x + 'A', 15 - y, res.Living_3, res.Rush_4, res.Living_4);
}

bool Noban(int x, int y, int direction, int num, int color)
{
    // return 1;
    // if (board[x][y])
    //     printf("%c %d %d\n", x + 'A', 15 - y, board[x][y]);
    if (color == WHITE)
        return 1;
    int fl = 1;
    if (direction >= 4)
    {
        fl = -1;
        direction -= 4;
    }
    bool _Empty = true;
    if (board[x][y])
    {
        _Empty = false;
    }
    board[x][y] = color;
    int newX = x + fl * dx[direction] * num, newY = y + fl * dy[direction] * num;
    bool flag = judge_next(newX, newY, color);
    if (_Empty)
    {
        board[x][y] = 0;
    }
    return flag;
}

bool judge_next(int x, int y, int color)
{
    // return 1;
    // clock_t start_1 = clock();
    // ++cnt;
    // ? 为3 - color 或 边界，_ 为空位，1 为color
    int adjoin_same[8];
    int adjoin_empty[8];
    int gap_same[8];
    int gap_empty[8];
    int gap_gap_same[8];
    int newX, newY;
    for (int i = 0; i < 8; i++)
    {
        adjoin_same[i] = adjoin_empty[i] = gap_same[i] = gap_empty[i] = gap_gap_same[i] = 0;
    }

    for (newX = x + 1, newY = y; newX < BOARD_SIZE && board[newX][newY] == color; newX++, adjoin_same[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == 0; newX++, adjoin_empty[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == color; newX++, gap_same[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == 0; newX++, gap_empty[0]++)
        ;
    for (; newX < BOARD_SIZE && board[newX][newY] == color; newX++, gap_gap_same[0]++)
        ;

    for (newY = y + 1, newX = x; newY < BOARD_SIZE && board[newX][newY] == color; newY++, adjoin_same[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == 0; newY++, adjoin_empty[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == color; newY++, gap_same[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == 0; newY++, gap_empty[1]++)
        ;
    for (; newY < BOARD_SIZE && board[newX][newY] == color; newY++, gap_gap_same[1]++)
        ;

    for (newX = x + 1, newY = y + 1; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, adjoin_same[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == 0; newX++, newY++, adjoin_empty[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, gap_same[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == 0; newX++, newY++, gap_empty[2]++)
        ;
    for (; newX < BOARD_SIZE && newY < BOARD_SIZE && board[newX][newY] == color; newX++, newY++, gap_gap_same[2]++)
        ;

    for (newX = x + 1, newY = y - 1; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, adjoin_same[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == 0; newX++, newY--, adjoin_empty[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, gap_same[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == 0; newX++, newY--, gap_empty[3]++)
        ;
    for (; newX < BOARD_SIZE && newY >= 0 && board[newX][newY] == color; newX++, newY--, gap_gap_same[3]++)
        ;

    for (newX = x - 1, newY = y; newX >= 0 && board[newX][newY] == color; newX--, adjoin_same[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == 0; newX--, adjoin_empty[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == color; newX--, gap_same[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == 0; newX--, gap_empty[4]++)
        ;
    for (; newX >= 0 && board[newX][newY] == color; newX--, gap_gap_same[4]++)
        ;

    for (newY = y - 1, newX = x; newY >= 0 && board[newX][newY] == color; newY--, adjoin_same[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == 0; newY--, adjoin_empty[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == color; newY--, gap_same[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == 0; newY--, gap_empty[5]++)
        ;
    for (; newY >= 0 && board[newX][newY] == color; newY--, gap_gap_same[5]++)
        ;

    for (newX = x - 1, newY = y - 1; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, adjoin_same[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == 0; newX--, newY--, adjoin_empty[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, gap_same[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == 0; newX--, newY--, gap_empty[6]++)
        ;
    for (; newX >= 0 && newY >= 0 && board[newX][newY] == color; newX--, newY--, gap_gap_same[6]++)
        ;

    for (newX = x - 1, newY = y + 1; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, adjoin_same[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == 0; newX--, newY++, adjoin_empty[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, gap_same[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == 0; newX--, newY++, gap_empty[7]++)
        ;
    for (; newX >= 0 && newY < BOARD_SIZE && board[newX][newY] == color; newX--, newY++, gap_gap_same[7]++)
        ;

    // for (int i = 0; i < 4; i++) {
    //     newX = x + dx[i], newY = y + dy[i];
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], adjoin_same[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], gap_same[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX += dx[i], newY += dy[i], gap_gap_same[i]++);
    // }
    // for (int i = 0; i < 4; i++) {
    //     newX = x - dx[i], newY = y - dy[i];
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], adjoin_same[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], gap_same[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++);
    //     for (; isInBounds(newX, newY) && board[newX][newY] == color; newX -= dx[i], newY -= dy[i], gap_gap_same[i + 4]++);
    // }

    int _4 = 0, Living_3 = 0;
    for (int i = 0; i < 4; i++)
    {
        if (adjoin_same[i] + adjoin_same[i + 4] == 4 || (adjoin_same[i] == 4 && adjoin_same[i + 4] == 4))
        {
            return true;
        } // 五连
    }

    for (int i = 0; i < 4; i++)
    {
        if (adjoin_same[i] + adjoin_same[i + 4] >= 5)
        {
            return false;
        } // 长连
    }

    for (int i = 0; i < 4; i++)
    {
        if (adjoin_same[i] + adjoin_same[i + 4] == 3)
        {
            bool flag = false;
            if (adjoin_empty[i] > 0)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                    flag++;
            } // 1111_
            if (adjoin_empty[i + 4] > 0)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                    flag++;
            } // _1111
            if (flag)
                _4++;
        } // 四连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 2)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 1)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                {
                    _4 += 1;
                    flag = true;
                }
            } // 111_1
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                {
                    _4 += 1;
                    flag = true;
                }
            } // 1_111
            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0));             // 右边有两个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    Living_3 += 1;
                } //?_111__?, ?__111_?
            }
        } // 三连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 1)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 2)
            {
                _4 += 1;
                flag = true;
            } //?11_11?

            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2)
            {
                _4 += 1;
                flag = true;
            } //?11_11?

            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 1);                                      // 一空一同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));               // 最右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有至少一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    Living_3 += 1;
                } //?_11_1_?,//?_1_11_?
            }
        } // 二连

        else if (adjoin_same[i] + adjoin_same[i + 4] == 0)
        {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 3)
            {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                {
                    _4 += 1;
                    flag = true;
                }
            } //?1_111?
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 3)
            {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                {
                    _4 += 1;
                    flag = true;
                }
            } //?111_1?
            if (!flag)
            {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 2);                                      // 一空二同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));               // 右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)))
                {
                    Living_3 += 1;
                } //?_1_11_?, //?_11_1_?
            }
        } // 一连
    }
    // clock_t end_1 = clock();
    // ttt += (end_1 - start_1);
    if (Living_3 >= 2 || _4 >= 2)
        return false;
    return true;
}

int value[BOARD_SIZE][BOARD_SIZE][2], TotalValue[BOARD_SIZE][BOARD_SIZE];
void GetSingleScore(int x, int y)
{
    for (int i = 0; i < 2; i++)
    {
        Status nowStatus = Value_Board[x][y][i];
        int score = 0;
        if ((nowStatus.Living_3 + nowStatus.Rush_4) >= 2 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = SHA;
        }
        else if (nowStatus.Living_3 >= 1 && (nowStatus.Living_2 >= 2 || nowStatus.Rush_3 >= 1) && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = KUAISHA;
        }
        else if (nowStatus.Rush_3 >= 2 && nowStatus.Living_2 >= 1 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = KUAIXIAOSHA;
        }
        else if (((nowStatus.Rush_3 >= 1 && (nowStatus.Rush_2 + nowStatus.Living_2) >= 2) || nowStatus.Rush_3 >= 2) && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = JIAOCHA;
        }
        else if (nowStatus.Living_2 >= 2 && nowStatus.Rush_2 >= 1 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = YITUAN;
        }
        else if (nowStatus.Living_2 >= 2 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
        {
            score = YIXIAOTUAN;
        }
        else
        {
            score += nowStatus.Right_5 * Value_Right_5;
            score += nowStatus.Living_4 * Value_Living_4;
            score += nowStatus.Rush_4 * Value_Rush_4;
            score += nowStatus.Living_3 * Value_Living_3;
            score += nowStatus.Rush_3 * Value_Rush_3;
            score += nowStatus.Living_2 * Value_Living_2;
            score += nowStatus.Rush_2 * Value_Rush_2;
        }
        value[x][y][i] = score;
    }
    TotalValue[x][y] = value[x][y][0] + value[x][y][1];
}

int GetSingleScore_2(int x, int y, int color)
{
    GetStatus(x, y, color);
    Status nowStatus = Value_Board[x][y][color - 1];
    int score = 0;
    if ((nowStatus.Living_3 + nowStatus.Rush_4) >= 2 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = SHA;
    }
    else if (nowStatus.Living_3 >= 1 && (nowStatus.Living_2 >= 2 || nowStatus.Rush_3 >= 1) && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = KUAISHA;
    }
    else if (nowStatus.Rush_3 >= 2 && nowStatus.Living_2 >= 1 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = KUAIXIAOSHA;
    }
    else if (((nowStatus.Rush_3 >= 1 && (nowStatus.Rush_2 + nowStatus.Living_2) >= 2) || nowStatus.Rush_3 >= 2) && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = JIAOCHA;
    }
    else if (nowStatus.Living_2 >= 2 && nowStatus.Rush_2 >= 1 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = YITUAN;
    }
    else if (nowStatus.Living_2 >= 2 && nowStatus.Right_5 == 0 && nowStatus.Living_4 == 0)
    {
        score = YIXIAOTUAN;
    }
    else
    {
        score += nowStatus.Right_5 * Value_Right_5;
        score += nowStatus.Living_4 * Value_Living_4;
        score += nowStatus.Rush_4 * Value_Rush_4;
        score += nowStatus.Living_3 * Value_Living_3;
        score += nowStatus.Rush_3 * Value_Rush_3;
        score += nowStatus.Living_2 * Value_Living_2;
        score += nowStatus.Rush_2 * Value_Rush_2;
    }
    return score;
}
int GetWholeScore(int color)
{
    int value = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == color)
            {
                value += GetSingleScore_2(i, j, color);
            }
            else if (board[i][j] == 3 - color)
            {
                value -= GetSingleScore_2(i, j, 3 - color);
            }
        }
    }
    return value;
}