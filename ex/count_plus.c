# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAXLENGTH 5

int printPartition ( int * arr , int len )
{
  int ind ;
  printf ("= ");
  for ( ind = 0; ind < len - 1; ind ++)
  {
    printf ("% d + " , arr [ ind ]);
  }
  printf ("% d \n" , arr [ len - 1]);
  return len - 1;
}

void partitionHelper ( int value , int * arr , int ind , int * plus)
{
  if ( value == 0)
  {
    *plus += printPartition ( arr , ind );
    return;/////
  }
  int nextVal ;
  for ( nextVal = 1; nextVal <= value ; nextVal ++)
  {
    arr [ ind ] = nextVal ;
    partitionHelper ( value - nextVal , arr , ind + 1, plus);
  }
}


void partition ( int value )
{
  int count = 0;
  int plus = 0;
  int arr [ MAXLENGTH ];
  partitionHelper ( value , arr , 0, &plus);
  printf ("\"+\" is used % d times to partition % d \n" , plus , value );
}


int main ( int argc , char * * argv )
{
  int val ;
  for ( val = 1; val <= MAXLENGTH ; val ++)
  {
    partition ( val );
  }
  return EXIT_SUCCESS ;
}
