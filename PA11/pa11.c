#include <stdio.h>
#include "answer11.h"
#include "treefun.h"

int main()
{
  
  FILE * fptr = fopen("inputs/01-tibbs.txt-huff","r");
  HuffNode * temp = HuffTree_readTextHeader(fptr);
  fclose(fptr);
  HuffNode_printPretty(stdout,temp);
  return 0;
}