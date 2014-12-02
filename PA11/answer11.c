#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer11.h"
#include "treefun.h"


void List_destroy(StackNode *);
unsigned char get_byte(FILE *);

void List_destroy(StackNode * input_list)
{
  while (input_list != NULL)
  {
    StackNode * temp = input_list -> next;
    HuffNode_destroy(input_list -> tree);
    free(input_list);
    input_list = temp;
  }
}

HuffNode * HuffNode_create(int value)
{
  HuffNode * temp = malloc(sizeof(HuffNode));
  if (temp == NULL)
    return NULL;
  temp -> left = NULL;
  temp -> right = NULL;
  temp -> value = value;
  return temp;
}

void HuffNode_destroy(HuffNode * tree)
{
   if (tree == NULL)
   {
     free(tree);
     return;
   }
   HuffNode_destroy(tree -> left);
   HuffNode_destroy(tree -> right);
   free(tree);
}

Stack * Stack_create()
{
  Stack * temp_stack = malloc(sizeof(Stack));
  temp_stack -> head = NULL;
  return temp_stack;
}

void Stack_destroy(Stack * stack)
{
  List_destroy(stack -> head);
  free(stack);
}

int Stack_isEmpty(Stack * stack)
{
  if (stack == NULL)
    return 1;
  return 0;
}

HuffNode * Stack_popFront(Stack * stack)
{
  if (stack -> head == NULL){
    Stack_destroy(stack);
    return NULL;}
  StackNode * temp = stack -> head -> next;
  HuffNode * tree = stack -> head -> tree;
  free(stack -> head);
  stack -> head = temp;
  return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  if (stack -> head == NULL)
  {
    stack -> head = malloc(sizeof(StackNode));
    stack -> head -> tree = tree;
    stack -> head -> next = NULL;
    return;
  }
  
  if (tree == NULL)
    return;
  
  StackNode * front = malloc(sizeof(StackNode));
  front -> tree = tree;
  front -> next = stack -> head;
  stack -> head = front;
}

void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode * return_tree = HuffNode_create(0);
  HuffNode * right_tree = Stack_popFront(stack);
  HuffNode * left_tree = Stack_popFront(stack);
  return_tree -> left = left_tree;
  return_tree -> right = right_tree;
  Stack_pushFront(stack,return_tree);
}
  
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  Stack * stack = Stack_create();
  unsigned char byte = 0;
  HuffNode * return_tree;
  while ((byte = (fgetc(fp))))
  {
    if (byte == '1')
    {
      byte = fgetc(fp);
      return_tree = HuffNode_create(byte);
      Stack_pushFront(stack,return_tree);
    }
    else
    {
    if (byte == '0' && (stack -> head -> next != NULL))
    {
      Stack_popPopCombinePush(stack);
    }
    else
    {
	break;      
    }
    }
  }
  return_tree = stack -> head -> tree;
  free(stack -> head); // do i need to call destroy stack
  free(stack);
  return return_tree;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
  Stack * stack = Stack_create();
  HuffNode * return_tree;
  // need to convert binary file into 1 array with ascii values and keep track of length
  
  //find how many characters are in it
  unsigned char val;
  int length_arr;
  int ind;
  while ((val = (fgetc(fp))))
  {
     length_arr++;
  }
  fseek(fp,0,SEEK_SET); //put back to beginning 
  unsigned char * arr = malloc(sizeof(unsigned char) * (length_arr + 1));
  arr[length_arr] = '\0';
  for (ind = 0; ind < length_arr; ind++)
  {
    arr[ind] = get_byte(fp);
  }
  
  
  
  for (ind = 0; ind < length_arr; ind++)
  {
    if (arr[ind] == '1')
    {
      ind++;
      val = arr[ind];
      printf("val = %c\n",val);
      return_tree = HuffNode_create(val);
      Stack_pushFront(stack,return_tree);
    }
    else
    {
    if (arr[ind] == '0' && (stack -> head -> next != NULL))
    {
      Stack_popPopCombinePush(stack);
      HuffNode_printPretty(stdout,return_tree);
    }
    else
    {
	break;      
    }
    }
  }
  //return_tree = stack -> head -> tree;
  free(stack -> head); // do i need to call destroy stack
  free(stack);
  free(arr);
  return return_tree;
}

unsigned char get_byte(FILE * fp)
{
  unsigned char byte = fgetc(fp);
  int final = 0;
  int ind;
  int power;
  int current;
  for (ind = 7; ind >= 0; ind--)
  {
     current = 1;
     int mask = (1 << ind);
     int set = byte & mask;
     int bit = (set >> ind);
     for (power = 0; power < ind; power++)
     {
       current *= 2;
     }
     final += current * bit;
  }
  
  return ((unsigned char) final);
}
