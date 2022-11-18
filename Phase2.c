// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h>   /* needed to call time */

char board[6][7]; // board as a global variable
int mode;
char namePlayer[20];
char nameOpp[20];
char *nameNoviceBot = "Novice Bot";
char *nameAdvancedBot = "Advanced Bot";
char *nameExpertBot = "Expert Bot";
double timePlayer = 0;
double timePlayer2 = 0;




// Amount of empty spaces in each coloumn
int columnHeight[7] = {5, 5, 5, 5, 5, 5, 5};

#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

// These definitions give context to the code regarding the mode of play, and the name of the opposing player in each case
#define CHOSENMODEMOVE if (mode == 1) { NoviceBotMove(); } else if (mode == 2) { AdvancedBotMove(); } else if (mode == 3)  { ExpertBotMove(); } else {player2Move();}
#define NAMEPLAYER2 (mode == 1) ? nameNoviceBot : (mode == 2) ? nameAdvancedBot : (mode == 3) ? nameExpertBot : nameOpp


struct minimaxReturn
// This struct is used to return the best move and the score of the best move from the minimax function
{
    int column;
    int score;
};
typedef struct minimaxReturn minimaxReturn;

// All methods needed for the program
void resetBoard();
void displayBoard();
int tossCoin();
void playerMove();
void player2Move();
void NoviceBotMove();
void AdvancedBotMove();
void ExpertBotMove();
int evaluateForAI();
int checkWinner();
int checkFreeSpaces();
void askPlayerNameAndMode();
int checkVertical();
int checkHorizontal();
int checkDiagonal1();
int checkDiagonal2();
minimaxReturn minimax();
int evaluateLine();





void playerMove()
// Requires: nothing
// Modifies: board
// Effects: asks the player to make a move
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("%s, your move...", namePlayer);
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
            board[columnHeight[columnNumber]][columnNumber] = 1;
            columnHeight[columnNumber]--;
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer += ((double)(end - start));
}


void player2Move()
// Requires: nothing
// Modifies: board
// Effects: asks the player to make a move
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("%s, your move...", nameOpp);
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
            board[columnHeight[columnNumber]][columnNumber] = 2;
            columnHeight[columnNumber]--;
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer2 += ((double)(end - start));
}

// Function to make a move for the Novice Bot. Note that the Novice Bot is a random bot, and does not use any AI
void NoviceBotMove()
// Requires: nothing
// Modifies: board
// Effects: makes a move for the Novice Bot. 
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("Novice Bot is now playing...\n\n");
    start = time(NULL);

    columnNumber = minimax(1, -1000000, 1000000, 2).column;

    board[columnHeight[columnNumber]][columnNumber] = 2;
    columnHeight[columnNumber]--;
    end = time(NULL);

    timePlayer2 += ((double)(end - start));
}

// AdvancedBotMove function that uses minimax algorithm with alpha-beta pruning to find the best move to the depth assigned
void AdvancedBotMove()
// Requires: nothing
// Modifies: board
// Effects: executes the move of the advanced bot using the minimax algorithm with alpha-beta pruning, with depth of 3
// Testing Strategy: tested by running the program and checking if the move is made correctly
{
    int columnNumber;
    time_t start, end;

    printf("Advanced Bot is now playing...\n\n");
    start = time(NULL);

    columnNumber = minimax(3, -1000000, 1000000, 2).column;

    board[columnHeight[columnNumber]][columnNumber] = 2;
    columnHeight[columnNumber]--;
    end = time(NULL);

    timePlayer2 += ((double)(end - start));
}


// ExpertBotMove function that uses minimax algorithm with alpha-beta pruning to find the best move to the depth assigned
void ExpertBotMove()
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

        columnNumber = minimax(11, -10000000, 10000000, 2).column;


        // check if column is full or not
        if (board[0][columnNumber] != 0)
        {
            printf("Column full!\n");
        }
        else
        {
            printf("Column number: %d \n\n", columnNumber + 1);
            board[columnHeight[columnNumber]][columnNumber] = 2;
            columnHeight[columnNumber]--;
            break;
        }
    } while (board[0][columnNumber] != 0);
    end = time(NULL);

    timePlayer2 += ((double)(end - start));
}

void askPlayerNameAndMode()
// Requires: nothing
// Modifies: namePlayer, NAMEPLAYER2
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
    scanf("%d", &mode);

    // Asking player names
    printf("Please Enter Your Name: ");
    scanf("%s", namePlayer);
    printf("\n");

    // If the mode is 4 (not against bot), ask the name of the second player
    if (mode == 4)
    {
        printf("Please Enter Your Name: ");
        scanf("%s", nameOpp);
        printf("\n");
    }


}


