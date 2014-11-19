#include "answer10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  
  struct YelpDataBST * bst = create_business_bst("shortfilebus.tsv", "shortfilerev.tsv");
  //char * name = malloc(sizeof(char) * 13);
  //strcpy(name,"Ruby's Diner");
//   struct Business * bus_node = get_business_reviews(bst, name, NULL, NULL);
   destroy_business_bst(bst);
//   destroy_business_result(bus_node);
  return 0;
}