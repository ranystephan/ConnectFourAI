#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h> /* needed to call time */


char board[6][7]; //board as a global variable

char namePlayer1[20];
char namePlayer2[20];

int columnHeight[7] = {5,5,5,5,5,5,5};


void resetBoard();
void displayBoard();
void tossCoin();
void player1Move();
void player2Move();
char checkWinner(char);
int checkFreeSpaces();
void askPlayerNames();
void checkVeritcal();
void checkHorizontal();


int main()
{
  char winner = ' ';

  resetBoard();
  askPlayerNames();
  tossCoin(namePlayer1, namePlayer2);


  while (winner == ' ' && checkFreeSpaces() != 0 )
    {
      displayBoard();
      player1Move();
      displayBoard();
      player2Move();
      winner = checkWinner(winner); //error with comparison pointer and integer in checkHorizontal and checkVertical
    }
  printf("Congratulations, %c, you won!", winner);

}

char checkWinner(char winner)
{
  if (checkHorizontal != ' ')
  {
    return checkHorizontal;
  }
  else if (checkVertical != ' ')
  {
    return checkVertical;
  }
}

char checkHorizontal(char winner)
{
  for (int row = 0; row <= 5; row++)
  {
    for (int col = 0; col <= 3; col++)
    {
      if (board[row][col] == 1 && board[row][col + 1] == 1 && board[row][col + 2] == 1 && board[row][col + 3] == 1)
          {
            winner = '1';
            return winner;
          }
      else if (board[row][col] == 2 && board[row][col + 1] == 2 && board[row][col + 2] == 2 && board[row][col + 3] == 2)
          {
            winner = '2';
            return winner;
          }
      else
          {
            return ' ';
          }
      
    }
  }
}


char checkVertical(char winner) //error here
{
  for (int col = 0; col <= 6; col++)
  {
    for (int row = 0; row <= 2; row++)
    {
          if (board[row][col] == 1 && board[row + 1][col] == 1 && board[row + 2][col] == 1 && board[row + 3][col] == 1)
          {
            winner = '1';
            return winner;
          }
      else if (board[row][col] == 2 && board[row + 1][col] == 2 && board[row + 2][col] == 2 && board[row + 3][col] == 2)
          {
            winner = '2';
            return winner;
          }
      else
          {
            return ' ';
          }
      
    }
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



void player1Move()
{
  int columnNumber;

  printf("%s, your move...", namePlayer1);
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
      board[columnHeight[columnNumber]][columnNumber] = 1;
      columnHeight[columnNumber]--;
      break;

    }
  } while(board[0][columnNumber] == 0);
}

void player2Move()
{

  printf("%s, your move...", namePlayer2);
  int columnNumber;
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
  } while(board[0][columnNumber] == 0);
}