int checkWinner()
// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
{
    if (checkHorizontal() != 0)
    {
        return 1;
    }
    else if (checkVertical() != 0)
    {
        return 1;
    }
    else if (checkDiagonal1() != 0)
    {
        return 1;
    }
    else if (checkDiagonal2() != 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}


int checkHorizontal()
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


int checkDiagonal1()
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


int checkDiagonal2()
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


int checkVertical()
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


void resetBoard()
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



void displayBoard()
// Requires: nothing
// Modifies: board
// Effects: displays the board
// Testing Strategy: tested by running the program and checking if the board is displayed correctly
{
    printf("|1||2||3||4||5||6||7|\n");
    printf("---------------------\n");
    int row, column = 0;

    for (row = 0; row < 6; row++)
    {
        for (column = 0; column < 7; column++)
        {
            printf("|%d|", board[row][column]);
        }
        printf("\n");
    }

    printf("---------------------\n");
}


int checkFreeSpaces()
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
        printf("%s, the coin chose you! You may start playing!\n\n", namePlayer);
        return 1;
    }
    else
    {
        if (mode == 4)
        {
            printf("%s, the coin chose you! You may start playing!\n\n", nameOpp);
            return 2;
        }
        else
        {
            printf("The coin chose the computer! The computer may start playing!\n\n");
            return 2;
        }
    }
}


int checkWinningSide(int side)
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




minimaxReturn minimax(int depth, int alpha, int beta, int maximizingPlayer)
// Requires: depth is an integer, alpha and beta are integers, maximizingPlayer is either 1 or 2
// Modifies: nothing
// Effects: returns the best move for the computer
// Testing Strategy: tested by running the program and checking if the computer makes the best move
{
    minimaxReturn ret;
    int check = checkWinningSide(2) - checkWinningSide(1);
    if (depth == 0 || checkWinner() == 1)
    {
        if (checkWinner() == 1)
        {
            checkWinner();
            if (check == 1)
            {
                ret.column = -2;
                ret.score = 100000000;
                return ret;
            }
            else if (check == -1)
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
            ret.score = evaluateLine();
            return ret;
        }
    }

    if ( maximizingPlayer == 2 )
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
                board[columnHeight[i]][i] = 2;
                columnHeight[i]--;
                int score = minimax(depth - 1, alpha, beta, 1).score;
                board[columnHeight[i] + 1][i] = 0;
                columnHeight[i]++;

                if (score > bestScore)
                {
                    bestScore = score;
                    col = i;
                }

                alpha = max(alpha, bestScore);

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
    else
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
                board[columnHeight[i]][i] = 1;
                columnHeight[i]--;
                int score = minimax(depth - 1, alpha, beta, 2).score;
                board[columnHeight[i] + 1][i] = 0;
                columnHeight[i]++;

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
int evaluateLine()
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
            int window[4] = { rowArray[j], rowArray[j + 1], rowArray[j + 2], rowArray[j + 3] };
            score += evaluateWindow(window, 2);
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
            int window[4] = { colArray[j], colArray[j + 1], colArray[j + 2], colArray[j + 3] };
            score += evaluateWindow(window, 2);
        }
    }

    // score positive sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = { board[i][j], board[i + 1][j + 1], board[i + 2][j + 2], board[i + 3][j + 3] };
            score += evaluateWindow(window, 2);
        }
    }

    // score negative sloped diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int window[4] = { board[i + 3][j], board[i + 2][j + 1], board[i + 1][j + 2], board[i][j + 3] };
            score += evaluateWindow(window, 2);
        }
    }
    
    return score;
}






int main()
{
    int winner = 0;

    resetBoard();
    askPlayerNameAndMode();

    int first = tossCoin();

    while (winner == 0 && checkFreeSpaces() != 0)
    {
        displayBoard();
        if (first == 1)
        { // for checking which player goes first according to the toss
            playerMove();
            winner = checkWinner();
            if (winner != 0)
            {
                displayBoard(); // for displaying the board after the final move
                printf("Congratulations, %s, you won!", namePlayer);
                break;
            }
        }
        else
        {
            CHOSENMODEMOVE;
            winner = checkWinner();
            if (winner != 0)
            {
                displayBoard(); // for displaying the board after the final move
                printf("%s, I am sorry to say that you lost!", namePlayer);
                break;
            }
        }

        displayBoard();
        if (first == 2)
        { // for checking which player goes second according to the toss
            playerMove();
            winner = checkWinner();
            if (winner != 0)
            {
                displayBoard(); // for displaying the board after the final move
                printf("Congratulations, %s, you won!", namePlayer);
                break;
            }
        }
        else
        {
            CHOSENMODEMOVE;
            winner = checkWinner();
            if (winner != 0)
            {
                displayBoard(); // for displaying the board after the final move
                printf("%s, I am sorry to say that you lost!", namePlayer);
                break;
            }
        }
    }

    winner = checkWinner();

    if (winner == 0)
    {
        if (timePlayer > timePlayer2)
        {
            printf("%s, you took %f seconds \n", namePlayer, timePlayer);
            printf("%s, you took %f seconds \n", NAMEPLAYER2, timePlayer2);

            printf("Therefore, even if it's a tie, %s, YOU WON!!!", NAMEPLAYER2);
        }
        else if (timePlayer < timePlayer2)
        {
            printf("%s, you took %f seconds \n", namePlayer, timePlayer);
            printf("%s, you took %f seconds \n", NAMEPLAYER2, timePlayer2);

            printf("Therefore, even if it's a tie, %s, YOU WON!!!", namePlayer);
        }
        else
        {
            printf("Sorry, you were both too slow, no one won... \n");
        }
    }
}


