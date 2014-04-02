#include <stdlib.h>
#include <stdio.h>

#include "answer08.h"




SparseNode * SparseNode_create(int index, int value)
{
  SparseNode * node = malloc(sizeof(SparseNode));
  node -> index = index;
  node -> value = value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}



SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if (array == NULL)    return  SparseNode_create (index, value);
  if (value == 0)       return array;
  if (array -> index == index)    {
    array -> value = value;
  }
  else if (array -> index > index)    {
    array -> left = SparseArray_insert (array->left, index, value);
  }
  else if (array -> index < index)    {
    array -> right = SparseArray_insert (array->right, index, value);
  }
  return array;
}

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
  int i;
  SparseNode * array = NULL; 
  if (indices == NULL)     return NULL;

  for (i = 0; i < length; i++)     {
    if (values == 0)     continue;
    array = SparseArray_insert(array, indices[i], values[i]);
  }

  return array;
}


void SparseArray_destroy(SparseNode * array)
{
  if (array == NULL)     return;
  SparseArray_destroy (array -> left);
  SparseArray_destroy (array -> right);
  free (array);
}

int SparseArray_getMin(SparseNode * array)
{
  if (array == NULL)     return -1;
  
  if (array -> left == NULL)      return (array -> index);
  
  return SparseArray_getMin (array -> left);
}

int SparseArray_getMax(SparseNode * array)
{
  if (array == NULL)     return -1;
  
  if (array -> right == NULL)      return (array -> index);
  
  return SparseArray_getMax (array -> right);
}

SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
  if (array == NULL)     return NULL;
  if (array -> index == index)      return array;
  if (array -> index > index)     return SparseArray_getNode (array -> left, index);
  else     return SparseArray_getNode (array -> right, index);
}


SparseNode * SparseArray_remove(SparseNode * array, int index)
{
  if (array == NULL)     return NULL;

  if (array -> index > index)     {
    array -> left = SparseArray_remove (array->left, index);
    return array;
  }
  if (array -> index < index)     {
    array -> right = SparseArray_remove (array->right, index);
    return array;
  }

  //case 1, no child
  if ((array-> right == NULL) && (array -> left == NULL))    {
    free (array);
    return NULL;
  }

  //case 2, one child
  if (array -> left == NULL)     {
    SparseNode * rc = array -> right;
    free (array);
    return rc;
  }

  if (array -> right == NULL)     {
    SparseNode * lc = array -> left;
    free (array);
    return lc;
  }

  //case 3: 2 children
  SparseNode * su = array -> right;
  while ((su -> left) != NULL)     {
    su = su -> left;
  }

  array -> index = su -> index;
  array -> value = su -> value;
  su -> index = index;
  
  array -> right = SparseArray_remove (array -> right, index);

  return array;
}

SparseNode * SparseArray_copy(SparseNode * array)
{
  SparseNode * new = NULL;
  if (array == NULL)      return NULL;
  new = SparseNode_create(array -> index, array -> value);
  
  if ((array -> left == NULL) && (array -> right == NULL))    {
    return new;
  }

  if (array -> left != NULL)     {
    new -> left = SparseArray_copy (array -> left);
  }

  if (array -> right != NULL)     {
    new -> right = SparseArray_copy (array -> right);
  }

  return new;
}

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  SparseNode * new = NULL;
  if (array_1 == NULL)      return NULL;

  new = SparseArray_copy (array_1);
  
  //base
  if ((array_2 -> left == NULL) && (array_2-> right == NULL))   {
    return NULL;
  }

  //recursive

  SparseArray_merge (new -> left, array_2 -> left);
  SparseArray_merge (new -> right, array_2 -> right);


  if (new->value == 0)      {
    new = SparseArray_remove(new, new -> index);
  }

  if (new->index == array_2->index)      {
    if ((array_2 -> value + new -> value) == 0)    {
      new = SparseArray_remove (new, new->index);
    }
    new -> value = array_2 -> value + new -> value;
  }

  else       new = SparseArray_insert (new, array_2 -> index, array_2 -> value);

  return new;
}


