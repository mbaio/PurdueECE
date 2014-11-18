#include "answer10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp_names(char *,char *);

int main()
{
  
  struct YelpDataBST * bst = create_business_bst("shortfilebus2.tsv", "shortfilerev2.tsv");
  char * name = malloc(sizeof(char) * 13);
  strcpy(name,"Ruby's Diner");
  
  struct Business * bus_node = get_business_reviews(bst, name, NULL, NULL);
  
  return 0;
}