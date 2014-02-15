#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FAILURE 0
#define ERROR 2

void printHelp();
int catFile (const char *, FILE *);

int main(int argc, char * * argv)
{
  //check for no input
  if (argc == 1)    {
    catFile("-", stdout);
    return EXIT_SUCCESS;
  }
  
  //check for help
  int i;
  for (i = 1; i < argc; i++)    {
    if (strcmp(argv[i], "--help") == 0)    {
      printHelp();
      return EXIT_SUCCESS;
    }
  }
  
  for (i = 1; i < argc; i++)    {
    if (catFile(argv[i], stdout) == FAILURE)    {
      fprintf(stderr, "cat cannot open %s\n",argv[i]);
      return FAILURE;
    }
  }
  return EXIT_SUCCESS;
      
}

void printHelp()
{
  printf("Usage: cat-lite [--help] [FILE]...\n");
  printf("With no FILE, or when FILE is -, read standard input.\n");
  printf("\n");
  printf("Examples:\n");
  printf("  cat-lite README   Print the file README to standard output.\n");
  printf("  cat-lite f - g    Print f's contents, then standard input,\n");
  printf("                    then g's contents.\n");
  printf("  cat-lite          Copy standard input to standard output.\n");
  printf("\n");
}

int catFile (const char * filename, FILE * fout)
{
  FILE * fin;
  int isStdin = strcmp (filename, "-") == 0;
  if (isStdin)    fin = stdin;
  else   fin = fopen(filename,"r");
  
  if (fin == NULL)    return FAILURE;
  

  int ch;
  while ((ch = fgetc(fin)) != EOF)    {
    fputc (ch, fout);
  }

  if (!isStdin)    fclose(fin);
  return TRUE;
}
