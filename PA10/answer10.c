#include "answer10.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFLEN 2500


typedef struct ListNode_st
{
    int id;
    char * address;
    char * state;
    char * zip;
    char * city;
    struct ListNode_st * next;
} List;

typedef struct tree_node_t
{
  List * location_list;
  char * name;
  long int offset;
  int id;
  struct tree_node_t * left;
  struct tree_node_t * right;
} tree_node;

struct YelpDataBST
{
  tree_node * head_name;
  tree_node * head_id;
};

List * List_createNode(int, char *, char *, char *, char *);
void List_destroy(List *);
int List_length(List *);
List * List_push(List *,int,char *,char *,char *,char *);
char ** explode(const char *, const char *,int *);
tree_node * create_node(List *,char *, long int,int);
tree_node * tree_insert_name(tree_node *, tree_node *);
tree_node * tree_insert_id(tree_node *,tree_node *);
void destroy_tree(tree_node *);
void print_tree_name(tree_node *);
void print_node_name(tree_node *);
void print_tree_id(tree_node *);
void print_node_id(tree_node *);
void print_list(List *);
void destroyStringArray(char **, int);

List * List_createNode(int id, char * address, char * state, char * zip, char * city)
{
    List * temp_list = malloc(sizeof(List));
    temp_list -> id = id;
    temp_list -> address = strdup(address);
    temp_list -> state = strdup(state);
    temp_list -> zip = strdup(zip);
    temp_list -> city = strdup(city);
    temp_list -> next = NULL;
    return temp_list;
}

void List_destroy(List * list) // code from Prof Liu Book page 305
{
    while (list != NULL)
    {
      List * temp_list = list -> next;
      free (list -> address);
      free (list -> state);
      free (list -> zip);
      free (list -> city);
      free (list);
      list = temp_list;
    }
}

int List_length(List * list)
{
  int len_list = 0;
  List * temp_list = list;
  while (temp_list != NULL)
  {
    len_list++;
    temp_list = temp_list -> next;
  }

  return len_list;
}

List * List_push(List * head, int id, char * address, char * state, char * zip, char * city)
{
        List * newhead = List_createNode(id, address, state, zip, city);
        newhead->next = head;
        return newhead;
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

void destroyStringArray(char ** strArr, int len)
{
  int ind = 0;

  if (strArr == NULL)
  {
  return;
  }

  for (ind = 0; ind < len; ind++)
  {
    free(strArr[ind]);
  }

  free(strArr);
  return;

}

tree_node * create_node(List * location_list, char * name, long int offset, int id)
{
  tree_node * temp_node = malloc(sizeof(tree_node));
  temp_node -> location_list = location_list;
  temp_node -> name = strdup(name);
  temp_node -> offset = offset;
  temp_node -> id = id;
  temp_node -> left = NULL;
  temp_node -> right = NULL;
  return temp_node;
}

tree_node * tree_insert_name(tree_node * node, tree_node * root)
{
  if (root == NULL)
  {
    return node;
  }
  
  if (strcmp(node -> name,root -> name) < 0)
  {
    root -> left = tree_insert_name(node,root -> left);
  }
  else if (strcmp(node -> name,root -> name) > 0)
  {
    root -> right = tree_insert_name(node,root -> right);
  }
  else
  {
    root->location_list = List_push(root -> location_list, node->location_list->id, node->location_list->address, node->location_list->state, node->location_list->zip, node 
    -> location_list-> city);
  }
  
  return root;
}

tree_node * tree_insert_id(tree_node * node, tree_node * root)
{
  if (root == NULL)
  {
    return node;
  }
  if (node == NULL)
  {
    return root;
  }
  
  if (node -> id < root -> id)
  {
    root -> left = tree_insert_id(node,root -> left);
  }
  else if  (node -> id > root -> id)
  {
    root -> right = tree_insert_id(node,root -> right);
  }
  
  return root;
}

void destroy_tree(tree_node * root)
{
  if (root == NULL)
  {
    free(root);
    return;
  }  
  destroy_tree(root -> left);
  destroy_tree(root -> right);
  List_destroy(root -> location_list);
  free(root -> name);
  free(root); 
}

void print_tree_name(tree_node * tree)
{
  if (tree == NULL)
  {
    return;
  }
  print_node_name(tree);
  print_tree_name(tree -> left);
  print_tree_name(tree -> right);
}

void print_node_name(tree_node * node)
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
  equals[length_str + 4] = '\0';
  printf("%s\n",equals);
  print_list((List *)node -> location_list);
  printf("Address: %s\n\n\n",node -> name);
  free(equals);
  return;
}

