#include "main.h"

int step, player = 1, mycolor;
int game_mode; // 1 表示人人对战，2 表示人机对战
bool running = true;

int main() {
    // 添加选择游戏模式的菜单
    printf("请选择游戏模式:\n");
    printf("1. 人人对战\n");
    printf("2. 人机对战\n");
    printf("3. ai模拟\n");
    scanf("%d", &game_mode);
    if (game_mode == 1) {
        HumanVsHuman();
    } else if (game_mode == 2) {
        HumanVsAI();
    } else if (game_mode == 3) {
        AIVsAI();
    } else {
        printf("无效的选择！\n");
    }
    deinit();
    return 0;
}

void HumanVsHuman() {
    init();
    draw();
    while (running) {
        step++;
        move();
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull()) {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

void HumanVsAI() {
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
            AImove(player);
        }
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull()) {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}

void AIVsAI() {
    init();
    draw();
    while (running) {
        step++;
        AImove(player);
        printf("黑棋得分：%d\n", GetWholeScore(BLACK));
        printf("白棋得分：%d\n", GetWholeScore(WHITE));
        if (running & isBoardFull()) {
            printf("The game is a draw!\n");
            running = false;
        }
        player = 3 - player; // 切换玩家
    }
    pause();
}
void move() {
    SDL_Event e;
    bool success = false;
    while (!success) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x / GRID_SIZE;
                int y = e.button.y / GRID_SIZE;
                if (step == 1) {
                    if (x != 7 || y != 7) {
                        printf("Please place your stone at the H8.\n");
                        continue;
                    }
                }
                if (board[x][y] == 0) {
                    bool flag = judge(x, y, player);
                    if (!flag) {
                        running = false;
                        printf("%c %d is banned\n", x + 'A', 15 - y);
                        return;
                    }
                    board[x][y] = player;
                    success = true;
                    printf("%c %d\n", x + 'A', 15 - y);
                    if (isWin(x, y, player)) {
                        if (player == BLACK) {
                            printf("Black wins!\n");
                        } else {
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
void AImove() {
    clock_t start = clock();
    ttt = 0;
    cnt = 0;
    PTR_To_Point pos;
    pos = (PTR_To_Point)malloc(sizeof(Point) * 1);
    if (step == 1) {
        pos->x = 7;
        pos->y = 7;
    } else if (step == 2) {
        pos->x = 8;
        pos->y = 8;
    }  else {
        int DEPTH = 8;
        MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // if (player == WHITE) {
        //     int DEPTH = 6;
        //     MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // } else {
        //     int DEPTH = 8;
        //     MinMax(player, pos, DEPTH, -MAX_SCORE, MAX_SCORE, DEPTH);
        // }
    }
    printf("%c %d\n", pos->x + 'A', 15 - pos->y);
    board[pos->x][pos->y] = player;
    if (isWin(pos->x, pos->y, player)) {
        if (player == BLACK) {
            printf("Black wins!\n");
        } else {
            printf("White wins!\n");
        }
        running = false;
    }
    printf("cnt = %d\n", cnt);
    free(pos);
    draw();
    clock_t end = clock();
    printf("use time %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
