#include "main.h"

int step, player = 1, mycolor;
int game_mode; // 1 表示人人对战，2 表示人机对战
bool running = true;

int main()
{
    // 添加选择游戏模式的菜单
    printf("请选择游戏模式:\n");
    printf("1. 人人对战\n");
    printf("2. 人机对战\n");
    printf("3. ai模拟\n");
    scanf("%d", &game_mode);
    if (game_mode == 1)
    {
        HumanVsHuman();
    }
    else if (game_mode == 2)
    {
        HumanVsAI();
    }
    else if (game_mode == 3)
    {
        AIVsAI();
    }
    else
    {
        printf("无效的选择！\n");
    }
    deinit();
    return 0;
}

void HumanVsHuman()
{
    init();
    draw();
    while (running)
    {
        step++;
        move();
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull())
        {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

void HumanVsAI()
{
    printf("请玩家选择执棋颜色：\n");
    printf("1. 黑棋\n");
    printf("2. 白棋\n");
    scanf("%d", &mycolor);
    if (mycolor != 1 & mycolor != 2)
    {
        printf("无效的选择！\n");
        return;
    }
    init();
    draw();
    while (running)
    {
        step++;
        if (player == mycolor)
        {
            move();
        }
        else
        {
            AImove(player);
        }
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull())
        {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

void AIVsAI()
{
    init();
    draw();
    while (running)
    {
        step++;
        AImove(player);
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull())
        {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

int tot = 0;

void move()
{
    SDL_Event e;
    bool success = false;
    while (!success)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x / GRID_SIZE;
                int y = e.button.y / GRID_SIZE;
                if (step == 1)
                {
                    if (x != 7 || y != 7)
                    {
                        printf("Please place your stone at the H8.\n");
                        continue;
                    }
                }
                if (board[x][y] == 0)
                {
                    bool flag = judge(x, y, player);
                    if (!flag)
                    {
                        running = false;
                        printf("%c %d is banned\n", x + 'A', 15 - y);
                        return;
                    }
                    board[x][y] = player;
                    tot++;
                    success = true;
                    printf("第 %d 手下在 %c %d\n", step, x + 'A', 15 - y);
                    if (isWin(x, y, player))
                    {
                        if (player == BLACK)
                        {
                            printf("Black wins!\n");
                        }
                        else
                        {
                            printf("White wins!\n");
                        }
                        running = false;
                    }
                }
            }
        }
    }
    draw();
}
int cnt;
void get(PTR_To_Point pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}
void AImove()
{
    clock_t start = clock();
    PTR_To_Point pos;
    pos = (PTR_To_Point)malloc(sizeof(Point));
    pos->x = -1;
    pos->y = -1;
    if (step == 1)
    {
        get(pos,7,7);
    }
    if (step == 2)
    {
        get(pos, 8,8);
    }
    if (step == 3)
    {
        
        if (board[8][8] == WHITE || board[8][6] == WHITE)
        {
            get(pos, 6, 7);
        }
        
        if (board[6][6] == WHITE || board[6][8] == WHITE)
        {
            get(pos, 8, 7);
        }
        
        if (board[8][7] == WHITE || board[7][6] == WHITE)
        {
            get(pos, 8, 6);
        }
       
        if (board[6][7] == WHITE || board[7][8] == WHITE)
        {
            get(pos, 6, 8);
        }
    }
    if (step == 5)
    {
        
        if (board[8][8] == WHITE && board[8][7] == WHITE)
        {
            get(pos, 8, 6);
        }
        if (board[8][8] == WHITE && board[5][7] == WHITE)
        {
            get(pos, 6, 8);
        }
        if (board[8][8] == WHITE && board[7][9] == WHITE)
        {
            get(pos, 7, 6);
        }
        if (board[8][8] == WHITE && board[8][6] == WHITE)
        {
            get(pos, 8, 7);
        }
        if (board[8][8] == WHITE && board[9][7] == WHITE)
        {
            get(pos, 7, 9);
        }
        // 第二步白棋下左下
        if (board[8][6] == WHITE && board[8][7] == WHITE)
        {
            get(pos, 8, 8);
        }
        if (board[8][6] == WHITE && board[5][7] == WHITE)
        {
            get(pos, 6, 6);
        }
        if (board[8][6] == WHITE && board[7][5] == WHITE)
        {
            get(pos, 7, 8);
        }
        if (board[8][6] == WHITE && board[8][8] == WHITE)
        {
            get(pos, 8, 7);
        }
        if (board[8][6] == WHITE && board[9][7] == WHITE)
        {
            get(pos, 7, 5);
        }
        // 第二步白棋下右上
        if (board[6][8] == WHITE && board[9][7] == WHITE)
        {
            get(pos, 8, 8);
        }
        if (board[6][8] == WHITE && board[6][7] == WHITE)
        {
            get(pos, 6, 6);
        }
        if (board[6][8] == WHITE && board[7][9] == WHITE)
        {
            get(pos, 7, 6);
        }
        if (board[6][8] == WHITE && board[6][6] == WHITE)
        {
            get(pos, 6, 7);
        }
        if (board[6][8] == WHITE && board[5][7] == WHITE)
        {
            get(pos, 7, 9);
        }
        // 第二步白棋下左上
        if (board[6][6] == WHITE && board[6][7] == WHITE)
        {
            get(pos, 6, 8);
        }
        if (board[6][6] == WHITE && board[9][7] == WHITE)
        {
            get(pos, 8, 6);
        }
        if (board[6][6] == WHITE && board[7][5] == WHITE)
        {
            get(pos, 7, 8);
        }
        if (board[6][6] == WHITE && board[6][8] == WHITE)
        {
            get(pos, 6, 7);
        }
        if (board[6][6] == WHITE && board[5][7] == WHITE)
        {
            get(pos, 7, 5);
        }

        // 第二步白棋下下面
        if (board[8][7] == WHITE && (board[9][5] == WHITE || board[9][6] == WHITE))
        {
            get(pos, 6, 8);
        }
        if (board[8][7] == WHITE && board[6][8] == WHITE)
        {
            get(pos, 9, 6);
        }
        if (board[8][7] == WHITE && board[7][8] == WHITE)
        {
            get(pos, 9, 5);
        }
        if (board[8][7] == WHITE && board[7][6] == WHITE)
        {
            get(pos, 6, 5);
        }
        // 第二步白棋下左面
        if (board[7][6] == WHITE && (board[9][5] == WHITE || board[8][5] == WHITE))
        {
            get(pos, 6, 8);
        }
        if (board[7][6] == WHITE && board[6][8] == WHITE)
        {
            get(pos, 8, 5);
        }
        if (board[7][6] == WHITE && board[6][7] == WHITE)
        {
            get(pos, 9, 5);
        }
        if (board[7][6] == WHITE && board[8][7] == WHITE)
        {
            get(pos, 6, 5);
        }
        // 第二步白棋下上面
        if (board[6][7] == WHITE && (board[5][8] == WHITE || board[5][9] == WHITE))
        {
            get(pos, 8, 6);
        }
        if (board[6][7] == WHITE && board[8][6] == WHITE)
        {
            get(pos, 5, 8);
        }
        if (board[6][7] == WHITE && board[7][6] == WHITE)
        {
            get(pos, 5, 9);
        }
        if (board[6][7] == WHITE && board[7][8] == WHITE)
        {
            get(pos, 5, 6);
        }
        // 第二步白棋下右面
        if (board[7][8] == WHITE && (board[5][9] == WHITE || board[6][9] == WHITE))
        {
            get(pos, 8, 6);
        }
        if (board[7][8] == WHITE && board[8][7] == WHITE)
        {
            get(pos, 5, 9);
        }
        if (board[7][8] == WHITE && board[8][6] == WHITE)
        {
            get(pos, 6, 9);
        }
        if (board[7][8] == WHITE && board[6][7] == WHITE)
        {
            get(pos, 5, 6);
        }
    }
    if (step == 7)
    {
        if (board[8][8] == WHITE && board[5][7] == WHITE && board[8][6] == WHITE && board[6][8] == BLACK)
        {
            get(pos, 8, 9);
        }
        if (board[8][8] == WHITE && board[5][7] == WHITE && board[8][6] == WHITE && board[6][6] == BLACK)
        {
            get(pos, 8, 5);
        }
        if (board[8][8] == WHITE && board[5][7] == WHITE && board[5][9] == WHITE)
        {
            get(pos, 5, 8);
        }
        if (board[8][6] == WHITE && board[5][7] == WHITE && board[5][5] == WHITE)
        {
            get(pos, 5, 6);
        }
    }
    if (step == 9)
    {
        if (board[8][8] == WHITE && board[5][7] == WHITE && board[5][9] == WHITE && board[7][6] == WHITE)
        {
            get(pos, 6, 9);
        }
        if (board[8][6] == WHITE && board[5][7] == WHITE && board[5][5] == WHITE && board[7][8] == WHITE)
        {
            get(pos, 6, 5);
        }
    }
    if (step == 4)
    {
        if (board[7][7] == BLACK && board[6][7] == BLACK)
        {
            get(pos, 5, 7);
        }
        if (board[7][7] == BLACK && board[7][6] == BLACK)
        {
            get(pos, 7, 5);
        }
        if (board[7][7] == BLACK && board[7][8] == BLACK)
        {
            get(pos, 7, 9);
        }
        if (board[7][7] == BLACK && board[8][7] == BLACK)
        {
            get(pos, 9, 7);
        }
        if (board[7][7] == BLACK && board[6][8] == BLACK)
        {
            get(pos, 8, 6);
        }
        if (board[7][7] == BLACK && board[8][6] == BLACK)
        {
            get(pos, 6, 8);
        }
        if (board[7][7] == BLACK && board[6][6] == BLACK)
        {
            get(pos, 8, 7);
        }
    }
    if (step == 6)
    {
        if (board[7][7] == BLACK && board[6][7] == BLACK && board[6][8] == BLACK)
        {
            get(pos, 8, 6);
        }
        if (board[7][7] == BLACK && board[6][7] == BLACK && board[7][6] == BLACK)
        {
            get(pos, 7, 5);
        }
        if (board[7][7] == BLACK && board[6][6] == BLACK && board[8][6] == BLACK)
        {
            get(pos, 6, 8);
        }
        if (board[7][7] == BLACK && board[7][6] == BLACK && board[8][6] == BLACK)
        {
            get(pos, 6, 8);
        }
    }
    if (step == 225)
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == 0)
                {
                    pos->x = i;
                    pos->y = j;
                    break;
                }
            }
        }
    }
    if (!isInBounds(pos->x, pos->y))
    {
        cnt = 0;
        int DEPTH = 8;
        MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // if (player == WHITE)
        // {
        //     cnt = 0;
        //     int DEPTH = 6;
        //     MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // }
        // else
        // {
        //     cnt = 0;
        //     int DEPTH = 8;
        //     MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // }
    }
    printf("%d\n", cnt);
    printf("第 %d 手下在 %c %d\n", step, pos->x + 'A', 15 - pos->y);
    if (!isInBounds(pos->x, pos->y))
    {
        printf("The position is out of bounds!\n");
        running = false;
        return;
    }
    board[pos->x][pos->y] = player;
    tot++;
    if (isWin(pos->x, pos->y, player))
    {
        if (player == BLACK)
        {
            printf("Black wins!\n");
        }
        else
        {
            printf("White wins!\n");
        }
        running = false;
    }

    free(pos);
    draw();
    clock_t end = clock();
    printf("use time %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
