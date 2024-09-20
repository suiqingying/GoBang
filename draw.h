#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define GRID_SIZE 40
#define BOARD_SIZE 15

extern int board[BOARD_SIZE][BOARD_SIZE];

extern SDL_Window *win;
extern SDL_Renderer *renderer;

void draw_board(SDL_Renderer *renderer);
void draw_piece(SDL_Renderer *renderer, int x, int y, int player);
void init();
void draw();
void deinit();
