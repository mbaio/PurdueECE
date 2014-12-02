#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer11.h"

Huffnode * HuffNode_create(int value)
{
  Huffnode * temp = malloc(sizeof(HuffNode));
  if (temp == NULL)
    return NULL;
  temp -> left = NULL;
  temp -> right = NULL;
  temp -> value = value;
  return temp;
}

void HuffNode_destroy(HuffNode * tree);
{
   if (tree == NULL){
     free(tree);
     return;
   }
   HuffNode_destroy(tree -> left);
   HuffNode_destroy(tree -> right);
   free(tree);
}
