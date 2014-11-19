#include "answer10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  
  struct YelpDataBST * bst = create_business_bst("shortfilebus.tsv", "shortfilerev.tsv");
  
  char * name = malloc(sizeof(char) * 13);
  strcpy(name,"Ruby's Diner");
  
  struct Business * bus_node = get_business_reviews(bst, name, NULL, NULL);
  
  printf("\n\nName: %s\n",bus_node->name);
  int ind;
  int rev;
  for (ind = 0; ind < bus_node->num_locations;ind++)
  {
    printf("\n\nLocation[%d]: \nAddress: %s\nCity: %s\nState: %s\nZip: %s\n",ind,bus_node->locations[ind].address,bus_node->locations[ind].city,bus_node->locations[ind].state,bus_node->locations[ind].zip_code);   
    for (rev = 0; rev < bus_node->locations[ind].num_reviews;rev++)
    {
      printf("\nReview %d: %s\n\n",rev,bus_node->locations[ind].reviews[rev]); 
    }
  }
  printf("\n\n");
  destroy_business_bst(bst);
  destroy_business_result(bus_node);
  
  return 0;
}