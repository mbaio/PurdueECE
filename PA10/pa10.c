#include "answer10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  
  struct YelpDataBST * bst = create_business_bst("shortfilebus.tsv", "shortfilerev2.tsv");
  destroy_business_bst(bst);
  
  
  return 0;
}