// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h>   /* needed to call time */
#include "Phase2.h"

// global variables
int mode_AMR;
char namePlayer_AMR[20];
char nameOpp_AMR[20];
char *nameNoviceBot_AMR = "Novice Bot";
char *nameAdvancedBot_AMR = "Advanced Bot";
char *nameExpertBot_AMR = "Expert Bot";
double timePlayer_AMR = 0;
double timePlayer2_AMR = 0;
int AI_PIECE_AMR;
int PLAYER_PIECE_AMR;
int PLAYER2_PIECE_AMR;

// All methods needed for the program
void resetBoard();
void displayBoard();
int tossCoin();
void playerMove();
void player2Move();
void NoviceBotMove();
void AdvancedBotMove();
void ExpertBotMove();
int checkWinner();
int checkFreeSpaces();
void askPlayerNameAndMode();
int checkVertical();
int checkHorizontal();
int checkDiagonal1();
int checkDiagonal2();
minimaxReturn minimax();
int evaluateLine();
int firstEmpty_AMR();

int firstEmpty_AMR(int **board, int column)
{
    for (int j = 5; j >= 0; j--)
    {
        if (board[j][column] == 0)
        {
                return j;
        }
    }
    return -1;

}

// removePin function removes the highest pin in the column
void removePin_AMR(int **board, int column)
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




// dropPin function that takes an int and drops the pin in the column
void dropPin_AMR(int **board, int column, int side)
{
    // If the column is not full, return the row number
    int firstEmptyRow = firstEmpty_AMR(board, column);
    board[firstEmptyRow][column] = side;
}

void playerMove(int **board)
// Requires: nothing
// Modifies: board
// Effects: asks the player to make a move
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("%s, your move...", namePlayer_AMR);
    start = time(NULL);
    do
    {
        printf("Please, enter column #(1 - 7): ");
        scanf("%d", &columnNumber);
        printf("\n");
        columnNumber--;

        // check if column is full or not
        if (board[0][columnNumber] != 0)
        {
            printf("Column full!\n");
        }
        else
        {
            dropPin_AMR(board, columnNumber, PLAYER_PIECE_AMR);
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer_AMR += ((double)(end - start));
}

void player2Move(int **board)
// Requires: nothing
// Modifies: board
// Effects: asks the player to make a move
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("%s, your move...", nameOpp_AMR);
    start = time(NULL);
    do
    {
        printf("Please, enter column #(1 - 7): ");
        scanf("%d", &columnNumber);
        columnNumber--;

        // check if column is full or not
        if (board[0][columnNumber] != 0)
        {
            printf("Column full!\n");
        }
        else
        {
            dropPin_AMR(board, columnNumber, PLAYER2_PIECE_AMR);
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer2_AMR += ((double)(end - start));
}

// Function to make a move for the Novice Bot. Note that the Novice Bot is a random bot, and does not use any AI
void NoviceBotMove(int **board)
// Requires: nothing
// Modifies: board
// Effects: makes a move for the Novice Bot.
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("Novice Bot is now playing...\n\n");
    start = time(NULL);

    columnNumber = minimax(board, 1, -1000000, 1000000, AI_PIECE_AMR).column;

    dropPin_AMR(board, columnNumber, AI_PIECE_AMR);

    end = time(NULL);

    timePlayer2_AMR += ((double)(end - start));
}

// AdvancedBotMove function that uses minimax algorithm with alpha-beta pruning to find the best move to the depth assigned
void AdvancedBotMove(int **board)
// Requires: nothing
// Modifies: board
// Effects: executes the move of the advanced bot using the minimax algorithm with alpha-beta pruning, with depth of 3
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("Advanced Bot is now playing...\n\n");
    start = time(NULL);

    columnNumber = minimax(board, 3, -1000000, 1000000, AI_PIECE_AMR).column;

    dropPin_AMR(board, columnNumber, AI_PIECE_AMR);

    end = time(NULL);

    timePlayer2_AMR += ((double)(end - start));
}

// ExpertBotMove function that uses minimax algorithm with alpha-beta pruning to find the best move to the depth assigned
void ExpertBotMove(int **board)
// Requires: nothing
// Modifies: board
// Effects: executes the move of the expert bot taken from the minimax algorithm
// Testing Strategy: tested by running the program and checking if the move is made correctly

