#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer11.h"

void List_destroy(StackNode *);

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
  if (stack -> head == NULL)
    return NULL;
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
  HuffNode * left_tree = Stack_popFront(stack);
  HuffNode * right_tree = Stack_popFront(stack);
  return_tree -> left = left_tree;
  return_tree -> right = right_tree;
  Stack_pushFront(stack,return_tree);
}
  
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  HuffNode * return_tree = HuffNode_create(0);
  Stack * stack = Stack_create();
  unsigned char byte = 0;
  
  while (byte = fgetc(fp))
  {
    if (byte == '1')
    {
      byte = fgetc(fp);
      return_tree = HuffNode_create(byte);
      Stack_pushFront(stack,return_tree);
    }
    if (byte == '0' && (stack -> head -> next != NULL))
    {
      Stack_popPopCombinePush(stack);
    }
    else
    {
	break;      
    }
  }
  return_tree = stack -> head -> tree;
  Stack_destroy(stack);
  return return_tree;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
  HuffNode * temp = malloc(sizeof(HuffNode));
  temp = NULL;
  return temp;
}
  
  

