#include "answer10.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define BUFLEN 2500


typedef struct ListNode_st
{
    int id;
    long int offset_bus;
    long int offset_rev;
    struct ListNode_st * next;
} List;

typedef struct tree_node_t
{
  List * location_list;
  char * name;
  struct tree_node_t * left;
  struct tree_node_t * right;
} tree_node;

struct YelpDataBST
{
  tree_node * head_name;
  char * bus_file;
  char * rev_file;
};
long int find_rev_offset(int,char *);
List * List_createNode(int, long int, long int);
void List_destroy(List *);
int List_length(List *);
List * List_push(List *,int, long int, long int);
char ** explode(const char *, const char *,int *);
tree_node * create_node(List *,char *);
tree_node * tree_insert_name(tree_node *, tree_node *);
void destroy_tree(tree_node *);
void print_tree_name(tree_node *);
void print_node_name(tree_node *);
void print_list(List *);
void destroyStringArray(char **, int);
tree_node * tree_search_name(tree_node *,char *);
List * search_params(List *,char *,char *,char *,uint32_t *);
struct Location get_location_struct(List *,char *,char *);
struct Review * find_rev(List *,char *,uint32_t *);
void destroy_locations(struct Location);
void destroy_business_result(struct Business *);
List * List_delete(List * head,int id);
int cmploc(const void * ptr1,const void * ptr2);
int cmprev(const void * ptr1,const void * ptr2);