{
    int columnNumber;
    time_t start, end;

    start = time(NULL);
    do
    {
        printf("\nExpert Bot is now playing...\n");
        start = time(NULL);

        columnNumber = minimax(board, 10, -10000, 10000, AI_PIECE_AMR).column;

        // check if column is full or not
        if (board[0][columnNumber] != 0)
        {
            printf("Column full!\n");
        }
        else
        {
            printf("Column number chosen by the bot: %d \n\n", columnNumber + 1);
            
            dropPin_AMR(board, columnNumber, AI_PIECE_AMR);
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer2_AMR += ((double)(end - start));
}

void askPlayerNameAndMode()
// Requires: nothing
// Modifies: namePlayer_AMR, NAMEPLAYER2
// Effects: asks the user for the names of the players
// Testing Strategy: tested by running the program and checking if the names are asked correctly
{
    // Ask the player what mode he wants to play
    printf("Please choose a mode: \n");
    printf("1. Easy\n");
    printf("2. Advanced\n");
    printf("3. Expert\n");
    printf("4. Multiplayer\n");
    printf("Choose one of the modes #(1 - 4) : ");
    scanf("%d", &mode_AMR);

    // Asking player names
    printf("Please Enter Your Name: ");
    scanf("%s", namePlayer_AMR);
    printf("\n");

    // If the mode is 4 (not against bot), ask the name of the second player
    if (mode_AMR == 4)
    {
        printf("Please Enter Your Name: ");
        scanf("%s", nameOpp_AMR);
        printf("\n");
    }
}

int checkWinner(int **board)
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    if (checkHorizontal(board) != 0)
    {
        return 1;
    }
    else if (checkVertical(board) != 0)
    {
        return 1;
    }
    else if (checkDiagonal1(board) != 0)
    {
        return 1;
    }
    else if (checkDiagonal2(board) != 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int checkHorizontal(int **board)
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

int checkDiagonal1(int **board)
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

int checkDiagonal2(int **board)
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

int checkVertical(int **board)
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

void resetBoard(int **board)
// Requires: nothing
// Modifies: board
// Effects: resets the board to all 0's
// Testing Strategy: tested by running the program and checking if the board is reset
{

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            board[i][j] = 0;
        }
    }
}




void displayBoard(int **board)
// Requires: nothing
// Modifies: board
// Effects: displays the board
// Testing Strategy: tested by running the program and checking if the board is displayed correctly
{
    printf("|1||2||3||4||5||6||7|\n");
    printf("---------------------\n");
    int row, column = 0;

    for (row = 0; row < ROWS; row++)
    {
        for (column = 0; column < COLS; column++)
        {
            printf("|%d|", board[row][column]);
        }
        printf("\n");
    }

    printf("---------------------\n");
}


int checkFreeSpaces(int **board)
// Requires: nothing
// Modifies: nothing
// Effects: checks if there are any free spaces on the board. Returns 1 if there are free spaces, 0 if there are no free spaces.
// Testing Strategy: tested with a board with free spaces, a board with no free spaces, and a board with a tie.
{
    int freeSpaces = 42;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] != 0)
            {
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}

int tossCoin()
// Requires: nothing
// Modifies: nothing
// Effects: tosses a coin to decide who starts first. Returns 1 if Player starts first, 2 if player 2 starts first.
// Testing Strategy: tested by running the program and checking if the coin is tossed correctly
{
    srand(time(NULL));
    int headsOrTails = rand() % 2;

    if (headsOrTails == 1)
    {
        PLAYER_PIECE_AMR = 1;
        PLAYER2_PIECE_AMR = 2;
        AI_PIECE_AMR = 2;
        printf("%s, the coin chose you! You may start playing!\n\n", namePlayer_AMR);
        return 1;
    }
    else
    {

        if (mode_AMR == 4)
        {
            PLAYER_PIECE_AMR = 2;
            PLAYER2_PIECE_AMR = 1;
            printf("%s, the coin chose you! You may start playing!\n\n", nameOpp_AMR);
            return 2;
        }
        else
        {
            AI_PIECE_AMR = 1;
            PLAYER_PIECE_AMR = 2;
            printf("The coin chose the computer! The computer may start playing!\n\n");
            return 2;
        }
    }
}

int checkWinningSide(int **board, int side)
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

