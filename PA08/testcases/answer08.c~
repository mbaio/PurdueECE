#include "answer08.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List * List_createNode(const char * str)
{
    List * temp_list = malloc(sizeof(List));
    temp_list -> str = strdup(str);
    temp_list -> next = NULL;
    return temp_list;
}

void List_destroy(List * list) // code from Prof Liu Book page 305
{
    while (list != NULL)
    {
      List * temp_list = list -> next;
      free (List);
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

List * List_merge(List * lhs, 
		  List * rhs, 
		  int (*compar)(const char *, const char*))
		  
		  {
		    List * temp_list = NULL;
		    return temp_list;
		  }
		  
		  
List * List_sort(List * list, int (*compar)(const char *, const char*))
		  {
		    List * temp_list = NULL;
		    return temp_list;
		  }
  