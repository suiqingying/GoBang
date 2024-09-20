#include "search.h"

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

void MinMax(int depth, int color, int x, int y)
{
    if (depth == 0) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInBounds(nx, ny) && board[nx][ny] == 0) {
            board[nx][ny] = color;
            MinMax(depth - 1, -color, nx, ny);
            board[nx][ny] = 0;
        }
    }
}