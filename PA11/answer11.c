#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer11.h"
#include "treefun.h"


void List_destroy(StackNode *);
int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte); // From Book

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
  free(stack -> head); 
  free(stack);
  return return_tree;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp) // From Liu's Book- I did not write
{
  
  int done = 0;
  unsigned char whichbit = 0;
  unsigned char curbyte = 0;
  unsigned char onebit = 0;
  Stack * stack = Stack_create(0) ;
  while (done == 0)
  {
    readBit (fp ,& onebit ,& whichbit ,& curbyte );
    if (onebit == 1)
    {
      // a leaf node , get 7 move bits
      int bitcount ;
      unsigned char value = 0;
      for (bitcount = 0; bitcount < 8; bitcount ++)
      {
	value <<= 1; // shift left by one
	readBit (fp, & onebit, & whichbit, &curbyte );
	value |= onebit ;
      }
      // push a tree node into the list
      HuffNode * tn = HuffNode_create(value);
      Stack_pushFront(stack, tn);
      //StackNode * ln = StackNode_create();
      //head = List_insert (head , ln , STACK );
    }
    else
    {
      if (stack->head->next != NULL)
      {
	Stack_popPopCombinePush(stack);
      }
      else
      {
	done = 1;
      }
    }
  }
   
  // unnecessary to read the remaining unused bits
  HuffNode * root = stack->head->tree;
  // the linked list is no longer needed
  free (stack->head);
  free(stack);
  return root;
}


int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte) // From Liu's Book- I did not write
{
  int ret = 1;
  if((*whichbit) == 0)
  {
    // read a byte from a file
    ret = fread(curbyte, sizeof(unsigned char), 1, fptr);
  }
  if(ret != 1)
  {
    return -1;
  }
  unsigned char temp = (*curbyte) >> (7 - (*whichbit));
  temp = temp & 0X01;
  *whichbit = ((*whichbit) + 1) % 8;
  *bit = temp;
  return 1;

}
