#include "search.h"

node pos;



int MinMax(int depth, int color, int alpha, int beta)
{
    if (depth == 0 || isBoardFull()) {
        return GetWholeScore(color);
    }
    // POINTS P = GetPoints(color);
    // for (int k = 0; k < MAXLENGTH; k++)
    // {
    //     printf("(%d %d) ", P.pos[k].x, P.pos[k].y);
    // }
    // printf("\n");
    
    // for (int k = 0; k < MAXLENGTH; k++) {
    //     if(P.pos[k].x==-1) break;
    //     board[P.pos[k].x][P.pos[k].y] = color;
    //     int score = -MinMax(depth - 1, 3 - color, -beta, -alpha);
    //     board[P.pos[k].x][P.pos[k].y] = 0;
    //     if (score > alpha) {
    //         alpha = score;
    //         if (depth == maxDepth) {
    //             pos.x = P.pos[k].x;
    //             pos.y = P.pos[k].y;
    //         }
    //     }
    //     if (alpha >= beta) {
    //         return alpha;
    //     }
    // }
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

POINTS GetPoints(int color)
{
    bool vis[BOARD_SIZE][BOARD_SIZE];
    memset(vis, 0, sizeof(vis));
    POINTS P;
    int val[BOARD_SIZE][BOARD_SIZE];
    memset(val, 0, sizeof(val));
    for (int i = 0; i < MAXLENGTH; i++) {
        P.pos[i].x = -1;
        P.pos[i].y = -1;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                continue;
            }
            for (int k = -3; k <= 3; k++) {
                for (int l = 0; l < 4; l++) {
                    if (isInBounds(i + k * dx[l], j + k * dy[l])) {
                        vis[i + k * dx[l]][j + k * dy[l]] = 1;
                    }
                }
            }
        }
    }
    if (step == 1) {
        P.pos[0].x = 7;
        P.pos[0].y = 7;
        return P;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            val[i][j] = -MAX_SCORE;
            if (!vis[i][j] || board[i][j] != 0) continue;
            board[i][j] = color;
            val[i][j] = GetWholeScore(color);
            // board[i][j] = 3 - color;
            // val[i][j] += GetWholeScore(3-color);
            board[i][j] = 0;
        }
    }
    for (int k = 0; k < MAXLENGTH; k++) {
        int max_score = -MAX_SCORE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (val[i][j] > max_score) {
                    max_score = val[j][k];
                    P.pos[k].x = i;
                    P.pos[k].y = j;
                }
            }
        }
        val[P.pos[k].x][P.pos[k].y] = -MAX_SCORE;
    }
    return P;
}