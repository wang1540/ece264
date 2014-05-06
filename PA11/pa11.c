
#include "answer11.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main (int argc , char ** argv)
{
  if (argc < 3)   return EXIT_FAILURE;

  char * stage = argv [1];
  char * state = argv [2];


  if (strcmp(stage,"1")==0)   {
    if (argc != 4)   return EXIT_FAILURE;
    char * movelist = argv[3];
    if (!isValidState(state))    return EXIT_FAILURE;
    if (!isValidMoveList(movelist))    return EXIT_FAILURE;
    processMoveList (state, movelist);
    return EXIT_SUCCESS;
  }



  if (strcmp(stage,"2")==0)   {
    if (argc != 4)   return EXIT_FAILURE;
    int n_moves = atoi (argv[3]); // number of moves
    if ((n_moves < 0)||(n_moves > 9))    return EXIT_FAILURE;

    if (!isValidState(state))    return EXIT_FAILURE;

   
    MoveTree * root = generateAll(state, n_moves);
    MoveTree_print (root);
    //printf("\n");
    MoveTree_destroy(root);
    return EXIT_SUCCESS;
  }


  if (strcmp(stage,"3") == 0)   {


    char * solution = solve (state);
    if (solution != NULL)  {
      printf("%s\n", solution);
    }
    //printf("\n");
    
    return EXIT_SUCCESS;

  }

  return EXIT_FAILURE;
}
