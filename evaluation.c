#include "evaluation.h"

bool judge(int x, int y, int player, int game_mode)
{
    if (player == 2) {
        int status = isWin(x, y, player);
        if (status == 1)
            printf("White wins!\n");
        return !status;
    }
    Status res = GetStatus(x, y, player);
    int status = BanMove(x, y, res);
    if (status <= 3 && status >= 1) {
        if (status == 1)
            printf("Double three ban!\n");
        else if (status == 2)
            printf("Double four ban!\n");
        else if (status == 3)
            printf("Too long ban!\n");
        if (game_mode == 1)
            printf("White wins!\n");
        else
            printf("You Lost!RUBBISH!\n");
        return false;
    }
    if (status == 4) {
        if (game_mode == 1) {
            if (player == 1) {
                printf("White wins!\n");
            } else if (player == 2) {
                printf("Black wins!\n");
            }
        } else
            printf("You win\n");
        return false;
    }
    return true;
}

bool isInBounds(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool isBoardFull()
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool isWin(int x, int y, int player)
{
    for (int i = 0; i < 4; i++) {
        int count = 1;
        for (int j = 1; j <= 4; j++) {
            int newX = x + dx[i] * j;
            int newY = y + dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == player) {
                count++;
            } else {
                break;
            }
        }
        for (int j = 1; j <= 4; j++) {
            int newX = x - dx[i] * j;
            int newY = y - dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == player) {
                count++;
            } else {
                break;
            }
        }
        if ((player == 2 && count >= 5) || (player == 1 && count == 5)) {
            return true;
        }
    }
    return false;
}

Status GetStatus(int x, int y, int color)
{
    // ? 为3 - color 或 边界，_ 为空位，1 为color
    int adjoin_same[8];
    int adjoin_empty[8];
    int gap_same[8];
    int gap_empty[8];
    int gap_gap_same[8];
    int newX, newY;
    Status res;
    memset(&res, 0, sizeof(res));
    for (int i = 0; i < 8; i++) {
        adjoin_same[i] = adjoin_empty[i] = gap_same[i] = gap_empty[i] = gap_gap_same[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        newX = x + dx[i], newY = y + dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], adjoin_same[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_same[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_gap_same[i]++)
            ;
    }
    for (int i = 0; i < 4; i++) {
        newX = x - dx[i], newY = y - dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], adjoin_same[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_same[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_gap_same[i + 4]++)
            ;
    }

    for (int i = 0; i < 4; i++) {

        if (adjoin_same[i] + adjoin_same[i + 4] == 4) {
            res.Right_5 = true;
            return res;
        } // 五连

        if (adjoin_same[i] + adjoin_same[i + 4] >= 5) {
            if (color == 1) {
                res.Too_long = true;
            } else {
                res.Right_5 = true;
            }
            return res;
        } // 长连

        if (adjoin_same[i] + adjoin_same[i + 4] == 3) {
            int flag = 0;
            if (adjoin_empty[i] > 0) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                    flag++;
            } // 1111_
            if (adjoin_empty[i + 4] > 0) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                    flag++;
            } // _1111
            if (flag == 1)
                res.Rush_4 += 1;
            if (flag == 2)
                res.Living_4 += 1;
        } // 四连

        if (adjoin_same[i] + adjoin_same[i + 4] == 2) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 1) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 111_1
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 1_111
            if (!flag) {
                bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0)); // 右边有两个空位且不会形成长连
                bool flagR_2 = (adjoin_empty[i] == 1 && gap_same[i] == 0); // 右边有恰好一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
                bool flagL_2 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0);
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                } //?_111__?, ?__111_?
                else if ((((flagR_2 && flagR_3) || (flagR_1 && !flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || (((flagL_2 && flagL_3) || (flagL_1 && !flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                }
            }
        } // 三连

        if (adjoin_same[i] + adjoin_same[i + 4] == 1) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 2) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?11_11?

            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?11_11?
            // 事实上这两处的禁手判断是多余的

            if (!flag) {
                bool flagR_1 = adjoin_empty[i] = 1 && gap_same[i] == 1; // 一空一同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0)); // 最右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 0)); // 左边有至少一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 1);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                } //?_11_1_?,//?_1_11_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                }
            }
            // 判断活2和冲2
            bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0)); // 右边至少有两个空位且不会形成长连
            bool flagR_2 = (adjoin_empty[i] > 3 || (adjoin_empty[i] == 3 && gap_same[i] == 0)); // 右边至少有三个空位且不会形成长连
            bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边至少有一个空位且不会形成长连
            bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
            bool flagL_2 = (adjoin_empty[i + 4] > 3 || (adjoin_empty[i + 4] == 3 && gap_same[i + 4] == 0));
            bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
            if ((flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 2, 1)) || (flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 2, -1))) {
                res.Living_2 += 1;
            } else if (flagR_1 && (flagR_2 || flagR_3) && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 2, color) || (flagL_1 && (flagL_2 || flagL_3) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 2, color))) {
                res.Rush_2 += 1;
            }
        } // 二连

        if (adjoin_same[i] + adjoin_same[i + 4] == 0) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 3) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?1_111?
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 3) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?111_1?
            if (!flag) {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 2); // 一空二同色
                bool flagR_2 = (gap_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0)); // 右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                    flag = true;
                } //?_1_11_?, //?_11_1_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                    flag = true;
                }
            }
            if (!flag) {
                bool flag1_1 = (adjoin_empty[i] == 1 && gap_same[i] == 1 && gap_empty[i] >= 1);
                bool flag1_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0));
                bool flag1_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0));
                bool flag2_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1 && gap_empty[i + 4] >= 1);
                bool flag2_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flag2_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flag1_1 && flag1_2 && flag1_3 && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 2, color)) || (flag2_1 && flag2_2 && flag2_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 3, color)))
                    res.Living_2 += 1;
                else if ((flag1_1 && (flag1_2 || flag1_3) && Noban(x, y, i, adjoin_same[i] + 1, color) && Noban(x, y, i, adjoin_same[i] + 3, color)) || (flag2_1 && (flag2_2 || flag2_3) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color) && Noban(x, y, i + 4, adjoin_same[i + 4] + 3, color)))
                        res.Rush_2 += 1;
            }
        } // 一连
    }
    return res;
}

