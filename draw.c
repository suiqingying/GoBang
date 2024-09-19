#include "main.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define GRID_SIZE 40
#define BOARD_SIZE 15

void draw_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= BOARD_SIZE; i++) {
        SDL_RenderDrawLine(renderer, GRID_SIZE * i, 0, GRID_SIZE * i, WINDOW_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, GRID_SIZE * i, WINDOW_WIDTH, GRID_SIZE * i);
    }
}

void draw_piece(SDL_Renderer *renderer, int x, int y, int player) {
    if (player == 1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black piece
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White piece
    }
    SDL_Rect rect = {x * GRID_SIZE - GRID_SIZE / 2, y * GRID_SIZE - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(renderer, &rect);
}

void draw() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow("Gobang", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    int player = 1;
    int running = 1;
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
                    player = 3 - player; // Switch player
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        draw_board(renderer);

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != 0) {
                    draw_piece(renderer, i, j, board[i][j]);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}