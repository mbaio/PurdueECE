#include "answer10.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
  char * bus_file;
  char * rev_file;
};
int comp_names(char *,char *);
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
tree_node * tree_search_name(tree_node *,char *);
tree_node * tree_search_id(tree_node *, int);
List * search_params(List *,char *,char *);
struct Review * find_rev(tree_node *,int,char *,uint32_t *);


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

tree_node * create_node(List * location_list1, char * name1, long int offset1, int id1)
{
  tree_node * temp_node = malloc(sizeof(tree_node));
  if (name1 != NULL)
  {
    temp_node -> location_list = location_list1;
    temp_node -> name = strdup(name1);
  }
  else
  {
    temp_node -> location_list = NULL;
    temp_node -> name = NULL;
  }
  temp_node -> offset = offset1;
  temp_node -> id = id1;
    

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
  else
  {
    List_destroy(node->location_list);
    free(node->name);
    free(node);
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
  struct YelpDataBST * tempBST = malloc(sizeof(struct YelpDataBST));
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
    tree_node * temp_node = create_node(list_node,line_elements[1],-1,id_num);
    temp_tree = tree_insert_name(temp_node,temp_tree);   
    destroyStringArray(line_elements, file_line_length);
  }  
  fclose(fptr);
  
  fptr = fopen(reviews_path,"r");
  if (fptr == NULL)
  {
    fprintf(stderr,"Could not open file!\n");
    free(line);
    return NULL;
  }
  
  while (fgets(line,BUFLEN,fptr))
  {
    printf("\nline read: %s",line);
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);
    id_num = atoi(line_elements[0]);
    offset = ftell(fptr);
    printf("\nID: %d  Offset: %ld",id_num,offset);
    tree_node * temp_node = create_node(NULL,NULL,offset,id_num);
    temp_id_tree = tree_insert_id(temp_node,temp_id_tree);
    destroyStringArray(line_elements,file_line_length);
  }
  free(line);
  fclose(fptr);
  
  
  tempBST -> head_name = temp_tree;
  tempBST -> head_id = temp_id_tree;
  tempBST -> bus_file = (char *)businesses_path;
  tempBST -> rev_file = (char *)reviews_path;
  
  return tempBST;

}


struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
  struct Business * temp_bus = malloc(sizeof(struct Business));
  if (temp_bus == NULL)
    return NULL;
  tree_node * get_node = tree_search_name(bst->head_name,name); // find the node that has the correct name
  if (get_node == NULL)
    return NULL;
  List * get_list = search_params(get_node->location_list,state,zip_code); // get the list that only has locations of the parameters sent
  get_node -> location_list = get_list; // assign that new list to the found node
  int id = get_node -> id;
  uint32_t num_locs = List_length(get_list);
  temp_bus -> num_locations = num_locs;
  temp_bus -> name = strdup(name);
  int ind;
  uint32_t num_rev;
  struct Location * location_array = malloc(sizeof(struct Location) * num_locs);
  if (location_array == NULL)
    return NULL;
  for (ind = 0; ind < num_locs; ind++)
  {
    location_array[ind].address = get_list-> address;
    location_array[ind].city = get_list-> city;
    location_array[ind].state = get_list-> address;
    location_array[ind].zip_code = get_list-> address;
    struct Review * review_array = find_rev(bst->head_id,id,bst -> rev_file,&num_rev);
    location_array[ind].reviews = review_array;
    location_array[ind].num_reviews = num_rev;
    get_list = get_list -> next;
  }
  temp_bus -> locations = location_array;
  return temp_bus;
}

