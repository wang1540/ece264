
#include "answer11.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Prints the puzzle-state as a 2d matrix. 
 * This function is supplied to you.
 */
void printPuzzle(const char * state)
{
    int row, col;
    for(row = 0; row < SIDELENGTH; ++row) {
	for(col = 0; col < SIDELENGTH; ++col) {
	    printf(" %c", state[row*SIDELENGTH + col]);
	}
	printf("\n");
    }
}

/**
 * Print the moves in a move-tree.
 * This function is supplied to you.
 */
void MoveTree_print(MoveTree * node)
{
    if(node == NULL)
	return;
    printf("%s\n", node -> state);
    MoveTree_print(node -> left);
    MoveTree_print(node -> right);
}

int charcmp (const void *a, const void *b)
{
  return *((char *) a) - *((char *) b);
}

int isValidState(const char * state)
{
  if (strlen(state) != 16)    return FALSE;
  char buffer[17];
  strcpy(buffer,state);
  qsort(buffer,16,sizeof(char),charcmp);
  const char * valid = "-123456789ABCDEF";
  if (strcmp(buffer,valid) == 0) return TRUE;
  return FALSE;
}

int isValidMoveList(const char * movelist)
{
  int ind;
  const char * valid = "RLUD";
  int len = strlen (movelist);
  for (ind = 0; ind < len; ind++)    {
    if (strchr(valid, movelist[ind]) == NULL)    return FALSE;
  }
  return TRUE;
}

void Swap (char * a, char * b)
{
  char temp = * a;
  * a = * b;
  * b = temp;
}

int move(char * state, char m)
{
  int position;
  for (position=0; position < SIDELENGTH * SIDELENGTH; position++)   {
    if (state[position] == '-') break;
  }
  int row = position / SIDELENGTH;
  int col = position % SIDELENGTH;

  int new_row = row;
  int new_col = col;

  switch (m)  {
  case 'U': new_row = row - 1;    break;
  case 'D': new_row = row + 1;    break;
  case 'L': new_col = col - 1;    break;
  case 'R': new_col = col + 1;    break;
  }

  if( (new_row < 0) ||( new_row >= SIDELENGTH) || (new_col < 0) || (new_col >= SIDELENGTH) )   {
    return FALSE;
  }

  int target_position = new_row * SIDELENGTH + new_col;

  Swap((state + position), (state + target_position));////////////////////

  return TRUE;
}



void processMoveList(char * state, const char * movelist)
{
  int ind;
  int len = strlen(movelist);
  for (ind = 0; ind < len; ind ++)   {
    if ( move (state, movelist[ind]) == FALSE)   {
      printf("I\n");
      return;
    }
  }
  printf ("%s\n", state);
}


MoveTree * MoveTree_create(const char * state, const char * moves)
{
  MoveTree * node = malloc (sizeof(MoveTree));
  node -> state = strdup (state);
  node -> moves = strdup (moves);
  node -> left = NULL;
  node -> right = NULL;

  return node;
}

void MoveTree_destroy(MoveTree * node)
{
  if (node == NULL)  return;
  MoveTree_destroy (node->left);
  MoveTree_destroy (node->right);

  free(node -> state);
  free(node -> moves);

  free(node);
}

MoveTree * MoveTree_insert(MoveTree * node, 
			   const char * state, 
			   const char * moves)
{
  if (node == NULL)    return MoveTree_create (state, moves);
  int cmp = strcmp (state, node->state);

  if (cmp == 0)   {
    if (strlen(moves) < strlen(node -> moves))  {
      free(node -> moves);
      node->moves = strdup (moves);
    }
  }
  else if (cmp < 0)  {
    node ->left = MoveTree_insert (node->left, state, moves);
  }

  else if (cmp > 0)  {
    node ->right = MoveTree_insert (node->right, state, moves);
  }

  return node;
}

MoveTree * MoveTree_find(MoveTree * node, const char * state)
{
  if (node == NULL)   return NULL;
  int cmp = strcmp (state, node -> state);
  if (cmp == 0)   return node;
  else if (cmp < 0)    return MoveTree_find(node -> left, state);
  return MoveTree_find(node -> right, state);
}


void generateAll_Helper (MoveTree * root, int n_moves, const char * state,
			 char * movelist, int ind)
{
  if (ind == n_moves)    return;
  const char * validmoves = "UDLR";
  int i;
  for (i = 0; i < strlen(validmoves); i++)    {
    char m = validmoves [i];
    char * dup_state = strdup (state);
    int result = move(dup_state, m);
    if (result == TRUE)   {
      movelist [ind] = m;
      movelist [ind + 1] = '\0';
      MoveTree_insert (root, dup_state, movelist);
      generateAll_Helper (root, n_moves, dup_state, movelist, ind + 1);
    }
    free (dup_state);
  }
}
 

MoveTree * generateAll(char * state, int n_moves)
{
  char * movelist = malloc (sizeof(char) * (n_moves + 1));
  movelist [0] = '\0';
  MoveTree * root = MoveTree_create (state, movelist);
  generateAll_Helper (root, n_moves, state, movelist, 0);
  free(movelist);
  return root;  
}


char * solve(char * state)
{
  MoveTree * tree = generateAll (state, MAX_SEARCH_DEPTH);
  MoveTree * answer = MoveTree_find (tree, FINAL_STATE);
  char * move_now = NULL;
  if (answer != NULL)  {
    move_now = strdup (answer -> moves);
  }

  MoveTree_destroy (tree);
  //MoveTree_destroy (answer);
  return move_now;
}

