#include "answer03.h"
#include <string.h>


char * strcat_ex(char ** dest, int * n, const char * src)
{
  size_t src_len = strlen (src); 
  size_t dest_len = *dest == NULL ? 0 : strlen (*dest);
  if (dest_len == 0 || ((src_len + dest_len + 1) >= *n))    {
    *n =  1 + 2 * (dest_len + src_len);
    char * buffer = malloc (*n * sizeof(char));
    *buffer = '\0';
    if (*dest != NULL)    {
      strcpy (buffer, *dest);
    }
    free (*dest);
    *dest = buffer;
  }
  strcat (*dest, src);
  return *dest;
  
}

char ** explode(const char * str, const char * delims, int * arrLen)
{
  // 1st calculate the # of strings we need
  *arrLen = 1;
  const char * pos = str;
  while (*pos != '\0')    {
    if (strchr (delims, *pos))    {
      (*arrLen)++;
      pos ++;
    }
  }

  // 2nd creat the array of strings
  char ** string_list = malloc (*arrLen * sizeof (char*));
  
  // 3rd split the string into substrings
  int i = 0;
  const char * start  = str;
  pos = str;
  while (*pos != '\0')    {
    if (strchr (delims, *pos))    {
      int len = pos - start;
      string_list[i] = malloc ((len + 1) * sizeof (char));
      memcpy (string_list [i], start, len * sizeof (char));
      string_list[i][len] = '\0';
      i ++;
      start = pos + 1;
    }
    pos ++;
  }
  
  // 4th copy the last string
  int len = pos - start;
  string_list[i] = malloc ((len + 1) * sizeof (char));
  memcpy (string_list[i], start, len * sizeof (char));
  string_list [i] [len] = '\0';
  return string_list;
}


char * implode(char * * strArr, int len, const char * glue)
{
  int i;
  char * newarray = NULL;

  for (i = 0; i < len - 1; i++)    {
    strcat_ex(&newarray, &len, strArr[i]);
    strcat_ex(&newarray, &len, glue);
  }
  strcat_ex(&newarray, &len, strArr[i]);
  return newarray;
}

int strcompare(const void *a, const void *b)
{
  const char **x = (const char **)a;
  const char **y = (const char **)b;
  return strcmp(*x,*y);
}

void sortStringArray (char * * arrString, int len)
{
  qsort(arrString, len, sizeof(char *), strcompare);
 return;
}

int charcompare(const void * a, const void * b)
{
  const char * x = (const char *) a;
  const char * y = (const char *) b;
  
  return *x - *y;
}

void sortStringCharacters(char * str)
{
  qsort(str,strlen(str),sizeof(char),charcompare);
  return;
}

void destroyStringArray(char * * strArr, int len)
{
  int i = 0;
  if(strArr == NULL)      return;
  for (i=0; i<len; i++)    {
    free(strArr[i]);
  }
  free(strArr);
  return;
}
