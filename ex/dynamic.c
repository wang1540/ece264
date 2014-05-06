# include <stdlib.h>
# include <stdio.h>
# include <time.h>

typedef struct listnode
{
  struct listnode * next ;
  int value;
} Node;

Node * List_reverse ( Node * head )
{
  if (head == NULL)
    { return NULL;}
  Node * revhead = NULL;
  while (head != NULL)
    {
      head -> next = revhead;
      revhead = head;
      head = head -> next;
    }
  return revhead;
}

int main ( int argc , char * argv [])
{
  srand(time(NULL));
  Node * head = NULL;
  head = List_reverse(head);
  return 1;
}
