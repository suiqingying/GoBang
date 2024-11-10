#include "evaluation.h"

int GetWholeScore(int color)
{
    double score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            node p = { i, j, board[i][j] };
            if (board[i][j] == color)
                score += 1.01 * GetSingleScore(p);
            else if (board[i][j] == 3 - color)
                score -= GetSingleScore(p);
        }
    }
    return score;
}

int GetSingleScore(node p)
{
    Status nowStatus = GetStatus(p);
    int score = 0;
    score += nowStatus._ALIVE_5 * ALIVE_5;
    score += nowStatus._ALIVE_4 * ALIVE_4;
    score += nowStatus._ALIVE_3 * ALIVE_3;
    score += nowStatus._ALIVE_2 * ALIVE_2;
    score += nowStatus._ALIVE_1 * ALIVE_1;
    score += nowStatus._BLOCK_4 * BLOCK_4;
    score += nowStatus._BLOCK_3 * BLOCK_3;
    score += nowStatus._BLOCK_2 * BLOCK_2;
    return score;
}

Status GetStatus(node p)
{   
    Status re;
    memset(&re, 0, sizeof(re));
    int oppcolor = 3 - p.color;
    for (int i = 0; i < 4; i++) {
        int count = 1, block = 0;
        for (int j = 1; j <= 4; j++) {
            int newX = p.x + dx[i] * j;
            int newY = p.y + dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == p.color) {
                count++;
            } else {
                if (isInBounds(newX, newY) && board[newX][newY] == oppcolor || !isInBounds(newX, newY)) {
                    block++;
                }
                break;
            }
        }
        for (int j = 1; j <= 4; j++) {
            int newX = p.x - dx[i] * j;
            int newY = p.y - dy[i] * j;
            if (isInBounds(newX, newY) && board[newX][newY] == p.color) {
                count++;
            } else {
                if (isInBounds(newX, newY) && board[newX][newY] == oppcolor || !isInBounds(newX, newY)) {
                    block++;
                }
                break;
            }
        }
        if (count >= 5) {
            re._ALIVE_5++;
        } else if (count == 4) {
            if (block == 0) {
                re._ALIVE_4++;
            } else if (block == 1) {
                re._BLOCK_4++;
            }
        } else if (count == 3) {
            if (block == 0) {
                re._ALIVE_3++;
            } else if (block == 1) {
                re._BLOCK_3++;
            }
        } else if (count == 2) {
            if (block == 0) {
                re._ALIVE_2++;
            } else if (block == 1) {
                re._BLOCK_2++;
            }
        } else if (count == 1 && block == 0) {
            re._ALIVE_1++;
        }
    }
    return re;
}