// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h>   /* needed to call time */
#include <string.h> 
#include "connect4_AMR.h"

//prototypes
int make_move_AMR();
minimaxReturn minimax_AMR();
int checkWinningSide_AMR();
int checkWinner_AMR();
int evaluateLine_AMR();
int evaluateWindow_AMR();
int firstEmpty_AMR();
void removePin_AMR();
void dropPin_AMR();
int checkVertical_AMR();
int checkHorizontal_AMR();
int checkDiagonal1_AMR();
int checkDiagonal2_AMR();


//NOTE: OUR CODE WORKS CONSIDERING THE BOT MOVE IS 2 ON THE BOARD, since the maximizingPlayer is 2 (which is us)
int make_move_AMR(int board[6][7])
{
    int columnNumber = 0;

    columnNumber = minimax_AMR(board, 10, -10000000, 10000000, 2).column;

    // Note: the clumn number is an index, so we need to add 1 to it to visualize it on the board
    printf("%d", columnNumber);
    return columnNumber;
}
int firstEmpty_AMR(int board[6][7], int column)
{
    for (int j = 6; j >= 0; j--)
    {
        if (board[j][column] == 0)
        {
            return j;
        }
    }
    return -1;
}

// removePin_AMR function removes the highest pin in the column
void removePin_AMR(int board[6][7], int column)
{
    for (int i = 0; i < 6; i++)
    {
        if (board[i][column] != 0)
        {
            board[i][column] = 0;
            break;
        }
    }
}

// dropPin_AMR function that takes an int and drops the pin in the column
void dropPin_AMR(int board[6][7], int column, int side)
{
    // If the column is not full, return the row number
    int firstEmptyRow = firstEmpty_AMR(board, column);
    board[firstEmptyRow][column] = side;
}

minimaxReturn minimax_AMR(int board[ROWS][COLS], int depth, int alpha, int beta, int maximizingPlayer)
// Requires: depth is an integer, alpha and beta are integers, maximizingPlayer is either 1 or 2
// Modifies: nothing
// Effects: returns the best move for the computer
// Testing Strategy: tested by running the program and checking if the computer makes the best move
{
    minimaxReturn ret;
    int check = checkWinningSide_AMR(board, 2) - checkWinningSide_AMR(board, 1);
    if (depth == 0 || checkWinner_AMR(board) == 1)
    {
        if (checkWinner_AMR(board) == 1) // if there is a winner
        {
            checkWinner_AMR(board);
            if (check == 1) // if the winner is the computer (maximizing player)
            {
                ret.column = -2;
                ret.score = 100000000;
                return ret;
            }
            else if (check == -1) // if the winner is not the computer (minimizing player)
            {
                ret.column = -2;
                ret.score = -100000000;
                return ret;
            }
            else // game is over, no more valid moves
            {
                ret.column = -2;
                ret.score = 0;
                return ret;
            }
        }
        else // depth is zero
        {
            ret.column = -2;
            ret.score = evaluateLine_AMR(board);
            return ret;
        }
    }

    if (maximizingPlayer == 2) // if it is the maximizing player's turn
    {
        int bestScore = -1000000;
        int col;

        do
            (col = rand() % 7);
        while (board[0][col] != 0);

        for (int i = 0; i < 7; i++)
        {
            if (board[0][i] == 0)
            {

                dropPin_AMR(board, i, 2);                                    // drops the piece on the board
                int score = minimax_AMR(board, depth - 1, alpha, beta, 1).score; // calculates the score of the tree by calling minimax_AMR recursively
                removePin_AMR(board, i);                                     // removes the piece from the board

                if (score > bestScore) // adjusting scores according to the best one
                {
                    bestScore = score;
                    col = i;
                }

                alpha = max(alpha, bestScore);

                if (beta <= alpha) // pruning the tree if the score is greater than beta
                {
                    break;
                }
            }
        }
        ret.column = col;
        ret.score = bestScore;
        return ret;
    }
    else // same principle but for minimizing player (scores here are negative)
    {
        int bestScore = 1000000;
        int col;

        do
            (col = rand() % 7);
        while (board[0][col] != 0);

        for (int i = 0; i < 7; i++)
        {
            if (board[0][i] == 0)
            {
                dropPin_AMR(board, i, 1);
                int score = minimax_AMR(board, depth - 1, alpha, beta, 2).score;
                removePin_AMR(board, i);

                if (score < bestScore)
                {
                    bestScore = score;
                    col = i;
                }

                beta = min(beta, bestScore);

                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        ret.column = col;
        ret.score = bestScore;
        return ret;
    }
}

int checkWinningSide_AMR(int board[ROWS][COLS], int side)
// Requires: side is either 1 or 2
// Modifies: nothing
// Effects: checks if there is a winner horizontally. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{

    int winningSide = 0;

    // check horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == side && board[i][j + 1] == side && board[i][j + 2] == side && board[i][j + 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check vertical
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == side && board[i + 1][j] == side && board[i + 2][j] == side && board[i + 3][j] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check diagonal1
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == side && board[i + 1][j + 1] == side && board[i + 2][j + 2] == side && board[i + 3][j + 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    // check diagonal2
    for (int i = 0; i < 3; i++)
    {
        for (int j = 6; j >= 3; j--)
        {
            if (board[i][j] == side && board[i + 1][j - 1] == side && board[i + 2][j - 2] == side && board[i + 3][j - 3] == side)
            {
                winningSide = 1;
            }
        }
    }

    return winningSide;
}

int checkWinner_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    if (checkHorizontal_AMR(board) != 0)
    {
        return 1;
    }
    else if (checkVertical_AMR(board) != 0)
    {
        return 1;
    }
    else if (checkDiagonal1_AMR(board) != 0)
    {
        return 1;
    }
    else if (checkDiagonal2_AMR(board) != 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

// evaluateLine_AMR function that evaluates the board
int evaluateLine_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: returns the score of the board
// Testing Strategy: tested by running the program and checking if the computer makes the best move
{
    int score = 0;

    // score center column
    int centerArray[6];
    for (int i = 0; i < 6; i++)
    {
        centerArray[i] = board[i][3];
    }
    int centerCount = 0;
    for (int i = 0; i < 6; i++)
    {
        if (centerArray[i] == 2)
        {
            centerCount++;
        }
    }
    score += centerCount * 3;

    // score horizontal
    for (int i = 0; i < 6; i++)
    {
        int rowArray[7];
        for (int j = 0; j < 7; j++)
        {
            rowArray[j] = board[i][j];
        }
        for (int j = 0; j < 4; j++)
        {
            int window[4] = {rowArray[j], rowArray[j + 1], rowArray[j + 2], rowArray[j + 3]};
            score += evaluateWindow_AMR(window, 2);
        }
    }

    // score vertical
    for (int i = 0; i < 7; i++)
    {
        int colArray[6];
        for (int j = 0; j < 6; j++)
        {
            colArray[j] = board[j][i];
        }
        for (int j = 0; j < 3; j++)
        {
            int window[4] = {colArray[j], colArray[j + 1], colArray[j + 2], colArray[j + 3]};
            score += evaluateWindow_AMR(window, 2);
        }
    }

    // score positive sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = {board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3]};
            score += evaluateWindow_AMR(window, 2);
        }
    }

    // score negative sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = {board[i + 3][j], board[i + 2][j + 1], board[i + 1][j + 2], board[i][j + 3]};
            score += evaluateWindow_AMR(window, 2);
        }
    }

    return score;
}

