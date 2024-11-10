#include "judge.h"

bool judge(int x, int y, int player, int game_mode)
{
    if (player == 2)
        return !isWin(x, y, player);
    int statue = BanMove(x, y);
    if (statue) {
        if (statue == 1)
            printf("Double three ban!\n");
        else if (statue == 2)
            printf("Double four ban!\n");
        else if (statue == 3)
            printf("Too long ban!\n");
        if (game_mode == 1)
            printf("Player %d wins!\n", 3 - player);
        else
            printf("You Lost!RUBBISH!\n");
        return false;
    }
    if (isWin(x, y, player)) {
        if (game_mode == 1)
            printf("Player %d wins!\n", player);
        else
            printf("You win!\n");
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

int BanMove(int x, int y)
{
    int newX, newY;
    int adjoin_black[8];
    int adjoin_empty[8];
    int gap_black[8];
    int gap_empty[8];
    int gap_gap_black[8];
    for (int i = 0; i < 8; i++) {
        adjoin_black[i] = adjoin_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        newX = x + dx[i], newY = y + dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], adjoin_black[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_black[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_gap_black[i]++)
            ;
    }
    for (int i = 0; i < 4; i++) {
        newX = x - dx[i], newY = y - dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], adjoin_black[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_black[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++)
            ;
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_gap_black[i + 4]++)
            ;
    }
    int Num_4 = 0;
    int Num_3 = 0;
    int whe_four;
    int whe_three;

    for (int i = 0; i < 4; i++) {
        if (adjoin_black[i] + adjoin_black[i + 4] == 4) {
            return 0;
        }
        if (adjoin_black[i] + adjoin_black[i + 4] >= 5) {
            return 3;
        }
    }

    for (int i = 0; i < 4; i++) {
        whe_four = 0;
        whe_three = 0;
        if (adjoin_black[i] + adjoin_black[i + 4] == 3) {
            if (adjoin_empty[i] > 0) {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1))
                    whe_four = 1;
            } // 1111_
            if (adjoin_empty[i + 4] > 0) {
                if (!Reban(x, y, i, adjoin_black[i] + 1, -1))
                    whe_four = 1;
            } // _1111
            if (whe_four)
                Num_4++;
        }

        if (adjoin_black[i] + adjoin_black[i + 4] == 2) {
            if (adjoin_empty[i] == 1 && gap_black[i] == 1) {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1)) whe_four = 1;
            } // 111_1
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 1) {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                    whe_four = 1;
            } // 1_111
            if (whe_four)
                Num_4++;

            if ((adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_black[i] == 0)) && (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_black[i + 4] == 0))) {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1))
                    whe_three = 1;
            } //?_111__?
            if ((adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_black[i + 4] == 0)) && (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0))) {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                    whe_three = 1;
            } //?__111_?
            if (whe_three)
                Num_3++;
        }

        if (adjoin_black[i] + adjoin_black[i + 4] == 1) {
            if (adjoin_empty[i] == 1 && gap_black[i] == 2) 
            {
               if (!Reban(x, y, i, adjoin_black[i] + 1, 1))
                    Num_4++;
            } //?11_11?

            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 2) 
            {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1)) 
                    Num_4++;
            } //?11_11?

            if (adjoin_empty[i] = 1 && gap_black[i] == 1 && (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_black[i] == 0)) && (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 0))) //?_11_1_?
            {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1)) 
                    Num_3++;
            } //?_11_1_?
            if (adjoin_empty[i + 4] = 1 && gap_black[i + 4] == 1 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_black[i + 4] == 0)) && (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0))) //?_1_11_?
            {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1)) 
                    Num_3++;
            } //?_1_11_?
        }

        if (adjoin_black[i] + adjoin_black[i + 4] == 0) {
            if (adjoin_empty[i] == 1 && gap_black[i] == 3) 
            {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1)) 
                    Num_4++;
            } //?1_111?
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 3) 
            {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1)) {
                    Num_4++;
                }
            } //?111_1?

            if (adjoin_empty[i] == 1 && gap_black[i] == 2 && (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_black[i] == 0)) && (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 0))) 
            {
                if (!Reban(x, y, i, adjoin_black[i] + 1, 1)) {
                    Num_3++;
                }
            } //?_1_11_?
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 2 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_black[i + 4] == 0)) && (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0))) 
            {
                if (!Reban(x, y, i, adjoin_black[i + 4] + 1, -1)) {
                    Num_3++;
                }
            } //?_11_1_?
        }
    }

    if (Num_3 >= 2)
        return 1;
    if (Num_4 >= 2)
        return 2;

    return 0; // 无禁手
}

int Reban(int x, int y, int direction, int num, int fl)
{
    board[x][y] = 1;
    int res = BanMove(x + fl * dx[direction] * num, y + fl * dy[direction] * num);
    board[x][y] = 0;
    return res;
}