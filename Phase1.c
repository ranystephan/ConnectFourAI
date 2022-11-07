// Github Repo: ranystephan/ConnectFourAI
// https://github.com/ranystephan/ConnectFourAI

#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h> /* needed to call time */


char board[6][7]; //board as a global variable

char namePlayer1[20];
char namePlayer2[20];


double timePlayer1 = 0;
double timePlayer2 = 0;



//Amount of empty spaces in each coloumn
int columnHeight[7] = {5,5,5,5,5,5,5};

//All methods needed for the program
void resetBoard();
void displayBoard();
int tossCoin();
void player1Move();
void player2Move();
int checkWinner();
int checkFreeSpaces();
void askPlayerNames();
int checkVertical();
int checkHorizontal();
int checkDiagonal1();
int checkDiagonal2();


int main()
{
  int winner = 0;


  
  resetBoard();
  askPlayerNames();
  int first=tossCoin(namePlayer1, namePlayer2);


  while (winner == 0 && checkFreeSpaces() != 0 )
    {
      displayBoard();
      if (first==1)
      { // for checking which player goes first according to the toss
        player1Move();
        winner = checkWinner();
        if (winner != 0){
            displayBoard(); // for displaying the board after the final move 
            printf("Congratulations, %s, you won!", namePlayer1);
            break;
        }
      }
      
      else{
        player2Move();
        winner = checkWinner();
        if (winner != 0){
            displayBoard(); // for displaying the board after the final move 
            printf("Congratulations, %s, you won!", namePlayer2);
            break;
        }
      }

      displayBoard();
      if (first==2){ // for checking which player goes second according to the toss
        player1Move();
        winner = checkWinner();
        if (winner != 0){
            displayBoard(); // for displaying the board after the final move 
            printf("Congratulations, %s, you won!", namePlayer1);
            break;
        }
      }
      else{
        player2Move();
        winner = checkWinner();
        if (winner != 0){
            displayBoard(); // for displaying the board after the final move 
            printf("Congratulations, %s, you won!", namePlayer2);
            break;
        }
      }

    }
        
        
      winner = checkWinner(winner); //error with comparison pointer and integer in checkHorizontal and checkVertical

      if (winner == 0){
      if(timePlayer1 > timePlayer2){
        printf("%s, you took %f seconds \n",namePlayer1, timePlayer1);
        printf("%s, you took %f seconds \n",namePlayer2, timePlayer2);

        printf("Therefore, even if it's a tie, %s, YOU WON!!!", namePlayer2);

      }
      else if(timePlayer1 < timePlayer2){
        printf("%s, you took %f seconds \n",namePlayer1, timePlayer1);
        printf("%s, you took %f seconds \n",namePlayer2, timePlayer2);

        printf("Therefore, even if it's a tie, %s, YOU WON!!! \n", namePlayer1);
      }
      else{
        printf("Sorry, you were both too slow, no one won... \n");
      }

      }
}

// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
int checkWinner()
{
  if (checkHorizontal() != 0)
  {
    return 1;
  }
  else if (checkVertical() != 0)
  {
    return 1;
  }
  else if(checkDiagonal1() !=0){
    return 1;
  }
  else if(checkDiagonal2() !=0){
    return 1;
  }
  
  else{
      return 0;
  }
  // Test cases: 
}

// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner horizontally. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
int checkHorizontal()
{
  for (int row = 0; row <= 5; row++)
  {
    for (int col = 0; col <= 3; col++)
    {
      if (board[row][col] == board[row][col + 1] &&  board[row][col + 2] == board[row][col + 3] && board[row][col] == board[row][col + 3] && board[row][col] != 0)
          {
            return 1;
          }
    }
  }
    return 0;
}

// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner on the first diagonal. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
int checkDiagonal1(){
    for(int j = 0; j < 4; ++j){
        for(int i = 0; i < 3; ++i){
            if(board[i+j][i] == board[i+j+1][i+1] && board[i+j][i] == board[i+2+j][i+2] && board[i+j][i] == board[i+3+j][i+3] && board[i+j][i] != 0){
                return 1;
              }
        }
  }
    return 0;
}

// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner on the second diagonal. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
int checkDiagonal2(){
  for(int j = 0; j < 4; ++j){
      for(int i = 3; i < 5; ++i){
          if(board[j][i] == board[j+1][i-1] && board[j][i] == board[j+2][i-2] && board[j][i] == board[j+3][i-3] && board[j][i] != 0){
              return 1;
          }
      }
    }
    return 0;
}


// Requires: nothing
// Modifies: nothing
// Effects: checks if there is a winner vertically. Returns 1 if there is a winner, 0 if there is no winner.
// Testing Strategy: tested with a board with a winner, a board with no winner, and a board with a tie.
int checkVertical()
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

//Requires: nothing
//Modifies: board
//Effects: resets the board to all 0's
//Testing Strategy: tested by running the program and checking if the board is reset
void resetBoard()
{

  for (int i = 0; i < 6; i++)
    {
      for (int j = 0; j < 7; j++)
        {
          board[i][j] = 0;
        }
    }
}


//Requires: nothing
//Modifies: board
//Effects: displays the board
//Testing Strategy: tested by running the program and checking if the board is displayed correctly
void displayBoard()
{
  printf("|1||2||3||4||5||6||7|\n");
  printf("---------------------\n");
  int row, column = 0;

  for (row=0; row < 6; row++){
    for(column = 0; column < 7; column++){
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


void askPlayerNames()
// Requires: nothing
// Modifies: namePlayer1, namePlayer2
// Effects: asks the user for the names of the players
// Testing Strategy: tested by running the program and checking if the names are asked correctly
{
  //Asking player names
  printf("Please Enter Your Name Player1: ");
  scanf("%s", namePlayer1);
  printf("Please Enter Your Name Player2: ");
  scanf("%s", namePlayer2);
  printf("\n");
  printf("Welcome %s, and %s!\n", namePlayer1, namePlayer2);
}


int tossCoin()
// Requires: nothing
// Modifies: nothing
// Effects: tosses a coin to decide who starts first. Returns 1 if player 1 starts first, 2 if player 2 starts first.
// Testing Strategy: tested by running the program and checking if the coin is tossed correctly
{
  srand(time(NULL));
  int headsOrTails = rand() % 2;

  if (headsOrTails == 1){
    printf("%s, the coin chose you! You may start playing!\n\n", namePlayer1);
    return 1;
  
  }else {
    printf("%s, the coin chose you! You may start playing!\n\n", (namePlayer2));
    return 2;
    
  }
}


//Requires: nothing
//Modifies: board
//Effects: asks the player to make a move
//Testing Strategy: tested by running the program and checking if the move is made correctly
void player1Move()
{
  int columnNumber;
  time_t start, end;

  printf("%s, your move...", namePlayer1);
  start = time(NULL);
  do
  {
    printf("Please, enter column #(1 - 7): ");
    scanf("%d", &columnNumber);
    printf("\n");
    columnNumber--;

    //check if column is full or not
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
  } while(board[0][columnNumber] != 0);
  end = time(NULL);

  timePlayer1 += ((double)(end - start));
}


//Requires: nothing
//Modifies: board
//Effects: asks the player to make a move
//Testing Strategy: tested by running the program and checking if the move is made correctly
void player2Move()
{
  int columnNumber;
  time_t start, end;

  printf("%s, your move...", namePlayer2);
  start = time(NULL);
  do
  {
    printf("Please, enter column #(1 - 7): ");
    scanf("%d", &columnNumber);
    columnNumber--;

    //check if column is full or not
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
  } while(board[0][columnNumber] != 0);
  end = time(NULL);
  
  timePlayer2 += ((double)(end - start));

  
}




