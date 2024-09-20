#include "main.h"

int game_mode; // 1 表示人人对战，2 表示人机对战
int step, player = 1, mycolor;
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
    init(); draw();
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
                if (board[x][y] == 0) {
                    board[x][y] = player;
                    success = true;
                    if (isWin(x, y, player)) {
                        if (game_mode == 1)
                            printf("Player %d wins!\n", player);
                        else
                            printf("You win!\n");
                        running = false;
                    }
                }
            }
        }
    }
    draw();
}

void AImove()
{
    int bestX = -1, bestY = -1, bestScore = -1 << 20;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == 0) {
                board[x][y] = player;
                int score = evaluate();
                board[x][y] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    bestX = x;
                    bestY = y;
                }
            }
        }
    }
    board[bestX][bestY] = player;
    if (isWin(bestX, bestY, player)) {
        printf("you lost,hahaha\n");
        running = false;
    }
    draw();
}

bool isInBounds(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
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
        if (count >= 5) {
            return true;
        }
    }
    return false;
}

bool isBoardFull()
{
    return step == BOARD_SIZE * BOARD_SIZE;
}

int evaluate()
{
    return 0;
}