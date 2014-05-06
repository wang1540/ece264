# include <stdio.h>
# include <stdlib.h>

# include "answer09.h"
# include "treefun.h"

size_t size (HuffNode * tree)
{
  if (tree == NULL)    return 0;
  size_t count = 0;
  size (tree -> left);
  count ++;
  size (tree -> right);
  count ++;
  return count;
}


int main (int argc, char ** argv)
{
  if (argc != 2)    return 0;
  FILE * f = fopen (argv[1], "r");
  HuffNode * tree = HuffTree_readTextHeader (f);
  HuffNode_print (stdout, tree);
  size_t length = size (tree);
  unsigned char s = Huffman_applyTree (f, tree, &length);
  Huff_destroy (tree);
  fclose(f);
  return SUCCESS;
}

