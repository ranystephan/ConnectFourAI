// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#ifndef FUNCTIONS_PHASE2_H
#define FUNCTIONS_PHASE2_H

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h>   /* needed to call time */


// macro declarations
#define ROWS 6
#define COLS 7

// typedef declaration
struct minimaxReturn
// This struct is used to return the best move and the score of the best move from the minimax_AMR function
{
    int column;
    int score;
};
typedef struct minimaxReturn minimaxReturn;

#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))


// function declarations
int make_move_AMR(int board[ROWS][COLS]);
minimaxReturn minimax_AMR(int board[ROWS][COLS], int depth, int alpha, int beta, int maximizingPlayer);
int checkWinningSide_AMR(int board[ROWS][COLS], int side);
int checkWinner_AMR(int board[ROWS][COLS]);
int evaluateLine_AMR(int board[ROWS][COLS]);
int evaluateWindow_AMR(int window[], int side);
int firstEmpty_AMR(int board[ROWS][COLS], int column);
void removePin_AMR(int board[ROWS][COLS], int column);
void dropPin_AMR(int board[ROWS][COLS], int column, int side);
int checkVertical_AMR(int board[ROWS][COLS]);
int checkHorizontal_AMR(int board[ROWS][COLS]);
int checkDiagonal1_AMR(int board[ROWS][COLS]);
int checkDiagonal2_AMR(int board[ROWS][COLS]);

#endif // FUNCTIONS_PHASE2_H