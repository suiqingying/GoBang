#include "judge.h"

bool judge(int x, int y, int player, int game_mode) {
    if (player == 2) return !isWin(x, y, player);
    int statue = BanMove(x, y);
    if (statue) {
        if (statue == 1)
            printf("Double three ban!\n");
        else if (statue == 2)
            printf("Double four ban!\n");
        else if (statue == 3)
            printf("Too long ban!\n");
        if(game_mode == 1)
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
    int newX,newY;    
    int adjoin_black[8]; 
    int adjoin_empty[8]; 
    int gap_black[8];     
    int gap_empty[8];     
    int gap_gap_black[8];  
    for (int i = 0; i < 8; i++)
    {
        adjoin_black[i] = adjoin_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
    }
    for (int i = 0; i < 4; i++)
    {
        newX = x + dx[i], newY = y + dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], adjoin_black[i]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], adjoin_empty[i]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_black[i]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX += dx[i], newY += dy[i], gap_empty[i]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX += dx[i], newY += dy[i], gap_gap_black[i]++);
    }
    for (int i = 0; i < 4; i++)
    {
        newX = x - dx[i], newY = y - dy[i];
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], adjoin_black[i + 4]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], adjoin_empty[i + 4]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_black[i + 4]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 0; newX -= dx[i], newY -= dy[i], gap_empty[i + 4]++);
        for (; isInBounds(newX, newY) && board[newX][newY] == 1; newX -= dx[i], newY -= dy[i], gap_gap_black[i + 4]++);
    }
    int con_four = 0;       //四连(包含活四、冲四)数量
    int active_three = 0;   //活三数量
    int whe_four;           //记录四连两端的落子点状态
    int whe_three;          //记录活三两端的落子点状态
    
    for (int i = 0; i < 4; i++)
    {        
        if (adjoin_black[i] + adjoin_black[i + 4] == 4)
        {
            return 0;
        }
        if (adjoin_black[i] + adjoin_black[i + 4] >= 5)
        {
            return 3;
        }
    }

    //判活四或冲四
    for (int i = 0; i < 4; i++)
    {
        if (adjoin_black[i] + adjoin_black[i + 4] == 3)
        {
            whe_four = 0;//初始化·
            if (adjoin_empty[i] > 0)//四连棋形：1111_
            {
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    whe_four = 1;
                }
            }
            else if (adjoin_empty[i + 4] > 0)//活四棋形：_1111
            {
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    whe_four = 1;
                }
            }
            if (whe_four)
            {
                con_four++;
            }
        }
    }

    //落子形成三连
    for (int i = 0; i < 4; i++)
    {
        if (adjoin_black[i] + adjoin_black[i + 4] == 2)
        {
            //检查是否为间隔的冲四
            if (adjoin_empty[i] == 1 && gap_black[i] == 1)//冲四棋形：111_1
            {
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    con_four++;
                }
            }
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 1)//冲四棋形：1_111
            {
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    con_four++;
                }
            }

            //检查是否为活三
            whe_three = 0;//初始化
            if ((adjoin_empty[i] > 2 || (adjoin_empty[i] == 2 && gap_black[i] == 0)) && 
            (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] = 1 && gap_black[i + 4] == 0)))//活三棋形：?_111__?
            {
                //活三右端的落子点状态，排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    whe_three = 1;
                }
            }
            if ((adjoin_empty[i + 4] > 2 || (adjoin_empty[i + 4] == 2 && gap_black[i + 4] == 0)) &&
            (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0)))//活三棋形：?__111_?
            {
                //活三左端的落子点状态，排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    whe_three = 1;
                }
            }
            //根据两端的落子点状态判断是否为活三
            if (whe_three)
            {
                active_three++;
            }
        }
    }

    //落子形成二连
    for (int i = 0; i < 4; i++)
    {
        if (adjoin_black[i] + adjoin_black[i + 4] == 1)
        {
            //检查是否为间隔的冲四
            if (adjoin_empty[i] == 1 && gap_black[i] == 2)//冲四棋形：?11_11?，对“右”方向的判断
            {
                if (!BanMove(x + dx[i] * (adjoin_black[i] + 1), y + dy[i] * (adjoin_black[i] + 1)))
                {
                    con_four++;
                }
            }
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 2)//冲四棋形：?11_11?，对“左”方向的判断
            {
                if (!BanMove(x - dx[i] * (adjoin_black[i + 4] + 1), y - dy[i] * (adjoin_black[i] + 1)))
                {
                    con_four++;
                }
            }

            //检查是否为活三
            if ( adjoin_empty[i] = 1 && gap_black[i] == 1 && (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_black[i] == 0)) &&
            (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 0)))//活三棋形：?_11_1_?,对“右”方向的判断
            {
                //二连右端的落子点状态，已经人为排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    active_three++;
                }
            }
            if (adjoin_empty[i + 4] = 1 && gap_black[i + 4] == 1 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_black[i + 4] == 0)) &&
            (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0)))//活三棋形：?_1_11_?,对“左”方向的判断
            {
                //二连左端的落子点状态，已经人为排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    active_three++;
                }
            }
        }
    }

    //落子形成单连
    for (int i = 0; i < 4; i++)
    {
        if (adjoin_black[i] + adjoin_black[i + 4] == 0)
        {
            //检查是否为间隔的冲四
            if (adjoin_empty[i] == 1 && gap_black[i] == 3)//冲四棋形：?1_111?，对“右”方向的判断
            {
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    con_four++;
                }
            }
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 3)//冲四棋形：?1_111?，对“左”方向的判断
            {
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    con_four++;
                }
            }

            //检查是否为活三
            if (adjoin_empty[i] == 1 && gap_black[i] == 2 && (gap_empty[i] > 1 || (gap_empty[i] == 1 && gap_gap_black[i] == 0)) &&
            (adjoin_empty[i + 4] > 1 || (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 0)))//活三棋形：?_1_11_?,对“右”方向的判断
            {
                //单连右端的落子点状态，已经人为排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i] + 1, 1))
                {
                    active_three++;
                }
            }
            if (adjoin_empty[i + 4] == 1 && gap_black[i + 4] == 2 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 && gap_gap_black[i + 4] == 0)) &&
            (adjoin_empty[i] > 1 || (adjoin_empty[i] == 1 && gap_black[i] == 0)))//活三棋形：?_11_1_?,对“左”方向的判断
            {
                //单连左端的落子点状态，已经人为排除非活四情况，故能落子则必为活三
                if(!Reban(x, y, i, adjoin_black[i + 4] + 1, -1))
                {
                    active_three++;
                }
            }
        }
    }
    //根据活三、活四数量判断是否为禁手
    if (active_three >= 2)//活三数量大于等于2
    {
        return 1;
    }
    if (con_four >= 2)//活四数量大于等于2
    {
        return 2;
    }

    return 0;//无禁手，返回值0
}

int Reban(int x, int y, int direction, int num, int fl) {
    board[x][y] = 1;
    int res = BanMove(x + fl * dx[direction] * num, y + fl * dy[direction] * num);
    board[x][y] = 0;
    return res;
}