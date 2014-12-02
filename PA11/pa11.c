#include <stdio.h>
#include "answer11.h"
#include "treefun.h"

int main()
{
  
  FILE * fptr = fopen("inputs/07-description.bit-huff","rb");
  HuffNode * temp = HuffTree_readBinaryHeader(fptr);
  fclose(fptr);
  HuffNode_printPretty(stdout,temp);
  HuffNode_destroy(temp);
  
  return 0;
}