void print_list(List * list)
{
  
  List * temp_list = list;
  
  printf("\n");
  while(temp_list != NULL)
  {
    printf("List: Id: %d    Address: %s    State: %s\nZip: %s    City: %s\n",temp_list -> id,temp_list -> address,temp_list -> state,temp_list -> zip,temp_list -> city);
    temp_list = temp_list -> next;  
  }
  
  
}

void print_tree_id(tree_node * tree)
{
  if (tree == NULL)
  {
    return;
  }
  print_node_id(tree);
  print_tree_id(tree -> left);
  print_tree_id(tree -> right);
}

void print_node_id(tree_node * node)
{
  if (node == NULL)
  {
    printf("Node is NULL\n");
    return;
  }
  printf("ID: %d\nOffset: %ld\n\n\n",node -> id,node -> offset);
  return;
}

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  struct YelpDataBST * tempBST = malloc(sizeof(struct YelpDataBST *));
  if (tempBST == NULL)
  {
    return NULL;
  }
  tree_node * temp_tree = NULL;
  tree_node * temp_id_tree = NULL;
  int file_line_length = 0;
  int id_num;
  char * line = malloc(BUFLEN * sizeof(char)); // line of data read from file
  char ** line_elements; // array of strings from line
  long int offset;
  if (line == NULL)
  {
    fprintf(stderr,"line not initialized!\n");
    free(line);
    return NULL;
  }
  
  FILE * fptr = fopen(businesses_path,"r"); // open businesses to make tree
  if (fptr == NULL)
  {
    fprintf(stderr,"Could not open file!\n");
    free(line);
    return NULL;
  }
  while (fgets(line, BUFLEN, fptr))
  {
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);   
    id_num = atoi(line_elements[0]);
    List * list_node = List_createNode(id_num,line_elements[2],line_elements[4],line_elements[5],line_elements[3]);
    tree_node * temp_node = create_node(list_node,line_elements[1],(long int)NULL,id_num);
    temp_tree = tree_insert_name(temp_node,temp_tree);   
    destroyStringArray(line_elements, file_line_length);
  }  
  fclose(fptr);
  print_tree_name(temp_tree);    
  
  fptr = fopen(reviews_path,"r");
  if (fptr == NULL)
  {
    fprintf(stderr,"Could not open file!\n");
    free(line);
    return NULL;
  }
/*  
  while (fgets(line,BUFLEN,fptr))
  {
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);
    id_num = atoi(line_elements[0]);
    offset = ftell(fptr);
    printf("\nID: %d  Offset: %ld",id_num,offset);
    tree_node * temp_node = create_node((List *)NULL,(char *)NULL,offset,id_num);
    temp_id_tree = tree_insert_id(temp_node,temp_id_tree);
    destroyStringArray(line_elements,file_line_length);
  }
  fclose(fptr);*/
  free(line);
  
  tempBST -> head_name = temp_tree;
  //tempBST -> head_id = temp_id_tree;
  
  return tempBST;

}


struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
  struct Business * temp_bus = malloc(sizeof(struct Business *));
  temp_bus = NULL;
  return temp_bus;
}

void destroy_business_bst(struct YelpDataBST* bst)
{
  destroy_tree(bst->head_name);
  //destroy_tree(bst->head_id);
  free(bst);
}

void destroy_business_result(struct Business* b)
{
  
  
  
}
                                   
                               