#include "search.h"

node pos;

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

int MinMax(int depth, int color, int alpha, int beta)
{
    if (depth == 0 || isBoardFull()) {
        return GetWholeScore(color);
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                board[i][j] = color;
                int score = -MinMax(depth - 1, 3 - color, -beta, -alpha);
                board[i][j] = 0;
                if (score > alpha) {
                    alpha = score;
                    if (depth == maxDepth) {
                        pos.x = i;
                        pos.y = j;
                    }
                }
                if (alpha >= beta) {
                    return alpha;
                }
            }
        }
    }
    return alpha;
}