#include "answer10.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  
  struct YelpDataBST * bst = create_business_bst("shortfilebus.tsv", "shortfilerev.tsv");
  
  
  
  char * name = malloc(sizeof(char) * 13);
  strcpy(name,"RUBy's Diner");
  char * zip = malloc(sizeof(char) * 6);
  strcpy(zip,"85226");
  char * state = malloc(sizeof(char) * 3);
  strcpy(state,"AZ");
  
  struct Business * bus_node = get_business_reviews(bst, name, state, zip);
  int ind;
  int rev;
  if (bus_node != NULL && bst != NULL)
  { 
    printf("\n\nName: %s\nNum locations: %d",bus_node->name,bus_node -> num_locations);
  for (ind = 0; ind < bus_node->num_locations;ind++)
  {
    printf("\n\nLocation[%d]: \nAddress: %s\nCity: %s\nState: %s\nZip: %s\nNum reviews = %d\n",ind,bus_node->locations[ind].address,bus_node->locations[ind].city,bus_node->locations[ind].state,bus_node->locations[ind].zip_code,bus_node->locations[ind].num_reviews);   
    for (rev = 0; rev < bus_node->locations[ind].num_reviews;rev++)
    {
      printf("\nReview %d: %s\n\n",rev,bus_node->locations[ind].reviews[rev]); 
    }
  }
  printf("\n\n");
  }
  
  
  
  
  
  destroy_business_bst(bst);
  destroy_business_result(bus_node);
  free(name);
  free(zip);
  free(state);
  return 0;
}