bool judge_next(int x, int y, int color)
{
    // ? 为3 - color 或 边界，_ 为空位，1 为color
    int adjoin_same[8];
    int adjoin_empty[8];
    int gap_same[8];
    int gap_empty[8];
    int gap_gap_same[8];
    int newX, newY;
    Status res;
    memset(&res, 0, sizeof(res));
    for (int i = 0; i < 8; i++) {
        adjoin_same[i] = adjoin_empty[i] = gap_same[i] = gap_empty[i] = gap_gap_same[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        newX = x + dx[i], newY = y + dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], adjoin_same[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_same[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_gap_same[i]++)
            ;
    }
    for (int i = 0; i < 4; i++) {
        newX = x - dx[i], newY = y - dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], adjoin_same[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_same[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_gap_same[i + 4]++)
            ;
    }

    for (int i = 0; i < 4; i++) {

        if (adjoin_same[i] + adjoin_same[i + 4] == 4) {
            res.Right_5 = true;
            return 1;
        } // 五连

        if (adjoin_same[i] + adjoin_same[i + 4] >= 5) {
            if (color == 1) {
                res.Too_long = true;
                return 0;
            } else {
                res.Right_5 = true;
                return 1;
            }
        } // 长连

        if (adjoin_same[i] + adjoin_same[i + 4] == 3) {
            int flag = 0;
            if (adjoin_empty[i] > 0) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color))
                    flag++;
            } // 1111_
            if (adjoin_empty[i + 4] > 0) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))
                    flag++;
            } // _1111
            if (flag == 1)
                res.Rush_4 += 1;
            if (flag == 2)
                res.Living_4 += 1;
        } // 四连

        if (adjoin_same[i] + adjoin_same[i + 4] == 2) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 1) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 111_1
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 1) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } // 1_111
            if (!flag) {
                bool flagR_1 = (adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_same[i] == 0)); // 右边有两个空位且不会形成长连
                bool flagR_2 = (adjoin_empty[i] == 1 && gap_same[i] == 0); // 右边有恰好一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_same[i + 4] == 0));
                bool flagL_2 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0);
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                } //?_111__?, ?__111_?
                else if ((((flagR_2 && flagR_3) || (flagR_1 && !flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || (((flagL_2 && flagL_3) || (flagL_1 && !flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                }
            }
        } // 三连

        if (adjoin_same[i] + adjoin_same[i + 4] == 1) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 2) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?11_11?

            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?11_11?
            // 事实上这两处的禁手判断是多余的

            if (!flag) {
                bool flagR_1 = adjoin_empty[i] = 1 && gap_same[i] == 1; // 一空一同色
                bool flagR_2 = (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_same[i] == 0)); // 最右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 0)); // 左边有至少一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] = 1 && gap_same[i + 4] == 1);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                } //?_11_1_?,//?_1_11_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                }
            }
        } // 二连

        if (adjoin_same[i] + adjoin_same[i + 4] == 0) {
            bool flag = false;
            if (adjoin_empty[i] == 1 && gap_same[i] == 3) {
                if (Noban(x, y, i, adjoin_same[i] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?1_111?
            if (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 3) {
                if (Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color)) {
                    res.Rush_4 += 1;
                    flag = true;
                }
            } //?111_1?
            if (!flag) {
                bool flagR_1 = (adjoin_empty[i] == 1 && gap_same[i] == 2); // 一空二同色
                bool flagR_2 = (gap_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0)); // 右边有至少一个空位且不会形成长连
                bool flagR_3 = (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0)); // 左边有一个空位且不会形成长连
                bool flagL_1 = (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 2);
                bool flagL_2 = (gap_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_same[i + 4] == 0));
                bool flagL_3 = (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_same[i] == 0));
                if ((flagR_1 && flagR_2 && flagR_3 && Noban(x, y, i, adjoin_same[i] + 1, color)) || (flagL_1 && flagL_2 && flagL_3 && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Living_3 += 1;
                    flag = true;
                } //?_1_11_?, //?_11_1_?
                else if (((flagR_1 && (flagR_2 || flagR_3)) && Noban(x, y, i, adjoin_same[i] + 1, color)) || ((flagL_1 && (flagL_2 || flagL_3)) && Noban(x, y, i + 4, adjoin_same[i + 4] + 1, color))) {
                    res.Rush_3 += 1;
                    flag = true;
                }
            }
        } // 一连
    }
    if (res.Living_3 >= 2 || res.Living_4 + res.Rush_4 >= 2)
        return 0;
    return 1;
}

