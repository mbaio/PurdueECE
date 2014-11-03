#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer09.h"

int main()
{
  
  BusinessNode * tree = load_tree_from_file("shortfile.tsv");
  
  
//   BusinessNode * node1 = create_node("4.0","Lil Mikey's","2948 Star Pass");
//   BusinessNode * node2 = create_node("3.5","Mcdonalds","State Street");
//   BusinessNode * node3 = create_node("2.7","Burger King","Nelson");
//   BusinessNode * node4 = create_node("1.2","Charlstons","Cedar");
//   BusinessNode * node5 = create_node("3.0","Culvers","Route 30");
//   
//   BusinessNode * tree = NULL;
//   tree = tree_insert(node1,tree);
//   tree = tree_insert(node2,tree);
//   tree = tree_insert(node3,tree);
//   tree = tree_insert(node4,tree);
//   tree = tree_insert(node5,tree);
  
  print_tree(tree);
  
  
  
  return 0;
}
