# include <stdio.h>
# include <stdlib.h>

void change (int * a)
{
  *a = 5;
}

int main ( int argc , char * * argv )
{
  int a = 1;
  change (&a);
  printf("%d\n",a);
  return 1;
}
