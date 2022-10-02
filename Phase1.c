#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h> /* needed to call time */


char board[6][7]; //board as a global variable

char namePlayer1[20];
char namePlayer2[20];

void resetBoard();
void displayBoard();
void tossCoin();
void playerMove();
char checkWinner(char);
int checkFreeSpaces();
void askPlayerNames();


int main()
{
  char winner = ' ';

  resetBoard();
  askPlayerNames();
  tossCoin(namePlayer1, namePlayer2);


  while (winner == ' ' && checkFreeSpaces() != 0 )
    {
      displayBoard();
      playerMove();


    }

}




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
{
  //Asking player names
  printf("Please Enter Your Name Player1: ");
  scanf("%s", namePlayer1);
  printf("Please Enter Your Name Player2: ");
  scanf("%s", namePlayer2);
  printf("\n");
  printf("Welcome %s, and %s!\n", namePlayer1, namePlayer2);
}

void tossCoin()
{
  srand(time(NULL));
  int headsOrTails = rand() % 2; 

  if (headsOrTails == 1){
    printf("%s, the coin chose you! You may start playing!\n\n", namePlayer1);
  }else {
    printf("%s, the coin chose you! You may start playing!\n\n", (namePlayer2));
  }
}



void playerMove()
{
  int columnNumber;

  printf("Please, enter column #(1 - 7): ");
  scanf("%d", &columnNumber);
  columnNumber--;

  do
  {
    //check if column is full or not
    if (board[0][columnNumber] != 0)
    {
      printf("Column full!\n");
    }
    else
    {
      board[0][columnNumber] = 1;
    }
  } while(board[0][columnNumber] == 0);
}

