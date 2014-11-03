#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer09.h"

char ** explode(const char *str, const char *delims, int * arrLen);

BusinessNode * create_node(char * stars, char * name, char * address)
{
  BusinessNode * temp_node = malloc(sizeof(BusinessNode));
  temp_node -> stars = stars;
  temp_node -> name = name;
  temp_node -> address = address;
  temp_node -> left = NULL;
  temp_node -> right = NULL;
  return temp_node;
}

BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
  if (root == NULL)
  {
    return node;
  }
  
  if (strcmp(node -> name,root -> name) <= 0)
  {
    root -> left = tree_insert(node,root -> left);
  }
  else
  {
    root -> right = tree_insert(node,root -> right);
  }
  
  return root;
}

void print_node(BusinessNode * node)
{
  if (node == NULL)
  {
    printf("Node is NULL\n");
    return;
  }
  printf("--%s--\n",node -> name);
  int length_str = strlen(node -> name);
  char * equals = malloc((length_str + 5) * sizeof(char));
  int ind;
  for (ind = 0;ind < length_str + 4;ind++)
  {
    equals[ind] = '=';
  }
  equals[length_str + 5] = '\0';
  printf("%s\n",equals);
  printf("Stars: %s\nAddress: %s\n\n\n",node -> stars,node -> address);
  free(equals);
  return;
}

void print_tree(BusinessNode * tree)
{
  if (tree == NULL)
  {
    return;
  }
  print_node(tree);
  print_tree(tree -> left);
  print_tree(tree -> right);
}

char ** explode(const char *str, const char *delims, int * arrLen)
{
  
  char * element =(char *) str;
  int length_return_array = 0;
  while ( *element != '\0')
  {  
  	if (strchr(delims, *element))
	{
	  length_return_array++;;
	}

	element++;
  }
  *arrLen = length_return_array + 1;
  
  char ** dest = malloc((*arrLen + 1) * sizeof(char *));

  int ind = 0; // which word I will be accessing
  element = (char *)str; // set back to the start
  char * start = (char *)str; // where the search will start
  int length_word; // how many characters the word is without delimiter

  while (ind < *arrLen)
  {
	if (strchr(delims, *element))
	{
	  length_word =  element - start;
	  dest[ind] = malloc((length_word + 1) * sizeof(char)); // length + 1 because of delimitter
	  memcpy(dest[ind],start, (length_word) * sizeof(char));
	  dest[ind][length_word] = '\0'; // to finish that word
	 
	 
      ind++; //go to the next word
	  start = start + length_word + 1;
	  element = start - 1;
	 
	}

	element++;
  }

  return dest;
}

BusinessNode * load_tree_from_file(char * filename)
{
  BusinessNode * temp_tree = NULL;
  int file_line_length = 0;
  char * line = malloc(250 * sizeof(char));
  
  char ** line_elements;
  
  
  if (line == NULL)
  {
    fprintf(stderr,"line not initialized!\n");
    return NULL;
  }
  

  FILE * fptr = fopen(filename,"r");
  if (fptr == NULL)
  {
    fprintf(stderr,"Could not open file!\n");
    return NULL;
  }
  while (fgets(line, 250, fptr))
  {
    line_elements = explode(line,"\t",&file_line_length);
    BusinessNode * temp_node = create_node(line_elements[0],line_elements[1],line_elements[2]);
    temp_tree = tree_insert(temp_node,temp_tree);
    free(line_elements[2]);
    free(line_elements[1]);
    free(line_elements[0]);
    free(line_elements);
  }
    free(line);
  
  return temp_tree;  
}

void destroy_tree(BusinessNode * root)
{
  if (root == NULL)
  {
    free(root);
    return;
  }
  destroy_tree(root -> left);
  destroy_tree(root -> right);
  free(root -> stars);
  free(root -> name);
  free(root -> address);
  free(root); 
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
  BusinessNode * temp = root;
  
  if (root == NULL)
  {
    return NULL;
  }
  printf("Current name: %s\n",root -> name);
  if (strcmp(root -> name,name) == 0)
  {
    return root;
  }
  if (strcmp(root -> name,name) > 0)
  {
    temp = tree_search_name(name,root -> left);
  }
  else
  {
    temp = tree_search_name(name,root -> right);
  }
  return temp;
}
  
  



  