List * List_createNode(int id, long int offset_bus, long int offset_rev)
{
    List * temp_list = malloc(sizeof(List));
    temp_list -> id = id;
    temp_list -> offset_bus = offset_bus;
    temp_list -> offset_rev = offset_rev;
    temp_list -> next = NULL;
    return temp_list;
}
void List_destroy(List * list) // code from Prof Liu Book page 305
{
    while (list != NULL)
    {
      List * temp_list = list -> next;
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
List * List_push(List * head, int id, long int offset_bus, long int offset_rev)
{
        List * newhead = List_createNode(id, offset_bus, offset_rev);
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
tree_node * create_node(List * location_list, char * name)
{
  tree_node * temp_node = malloc(sizeof(tree_node));
  temp_node -> location_list = location_list;
  temp_node -> name = strdup(name);
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
    root->location_list = List_push(root -> location_list, node->location_list->id, node->location_list->offset_bus, node->location_list->offset_rev); 
    destroy_tree(node); // maybe take out idk
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
  free(equals);
  return;
}
void print_list(List * list)
{ 
  List * temp_list = list; 
  printf("\n");
  while(temp_list != NULL)
  {
    printf("List: Id: %d    Bus offset: %ld    Rev offset: %ld\n",temp_list -> id,temp_list -> offset_bus,temp_list -> offset_rev);
    temp_list = temp_list -> next;  
  }
}
struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
  struct YelpDataBST * tempBST = malloc(sizeof(struct YelpDataBST));
  if (tempBST == NULL)
  {
    return NULL;
  }
  tree_node * temp_tree = NULL;
  int file_line_length1 = 0;
  int file_line_length2 = 0;
  int id_num1;
  int id_num2 = 0;
  char * line1 = malloc(BUFLEN * sizeof(char)); // line of data read from file
  char ** line_elements1; // array of strings from line
  char * line2 = malloc(BUFLEN * sizeof(char)); // line of data read from file
  char ** line_elements2; // array of strings from line
  long int offset_bus = 0;
  long int offset_rev = 0;
  if (line1 == NULL || line2 == NULL)
  {
    fprintf(stderr,"line not initialized!\n");
    free(line1);
    free(line2);
    return NULL;
  }
  FILE * fptr_bus = fopen(businesses_path,"r"); // open businesses to make tree
  FILE * fptr_rev = fopen(reviews_path,"r");
  if (fptr_bus == NULL || fptr_rev == NULL)
  {
    fprintf(stderr,"Could not open file!\n");
    free(line1);
    free(line2);
    return NULL;
  }
  int linelen1;
  int linelen2;
  while (fgets(line1, BUFLEN, fptr_bus))
  {
    linelen1 = strlen(line1);
    if(linelen1 > 0 && line1[linelen1-1] == '\n')
      line1[linelen1-1] = '\0';
    line_elements1 = explode(line1,"\t",&file_line_length1);   
    id_num1 = atoi(line_elements1[0]);
    while (id_num2 <= id_num1)
    {
      fgets(line2,BUFLEN,fptr_rev);
      linelen2 = strlen(line2);
      if(linelen2 > 0 && line2[linelen2-1] == '\n')
        line2[linelen2-1] = '\0';
      line_elements2 = explode(line2,"\t",&file_line_length2);   
      id_num2 = atoi(line_elements2[0]);
      if (id_num2 == id_num1)
      {
        List * list_node = List_createNode(id_num1,offset_bus,offset_rev);
        tree_node * temp_node = create_node(list_node,line_elements1[1]);
        temp_tree = tree_insert_name(temp_node,temp_tree);   
        destroyStringArray(line_elements2, file_line_length2);
	break;
      }
      offset_rev = ftell(fptr_rev);
      destroyStringArray(line_elements2, file_line_length2);
    }
    destroyStringArray(line_elements1, file_line_length1);
    offset_bus = ftell(fptr_bus);
  }  


  free(line1);
  free(line2);
  fclose(fptr_bus);
  fclose(fptr_rev);
  tempBST -> head_name = temp_tree;
  tempBST -> bus_file = (char *)businesses_path;
  tempBST -> rev_file = (char *)reviews_path;
  return tempBST;
}
// long int find_rev_offset(int id,char * reviews_path)
// {
//   FILE * fptr = fopen(reviews_path,"r");
//   if (fptr == NULL)
//     return -1;
//   char * line = malloc(sizeof(char) * BUFLEN);
//   char ** line_elements;
//   int linelen;
//   int id_num;
//   int file_line_length;
//   long int old_offset = 0;
//   while (fgets(line, BUFLEN, fptr))
//   {
//     linelen = strlen(line);
//     if(linelen > 0 && line[linelen-1] == '\n')
//       line[linelen-1] = '\0';
//     line_elements = explode(line,"\t",&file_line_length);   
//     id_num = atoi(line_elements[0]);
//     if (id_num == id){
//       fclose(fptr);
//       destroyStringArray(line_elements,file_line_length);
//       free(line);
//       return old_offset; 
//     }
//     old_offset = ftell(fptr);
//     destroyStringArray(line_elements,file_line_length);
//   }
//   free(line);
//   return -1; 
// }

struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
  struct Business * temp_bus = malloc(sizeof(struct Business));
  temp_bus -> name = name;
  temp_bus -> locations = NULL;
  temp_bus -> num_locations = 0;
  if (temp_bus == NULL)
    return temp_bus;
  tree_node * get_node = tree_search_name(bst->head_name,name); // find the node that has the correct name
  if (get_node == NULL)
  {
    return temp_bus;
  }
  uint32_t num_locs; // fix if list is null
  get_node -> location_list = search_params(get_node->location_list,state,zip_code,bst->bus_file,&num_locs); // get the list that only has locations of the parameters sent
  if (num_locs > 0)
    temp_bus -> name = get_node -> name;
  temp_bus -> num_locations = num_locs;
  int ind;
  struct Location * location_array = malloc(sizeof(struct Location) * (num_locs + 1));
  if (location_array == NULL){
    return temp_bus;
  }
  List * temp_list2 = get_node->location_list;
  for (ind = 0; ind < num_locs; ind++)
  {
    location_array[ind] = get_location_struct(temp_list2,bst->bus_file,bst->rev_file);
    temp_list2 = temp_list2 -> next;
  }
  temp_bus -> locations = location_array;
  
  //sorting state > city > address and star rating
  qsort(temp_bus -> locations,temp_bus -> num_locations,sizeof(struct Location),cmploc);
  for (ind = 0; ind < temp_bus -> num_locations;ind++)
  {
    qsort(temp_bus -> locations[ind].reviews,temp_bus -> locations[ind].num_reviews,sizeof(struct Review),cmprev);
  }
  
  return temp_bus;
}

int cmploc(const void * ptr1,const void * ptr2)
{
  struct Location * locptr1 = (struct Location *) ptr1;
  struct Location * locptr2 = (struct Location *) ptr2;
  char * str1 = malloc(sizeof(char) * BUFLEN);
  char * str2 = malloc(sizeof(char) * BUFLEN);
  strcpy(str1,(* locptr1).state);
  strcpy(str2,(* locptr2).state);
  strcat(str1,(* locptr1).city);
  strcat(str2,(* locptr2).city);
  strcat(str1,(* locptr1).address);
  strcat(str2,(* locptr2).address);
  int outcome = strcmp(str1,str2);
  free(str1);
  free(str2);
  return outcome;
}

int cmprev(const void * ptr1,const void * ptr2)
{
  struct Review * valptr1 = (struct Review *) ptr1;
  struct Review * valptr2 = (struct Review *) ptr2;
  int val1 = (int)  (* valptr1).stars ;
  int val2 = (int)  (* valptr2).stars ;
  
  if (val1 > val2)
    return -1;
  else if (val1 < val2)
    return 1;
  else 
    return (strcasecmp((* valptr1).text,(* valptr2).text));
}

struct Location get_location_struct(List * input_list,char * bus_file,char * rev_file)
{
  struct Location return_location;
  uint32_t num_rev;
  return_location.reviews = find_rev(input_list,rev_file,&num_rev);
  return_location.num_reviews = num_rev;
  if (num_rev == 0)
  {
    return_location.address = NULL;
    return_location.city = NULL;
    return_location.state = NULL;
    return_location.zip_code = NULL;
    return return_location;
  }
  FILE * fptr = fopen(bus_file,"r");
  if (fptr == NULL)
    return return_location;
  fseek(fptr,input_list->offset_bus,SEEK_SET);
  char * line = malloc(sizeof(char) * BUFLEN);
  char ** line_elements;
  int linelen;
  int file_line_length;
  
  fgets(line, BUFLEN, fptr);
  linelen = strlen(line);
  if(linelen > 0 && line[linelen-1] == '\n')
    line[linelen-1] = '\0';
  line_elements = explode(line,"\t",&file_line_length);  
  return_location.address = strdup(line_elements[2]);
  return_location.city = strdup(line_elements[3]);
  return_location.state = strdup(line_elements[4]);
  return_location.zip_code = strdup(line_elements[5]);
  destroyStringArray(line_elements,file_line_length);
  free(line);
  fclose(fptr);
  return return_location;
  
}

struct Review * find_rev(List * input_list,char * rev_file,uint32_t * num_rev) 
{
  int file_line_length = 0;
  char * line = malloc(BUFLEN * sizeof(char)); // line of data read from file
  char ** line_elements; // array of strings from line
  uint32_t number_rev = 0;
  FILE * fptr = fopen(rev_file,"r");
  if (fptr == NULL)
   return NULL;
  fseek(fptr, input_list->offset_rev, SEEK_SET);
  while (fgets(line,BUFLEN,fptr))
  {
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);
    int id_num = atoi(line_elements[0]);
    if (id_num != input_list->id)
    {
      destroyStringArray(line_elements,file_line_length);
      break;
    }
    number_rev++;
    destroyStringArray(line_elements,file_line_length);
  }
  * num_rev = number_rev;  
  if (number_rev == 0)
  {
    struct Review * review_array = malloc(sizeof(struct Review));
    review_array[0].stars = 0;
    review_array[0].text = NULL;
    return review_array;
  }
  struct Review * review_array = malloc(sizeof(struct Review) * (int)number_rev);
  fseek(fptr,input_list->offset_rev,SEEK_SET);
  
  int ind;
  for (ind = 0; ind < number_rev;ind++)
  {
    fgets(line,BUFLEN,fptr);
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length); 
    uint32_t star_num = (uint32_t)atoi(line_elements[1]);
    review_array[ind].stars = star_num;
    review_array[ind].text = strdup(line_elements[5]);
    destroyStringArray(line_elements,file_line_length);
  }
  free(line);
  fclose(fptr);
  return review_array;
}

