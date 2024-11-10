#include "draw.h"
#include <math.h>


const int dx[] = { 1, 0, 1, 1 };
const int dy[] = { 0, 1, 1, -1 };

int board[BOARD_SIZE][BOARD_SIZE];

SDL_Window *win;
SDL_Renderer *renderer;

// 绘制圆形的函数
void draw_circle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // 水平方向的距离
            int dy = radius - h; // 垂直方向的距离
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void draw_board(SDL_Renderer *renderer)
{
    // 设置棋盘颜色为浅木色
    SDL_SetRenderDrawColor(renderer, 222, 184, 135, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // 绘制棋盘边框
    SDL_Rect rect = {GRID_SIZE / 2 - 2 + 10, GRID_SIZE / 2 - 2 + 10, GRID_SIZE * (BOARD_SIZE - 1) + 5, GRID_SIZE * (BOARD_SIZE - 1) + 5};
    SDL_RenderDrawRect(renderer, &rect);
    // 设置网格线颜色为黑色
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        SDL_RenderDrawLine(renderer, GRID_SIZE * i + GRID_SIZE / 2 + 10, GRID_SIZE / 2 + 10, GRID_SIZE * i + GRID_SIZE / 2 + 10, GRID_SIZE * (BOARD_SIZE - 0.5) + 10);
        SDL_RenderDrawLine(renderer, GRID_SIZE / 2 + 10, GRID_SIZE * i + GRID_SIZE / 2 + 10, GRID_SIZE * (BOARD_SIZE - 0.5) + 10, GRID_SIZE * i + GRID_SIZE / 2 + 10);
    }
}

void draw_piece(SDL_Renderer *renderer, int x, int y, int player)
{
    if (player == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色棋子
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 白色棋子
    }
    // 调整棋子位置，使其位于网格线的交叉点上
    int centerX = x * GRID_SIZE + GRID_SIZE / 2 + 10;
    int centerY = y * GRID_SIZE + GRID_SIZE / 2 + 10;
    draw_circle(renderer, centerX, centerY, GRID_SIZE / 2 - 2); // 减去2以防止超出边界
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() == -1)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    win = SDL_CreateWindow("GoBang", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
}
void draw_text(SDL_Renderer *renderer, const char *text, int x, int y, SDL_Color color)
{
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
    if (font == NULL)
    {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}


void draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    draw_board(renderer);
// 绘制左侧和下方的标号
    SDL_Color textColor = {0, 0, 0, 255}; // 黑色
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        char label[3];
        snprintf(label, sizeof(label), "%d", i + 1);

        // 绘制左侧标号
        draw_text(renderer, label, 5, (14 - i) * GRID_SIZE + GRID_SIZE / 2, textColor);

        snprintf(label, sizeof(label), "%c", 'A' + i);
        // 绘制下方标号
        draw_text(renderer, label, i * GRID_SIZE + GRID_SIZE / 2 + 10, BOARD_SIZE * GRID_SIZE + 5, textColor);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != 0)
            {
                draw_piece(renderer, i, j, board[i][j]);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void deinit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}