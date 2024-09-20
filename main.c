#include "main.h"

int game_mode; // 1 表示人人对战，2 表示人机对战
int board[BOARD_SIZE][BOARD_SIZE];
int player = 1;
int running = 1;
int main() {

    // 添加选择游戏模式的菜单
    printf("请选择游戏模式:\n");
    printf("1. 人人对战\n");
    printf("2. 人机对战\n");
    scanf("%d", &game_mode);
    init();
    
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x / GRID_SIZE;
                int y = e.button.y / GRID_SIZE;
                if (board[x][y] == 0) {
                    board[x][y] = player;
                    player = 3 - player; // 切换玩家
                }
            }
        }
        draw();
    }

    deinit();
    return 0;
}