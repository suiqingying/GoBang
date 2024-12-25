#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 630
#define WINDOW_HEIGHT 650
#define GRID_SIZE 40
#define BOARD_SIZE 15
#define BLACK 1
#define WHITE 2
extern int tot;

extern int board[BOARD_SIZE][BOARD_SIZE];

extern const int dx[];
extern const int dy[];

extern SDL_Window *win;
extern SDL_Renderer *renderer;

void draw_board(SDL_Renderer *renderer);
void draw_piece(SDL_Renderer *renderer, int x, int y, int player);
void init();
void draw();
void deinit();
void pause();