minimaxReturn minimax(int **board, int depth, int alpha, int beta, int maximizingPlayer)
// Requires: depth is an integer, alpha and beta are integers, maximizingPlayer is either 1 or 2
// Modifies: nothing
// Effects: returns the best move for the computer
// Testing Strategy: tested by running the program and checking if the computer makes the best move
{
    minimaxReturn ret;
    int check = checkWinningSide(board, 2) - checkWinningSide(board, 1);
    if (depth == 0 || checkWinner(board) == 1)
    {
        if (checkWinner(board) == 1) // if there is a winner
        {
            checkWinner(board);
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
            ret.score = evaluateLine(board, AI_PIECE_AMR);
            return ret;
        }
    }

    if (maximizingPlayer == AI_PIECE_AMR) // if it is the maximizing player's turn
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

                dropPin_AMR(board, i, AI_PIECE_AMR); // drops the piece on the board
                int score = minimax(board, depth - 1, alpha, beta, PLAYER_PIECE_AMR).score; // calculates the score of the tree by calling minimax recursively
                removePin_AMR(board, i); // removes the piece from the board

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
                dropPin_AMR(board, i, PLAYER_PIECE_AMR);
                int score = minimax(board, depth - 1, alpha, beta, AI_PIECE_AMR).score;
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

// evaluate window function
int evaluateWindow(int window[], int side)
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

// evaluateLine function that evaluates the board
int evaluateLine(int **board, int side)
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
        if (centerArray[i] == side)
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
            score += evaluateWindow(window, side);
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
            score += evaluateWindow(window, side);
        }
    }

    // score positive sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = {board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3]};
            score += evaluateWindow(window, side);
        }
    }

    // score negative sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = {board[i + 3][j], board[i + 2][j + 1], board[i + 1][j + 2], board[i][j + 3]};
            score += evaluateWindow(window, side);
        }
    }

    return score;
}

int main()
{
    int **board = (int **)malloc(6 * sizeof(int *));
    for (int i = 0; i < 6; i++)
    {
        board[i] = (int *)malloc(7 * sizeof(int));
    }

    int winner = 0;

    resetBoard(board);
    askPlayerNameAndMode();
    displayBoard(board);

    int first = tossCoin();

    while (winner == 0 && checkFreeSpaces(board) != 0)
    {
        displayBoard(board);
        if (first == 1)
        { // for checking which player goes first according to the toss
            playerMove(board);
            winner = checkWinner(board);
            if (winner != 0)
            {
                displayBoard(board); // for displaying the board after the final move
                printf("Congratulations, %s, you won!", namePlayer_AMR);
                break;
            }
        }
        else
        {
            CHOSENMODEMOVE;
            winner = checkWinner(board);
            if (winner != 0)
            {
                displayBoard(board); // for displaying the board after the final move
                printf("%s, I am sorry to say that you lost!", namePlayer_AMR);
                break;
            }
        }

        displayBoard(board);
        if (first == 2)
        { // for checking which player goes second according to the toss
            playerMove(board);
            winner = checkWinner(board);
            if (winner != 0)
            {
                displayBoard(board); // for displaying the board after the final move
                printf("Congratulations, %s, you won!", namePlayer_AMR);
                break;
            }
        }
        else
        {
            CHOSENMODEMOVE;
            winner = checkWinner(board);
            if (winner != 0)
            {
                displayBoard(board); // for displaying the board after the final move
                printf("%s, I am sorry to say that you lost!", namePlayer_AMR);
                break;
            }
        }
    }

    winner = checkWinner(board);

    if (winner == 0)
    {
        if (timePlayer_AMR > timePlayer2_AMR)
        {
            printf("%s, you took %f seconds \n", namePlayer_AMR, timePlayer_AMR);
            printf("%s, you took %f seconds \n", NAMEPLAYER2, timePlayer2_AMR);

            printf("Therefore, even if it's a tie, %s, YOU WON!!!", NAMEPLAYER2);
        }
        else if (timePlayer_AMR < timePlayer2_AMR)
        {
            printf("%s, you took %f seconds \n", namePlayer_AMR, timePlayer_AMR);
            printf("%s, you took %f seconds \n", NAMEPLAYER2, timePlayer2_AMR);

            printf("Therefore, even if it's a tie, %s, YOU WON!!!", namePlayer_AMR);
        }
        else
        {
            printf("Sorry, you were both too slow, no one won... \n");
        }
    }
}
