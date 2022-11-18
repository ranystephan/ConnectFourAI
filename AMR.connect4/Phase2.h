// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#ifndef FUNCTIONS_PHASE2_H
#define FUNCTIONS_PHASE2_H

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h>   /* needed to call time */

// global variables
extern int mode_AMR;
extern char namePlayer_AMR[20];
extern char nameOpp_AMR[20];
extern char *nameNoviceBot_AMR;
extern char *nameAdvancedBot_AMR;
extern char *nameExpertBot_AMR;
extern double timePlayer_AMR;
extern double timePlayer2_AMR;

// macro declarations
#define ROWS 6
#define COLS 7

// typedef declaration
struct minimaxReturn
// This struct is used to return the best move and the score of the best move from the minimax function
{
    int column;
    int score;
};
typedef struct minimaxReturn minimaxReturn;

#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

// These definitions give context to the code regarding the mode_AMR of play, and the name of the opposing player in each case
#define CHOSENMODEMOVE          \
    if (mode_AMR == 1)              \
    {                           \
        NoviceBotMove(board);   \
    }                           \
    else if (mode_AMR == 2)         \
    {                           \
        AdvancedBotMove(board); \
    }                           \
    else if (mode_AMR == 3)         \
    {                           \
        ExpertBotMove(board);   \
    }                           \
    else                        \
    {                           \
        player2Move(board);     \
    }

#define NAMEPLAYER2 (mode_AMR == 1) ? nameNoviceBot_AMR : (mode_AMR == 2) ? nameAdvancedBot_AMR : (mode_AMR == 3)   ? nameExpertBot_AMR : nameOpp_AMR

//function declarations
void displayBoard(int board[ROWS][COLS]);
void resetBoard(int board[ROWS][COLS]);
void askPlayerNameAndMode();
int tossCoin();
void playerMove(int board[ROWS][COLS]);
void player2Move(int board[ROWS][COLS]);
void NoviceBotMove(int board[ROWS][COLS]);
void AdvancedBotMove(int board[ROWS][COLS]);
void ExpertBotMove(int board[ROWS][COLS]);
int checkWinner(int board[ROWS][COLS]);
int checkFreeSpaces(int board[ROWS][COLS]);
int checkVertical(int board[ROWS][COLS]);
int checkHorizontal(int board[ROWS][COLS]);
int checkDiagonal1(int board[ROWS][COLS]);
int checkDiagonal2(int board[ROWS][COLS]);
int checkWinningSide(int board[ROWS][COLS], int side);
minimaxReturn minimax(int board[ROWS][COLS], int depth, int alpha, int beta, int maximizingPlayer);
int evaluateWindow(int window[], int side);
int evaluateLine(int board[ROWS][COLS]);
int firstEmpty(int board[ROWS][COLS], int column);
void removePin(int board[ROWS][COLS], int column);
void dropPin(int board[ROWS][COLS], int column, int side);





#endif // FUNCTIONS_PHASE2_H