List * List_delete(List * head,int id) //code from textbok page 302
{
  List * p = head;
  if (p == NULL)
  {
    return p;
  }
  if ((p -> id) == id)
  {
    p = p -> next;
    free(head);
    return p;
  }
  List * q = p -> next;
  while ((q != NULL) && ((q -> id) != id))
  {
    p = p->next;
    q = q->next;
  }
  if (q != NULL)
  {
    p -> next = q -> next;
    free(q);
  }
  return head;
}


List * search_params(List * input_list,char * state,char * zip_code,char * businesses_path,uint32_t * num_locs)
{
  //printf("input list\n");
 // print_list(input_list);
  uint32_t num_locations;
  if ((state == NULL && zip_code == NULL)){// || (strcmp(state,"") == 0 && strcmp(zip_code,"") == 0)){
    //printf("entered null null\n");
    num_locations = List_length(input_list);
    * num_locs  = num_locations;
    return input_list; }
  //printf("printing input list:\n");
  //print_list(input_list);
  List * temp_input = input_list;
  int length_list = List_length(input_list);
  //int ind;
  char * line = malloc(sizeof(char) * BUFLEN);
  char ** line_elements;
  int file_line_length;
  FILE * fptr = fopen(businesses_path,"r");
  if (fptr == NULL)
    return input_list;
  int checked = 0;
  while (checked <= length_list && temp_input != NULL)
  {
    if (length_list == 0)
      break;
    fseek(fptr,temp_input->offset_bus,SEEK_SET);
    fgets(line,BUFLEN,fptr);
    int linelen = strlen(line);
    if(linelen > 0 && line[linelen-1] == '\n')
      line[linelen-1] = '\0';
    line_elements = explode(line,"\t",&file_line_length);
    if (state == NULL || strcmp(state,"") == 0)
    {
      if (strcmp(zip_code,line_elements[5]) != 0){
      input_list = List_delete(input_list,temp_input->id);
      temp_input = input_list;
      length_list--;
      }
      else
      {
	temp_input = input_list -> next;
      }
    }
    else if (zip_code == NULL || strcmp(zip_code,"") == 0)
    {
      if (strcasecmp(state,line_elements[4]) != 0){
      input_list = List_delete(input_list,temp_input->id);
      temp_input = input_list;
      length_list--;
      }
      else
      {
	temp_input = input_list -> next;
      }
    }
    else 
    {
      //printf("Comparing %s and %s -------%s and %s\n",zip_code,line_elements[5],state,line_elements[4]);
      if (strcmp(zip_code,line_elements[5]) != 0 || strcasecmp(state,line_elements[4]) != 0){ 
        //printf("entered delete\n");
	//int test = temp_input -> id;
	input_list = List_delete(input_list,temp_input->id);
	temp_input = input_list;
      length_list--; }
      else
      {
	temp_input = input_list -> next;
      }
    }
    destroyStringArray(line_elements,file_line_length);
    checked++;
    
  }
  free(line);
  fclose(fptr);
  length_list = List_length(input_list);
  //printf("\nlength list = %d\n",length_list);
  * num_locs = length_list;
 // printf("Final list\n");
 // print_list(input_list);
  return input_list;
}

tree_node * tree_search_name(tree_node * root, char * name)
{
  tree_node * temp = root;
  
  if (root == NULL)
  {
    return NULL;
  }
  if (strcasecmp(root -> name,name) == 0)
  {
    return root;
  }
  if (strcasecmp(root -> name,name) > 0)
  {
    temp = tree_search_name(root -> left,name);
  }
  else
  {
    temp = tree_search_name(root -> right,name);
  }
  return temp;
}


void destroy_business_bst(struct YelpDataBST* bst)
{
  destroy_tree(bst->head_name);
  free(bst);
}

void destroy_business_result(struct Business* b)
{

  uint32_t ind;
  uint32_t num_locations = b -> num_locations;
  for (ind = 0; ind < num_locations; ind++)
  {
    destroy_locations(b->locations[ind]);
  }
  free(b->locations);
  
  free(b);
}

void destroy_locations(struct Location location)
{
  int ind;
  uint32_t num_rev = location.num_reviews;
  for (ind = 0; ind < num_rev; ind++)
  {
    free(location.reviews[ind].text);
  }
  free(location.reviews);
  free(location.address);
  free(location.city);
  free(location.state);
  free(location.zip_code);
}

                                   
                               