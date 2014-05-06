# include <stdio.h>
# include <stdlib.h>
# include <string.h>
typedef struct
{
  int ID ;
  char * name ;
} Student ;


Student * Student_construct ( int i , char * n )
{
  Student * st = malloc ( sizeof ( Student ));
  st -> ID = i ;
  st -> name = n ;
  return st ;
}


void Student_print ( Student * st )
{
  printf (" Student : ID = %d , name = % s \n" , st -> ID , st -> name );
}


void Student_free ( Student * st )
{
  free ( st );
}
# define NUM_STUDENT 4


int main ( int argc , char * * argv )
{
  int id [ NUM_STUDENT ] = {264 , 2013 , 1024 , 913};
  char * name [ NUM_STUDENT ] = {" Amy " , " Bob " , " Cathy " , " David "};
  int ind ;
  Student ** st ; // array of Student pointers///////////////////double *
  st = malloc ( sizeof ( Student ) * NUM_STUDENT );
  for ( ind = 0; ind < NUM_STUDENT ; ind ++)
    {
      int currid = id [ ind ];
      char * currnam = name [ ind ];
      st [ ind ] = Student_construct ( currid , currnam );
    }
  for ( ind = 0; ind < NUM_STUDENT ; ind ++)
    {
      Student_print ( st [ ind ]);
    }
  for ( ind = 0; ind < NUM_STUDENT ; ind ++)
    {
      Student_free ( st [ ind ]);
    }
  return EXIT_SUCCESS ;
}