struct Review * find_rev(tree_node * head,int id,char * reviewfile,uint32_t * num_rev) 
{
  int file_line_length = 0;
  int id_num;
  char * line = malloc(BUFLEN * sizeof(char)); // line of data read from file
  char ** line_elements; // array of strings from line
  uint32_t number_rev = 0;
  tree_node * get_node = tree_search_id(head,id);
  long int offset = get_node -> offset;
  FILE * fptr = fopen(reviewfile,"r");
  if (fptr == NULL)
   return NULL;
  fseek(fptr, offset, SEEK_SET);
  while (fgets(line,BUFLEN,fptr))
  {
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);
    id_num = atoi(line_elements[0]);
    if (id_num != id)
    {
      destroyStringArray(line_elements,file_line_length);
      break;
    }
    number_rev++;
    destroyStringArray(line_elements,file_line_length);
  }
  * num_rev = number_rev;  
  struct Review * review_array = malloc(sizeof(struct Review) * (int)number_rev);
  fseek(fptr,offset,SEEK_SET);
  int ind;
  for (ind = 0; ind < number_rev;ind++)
  {
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length); 
    uint32_t star_num = (uint32_t)atoi(line_elements[1]);
    review_array[ind].stars = star_num;
    review_array[ind].text = line_elements[5];
    destroyStringArray(line_elements,file_line_length);
  }
  free(line);
  fclose(fptr);
  return review_array;
  
}
List * search_params(List * input_list,char * state,char * zip_code)
{
  if (state == NULL && zip_code == NULL)
    return input_list;
  
  List * temp_input = input_list;
  List * return_list = malloc(sizeof(List));
  int length_list = List_length(input_list);
  int ind;
  if (state == NULL)
  {
    for (ind = 0; ind < length_list; ind++)
    {
      if (strcmp(temp_input->zip,zip_code) == 0)
      {
	return_list = List_push(return_list,temp_input->id,temp_input->address,temp_input->state,temp_input->zip,temp_input->city);
      }
    }   
  }
  else if (zip_code == NULL)
  {
    for (ind = 0; ind < length_list; ind++)
    {
      if (strcmp(temp_input->state,state) == 0)
      {
	return_list = List_push(return_list,temp_input->id,temp_input->address,temp_input->state,temp_input->zip,temp_input->city);
      }
    }   
  }
  else
  {
    for (ind = 0; ind < length_list; ind++)
    {
      if (strcmp(temp_input->zip,zip_code) == 0 && strcmp(temp_input->state,state) == 0)
      {
	return_list = List_push(return_list,temp_input->id,temp_input->address,temp_input->state,temp_input->zip,temp_input->city);
      }
    }   
  }
  

  return return_list;
  
}

tree_node * tree_search_name(tree_node * root, char * name)
{
  tree_node * temp = root;
  
  if (root == NULL)
  {
    return NULL;
  }
  if (comp_names(root -> name,name) == 0)
  {
    return root;
  }
  if (comp_names(root -> name,name) > 0)
  {
    temp = tree_search_name(root -> left,name);
  }
  else
  {
    temp = tree_search_name(root -> right,name);
  }
  return temp;
}

tree_node * tree_search_id(tree_node * root, int id)
{
  tree_node * temp = root;
  
  if (root == NULL)
  {
    return NULL;
  }
  if (root->id == id)
  {
    return root;
  }
  if (root->id < id)
  {
    temp = tree_search_id(root -> right,id);
  }
  else
  {
    temp = tree_search_id(root -> left,id);
  }
  return temp;
}
  

void destroy_business_bst(struct YelpDataBST* bst)
{
  destroy_tree(bst->head_name);
  destroy_tree(bst->head_id);
  free(bst);
}

int comp_names(char * input_name ,char * node_name)
{
  int length_input = strlen(input_name);
  int length_node = strlen(input_name);
  if (length_input != length_node)
    return 0;
  int ind;
  char * str1 = malloc(sizeof(char) * length_input);
  char * str2 = malloc(sizeof(char) * length_node);
  strcpy(str1,input_name);
  strcpy(str2,node_name);
  for (ind = 0; ind < length_input;ind++)
  {
    str1[ind] = tolower(str1[ind]);
    str2[ind] = tolower(str2[ind]);
  }
  if (strcmp(str1,str2) == 0)
  {
    free(str1);
    free(str2);
    return 0;
  }
  else if (strcmp(str1,str2) < 0)
  {
    free(str1);
    free(str2);
    return -1;
  }
  else
  {
    free(str1);
    free(str2);
    return 1; 
  }
  
}

void destroy_business_result(struct Business* b)
{
  
  
  
}
                                   
                               