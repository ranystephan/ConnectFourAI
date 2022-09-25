#include <stdio.h>  /* needed to call prinf() and scanf() */
#include <stdlib.h> /* needed to call srand() and rand() */
#include <time.h> /* needed to call time */
//Display the initial game board
void boardDisplay() {

  printf("---------------------\n");

  int board[6][7] = {
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0}
  };

  int row, column = 0;

  for (row=0; row < 6; row++){
    for(column = 0; column < 7; column++){
      printf("|%d|", board[row][column]);
    }
    printf("\n");
  }

  printf("---------------------\n");
}

void askPlayerNames(){
// Ask the names of the players
  /* char namePlayer1[20];
  char namePlayer2[20];
  printf("Please Enter Your Name Player1: ");
  scanf("%s", namePlayer1);
  printf("\n Please Enter Your Name Player2: ");
  scanf("%s", namePlayer2);
  printf("Welcome %s \n", namePlayer1);
  printf("Welcome %s \n", namePlayer2);

  char playerNames[2][20] = {*namePlayer1, *namePlayer2}; */

}

void tossCoin(char **playerNames){
  srand(time(NULL));
  int headsOrTails = rand() % 2; 

  if (headsOrTails == 1){
    printf("%s, the coin chose you! \n You may start playing!\n", playerNames[0]);
  }
}

int main(){
// Ask the names of the players
  char namePlayer1[20];
  char namePlayer2[20];
  printf("Please Enter Your Name Player1: ");
  scanf("%s", namePlayer1);
  printf("\n Please Enter Your Name Player2: ");
  scanf("%s", namePlayer2);
  printf("Welcome %s \n", namePlayer1);
  printf("Welcome %s \n", namePlayer2);

  char *playerNames[2] = {namePlayer1, namePlayer2};
  askPlayerNames();
  boardDisplay();
  tossCoin(playerNames);

  }