int BanMove(int x, int y, Status res)
{
    if (res.Right_5)
        return 4;
    if (res.Living_3 >= 2)
        return 1;
    if (res.Living_4 + res.Rush_4 >= 2)
        return 2;
    if (res.Too_long)
        return 3;
}

int Noban(int x, int y, int direction, int num, int color)
{
    if (board[x][y])
        printf("%c %d %d\n", x + 'A', 15 - y, board[x][y]);
    if (color == 2)
        return 1;
    int fl = 1;
    if (direction >= 4)
        fl = -1;
    board[x][y] = color;
    int newX = x + fl * dx[direction] * num, newY = y + fl * dy[direction] * num;
    bool flag = judge_next(newX, newY, color);
    board[x][y] = 0;
    return flag;
}

int GetWholeScore(int color)
{
    double score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            node p = { i, j, board[i][j] };
            if (board[i][j] == color)
                score += 1.01 * GetSingleScore(p);
            else if (board[i][j] == 3 - color)
                score -= GetSingleScore(p);
        }
    }
    return score;
}

int GetSingleScore(node p)
{
    Status nowStatus = GetStatus(p.x, p.y, p.color);
    int score = 0;
    score += nowStatus.Living_2 * Value_Rush_2;
    score += nowStatus.Living_3 * Value_Rush_3;
    score += nowStatus.Living_4 * Value_Rush_4;
    score += nowStatus.Rush_2 * Value_Living_2;
    score += nowStatus.Rush_3 * Value_Living_3;
    score += nowStatus.Rush_4 * Value_Living_4;
    score += nowStatus.Right_5 * Value_Right_5;
    return score;
}