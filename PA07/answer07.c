#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "answer07.h"

List *List_createNode (const char * str)
{
  List *node = malloc(sizeof(List));
  node -> str = strdup(str);
  node -> next = NULL;
  return node;
}

void List_destroy (List * list)
{
  //Base Case
  if (list == NULL)      return;
  
  //Recursive
  List_destroy (list -> next);
  free (list -> str);
  free (list);
}

int List_length (List * list)
{
  if(list == NULL)     return 0;
  return 1 + List_length (list -> next);
}

List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  int length = List_length(list);
  
  //Base case: do we have a single length or empty list?
  if (length <=1)     return list;
  
  //Recursive case: keep splitting into two part (equal size)
  // sort the list, when done, merge the lists
  
  //split divide phase
  int half_length = length / 2;
  List * lhs = list;
  List * lhs_tail = list;
  while (--half_length > 0)     {
    lhs_tail = lhs_tail -> next;
  }
  List * rhs = lhs_tail -> next;
  lhs_tail -> next = NULL;/////////////////////////////////////////////
  
  //sort the two parts
  lhs = List_sort(lhs, compar);
  rhs = List_sort(rhs, compar);
  
  //merge conquer phase
  return List_merge (lhs, rhs, compar);
}

List * List_merge(List * lhs, 
		  List * rhs, 
		  int (*compar)(const char *, const char*))
{
  //special case
  if (lhs == NULL)     return rhs;
  if (rhs == NULL)     return lhs;
  
  //normal case
  List * head = NULL;
  List * tail = NULL;
  
  while (lhs != NULL && rhs != NULL)     {
    int cmp = compar (lhs -> str, rhs -> str);
    if (cmp <= 0)     {
      
      //left is smaller, add to merge list
      if(tail == NULL)     {
	head = lhs;
	tail = lhs;
      }
      else  {
	tail -> next = lhs;
	tail = lhs;
      }
      lhs = lhs -> next;
      tail -> next = NULL;
    }
    
    
    //right is smaller
    else    {
      if (tail == NULL)     {
	head = rhs;
	tail = rhs;
      }
      else  {
	tail -> next = rhs;
	tail = rhs;
      }
      rhs = rhs -> next;
      tail -> next = NULL;
    }
  }
    
  //tag on the remainder
  tail -> next = (lhs == NULL)? rhs: lhs;
  return head;
}
  
  
  
