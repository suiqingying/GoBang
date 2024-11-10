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
    scanf("%d", &game_mode);
    if (game_mode == 1) {
        TwoPlayerBattle();
    } else if (game_mode == 2) {
        HumanVsAI();
    } else {
        printf("无效的选择！\n");
    }
    deinit();
    return 0;
}

void TwoPlayerBattle()
{
    init();
    draw();
    while (running) {
        step++;
        move();
        if (running & isBoardFull()) {
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
    if (mycolor != 1 & mycolor != 2) {
        printf("无效的选择！\n");
        return;
    }
    init();
    draw();
    while (running) {
        step++;
        if (player == mycolor) {
            move();
        } else {
            AImove();
        }
        if (running & isBoardFull()) {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

void move()
{
    SDL_Event e;
    bool success = false;
    while (!success) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x / GRID_SIZE;
                int y = e.button.y / GRID_SIZE;
                if(step == 1) {
                    if (x !=7 || y != 7) {
                        printf("Please place your stone at the H8.\n");
                        continue;
                    }
                }
                if (board[x][y] == 0) {
                    running = judge(x, y, player, game_mode);
                    board[x][y] = player;
                    success = true;
                    printf("%c %d\n", x + 'A', 15 - y);
                }
            }
        }
    }
    draw();
}

void AImove()
{
    int alpha = -MAX_SCORE, beta = MAX_SCORE;
    if (step == 1) {
        pos.x = 7;
        pos.y = 7;
    } else {
        MinMax(maxDepth, player, alpha, beta);
    }
    board[pos.x][pos.y] = player;
    printf("%x %x\n", pos.x, pos.y);
    if (isWin(pos.x, pos.y, player)) {
        printf("You Lost!RUBBISH!\n");
        running = false;
    }
    draw();
}

void pause()
{
    printf("Press Enter key to continue...");
    while (getchar() != '\n') {
        ;
    }
    getchar();
}