// evaluate window function
int evaluateWindow_AMR(int window[], int side)
// Requires: window is an array of 4 integers, side is either 1 or 2
// Modifies: nothing
// Effects: returns the score of the window
// Testing Strategy: tested by running the program and checking if the computer makes the best move
{
    int score = 0;
    int oppSide = 3 - side;

    int countSide = 0;
    int countOppSide = 0;
    int countEmpty = 0;

    for (int i = 0; i < 4; i++)
    {
        if (window[i] == side)
        {
            countSide++;
        }
        else if (window[i] == oppSide)
        {
            countOppSide++;
        }
        else
        {
            countEmpty++;
        }
    }

    if (countSide == 4)
    {
        score += 100;
    }
    else if (countSide == 3 && countEmpty == 1)
    {
        score += 5;
    }
    else if (countSide == 2 && countEmpty == 2)
    {
        score += 2;
    }

    if (countOppSide == 3 && countEmpty == 1)
    {
        score -= 4;
    }

    return score;
}

int checkHorizontal_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner horizontally. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    for (int row = 0; row <= 5; row++)
    {
        for (int col = 0; col <= 3; col++)
        {
            if (board[row][col] == board[row][col + 1] && board[row][col + 2] == board[row][col + 3] && board[row][col] == board[row][col + 3] && board[row][col] != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkDiagonal1_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner on the first diagonal. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    for (int row = 0; row <= 2; row++)
    {
        for (int col = 0; col <= 3; col++)
        {
            if (board[row][col] == board[row + 1][col + 1] && board[row + 2][col + 2] == board[row + 3][col + 3] && board[row][col] == board[row + 3][col + 3] && board[row][col] != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkDiagonal2_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner on the second diagonal. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    for (int row = 0; row <= 2; row++)
    {
        for (int col = 6; col >= 3; col--)
        {
            if (board[row][col] == board[row + 1][col - 1] && board[row + 2][col - 2] == board[row + 3][col - 3] && board[row][col] == board[row + 3][col - 3] && board[row][col] != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkVertical_AMR(int board[ROWS][COLS])
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner vertically. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    for (int col = 0; col <= 6; col++)
    {
        for (int row = 0; row <= 2; row++)
        {
            if (board[row][col] == board[row + 1][col] && board[row + 2][col] == board[row + 3][col] && board[row][col] == board[row + 3][col] && board[row][col] != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}
