#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE   0
#define ERROR 2
#define BUFFER_SIZE 2040



void printHelp();


int main (int argc, char * * argv)
{
  int i;
  int showHelp = FALSE;
  int invertMatch = FALSE;
  int lineNumbers = FALSE;
  int quiet = FALSE;

  const char * pattern = argv[argc - 1];

  if (argc == 1)    {
    fprintf(stderr, "error!\n");
    return ERROR;
  }
  
  for (i = 1; i < argc-1; i++)    {
    if (strcmp (argv[i],"--help") == 0)    showHelp = TRUE;
    else if (strcmp (argv[i],"--invert-match") == 0)    invertMatch = TRUE;
    else if (strcmp (argv[i],"-v") == 0)    invertMatch = TRUE;
    else if (strcmp (argv[i],"-n") == 0)    lineNumbers = TRUE;
    else if (strcmp (argv[i],"--line-number") == 0)    lineNumbers = TRUE;
    else if (strcmp (argv[i],"--quiet") == 0)    quiet = TRUE;
    else if (strcmp (argv[i],"-q") == 0)    quiet = TRUE;
    else   {
      fprintf(stderr,"error!\n");
      return ERROR;
    }

  }
  

  if (showHelp || strcmp (pattern, "--help") == 0)    {
    printHelp();
    return EXIT_SUCCESS;
  }
  


  char buffer[BUFFER_SIZE];
  int found = FALSE;
  int currLine = 0;
  
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)    {
    currLine++;
    int matches = strstr(buffer, pattern) != NULL;
    if ((matches && !invertMatch) || (!matches && invertMatch))    {
      found = TRUE;
      if (!quiet)    {
	if(lineNumbers)    {
	  printf("%d:", currLine);
	}
	printf("%s", buffer);
      }
    }
  }
  

  return found ? 0 : 1;

}



  
void printHelp()
{
  printf("Usage: grep-lite [OPTION]... PATTERN\n");
  printf("Search for PATTERN in standard input. PATTERN is a\n");
  printf("string. grep-lite will search standard input line by\n");
  printf("line, and (by default) print out those lines which\n");
  printf("contain pattern as a substring.\n");
  printf("\n");
  printf("  -v, --invert-match     print non-matching lines");
  printf("  -n, --line-number      print line number with output\n");
  printf("  -q, --quiet            suppress all output\n");
  printf("\n");
  printf("Exit status is 0 if any line is selected, 1 otherwise;\n");
  printf("if any error occurs, then the exit status is 2.\n");
}
