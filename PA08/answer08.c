#include "answer08.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List * List_append(List * result,List * node); 
List * List_split(List * source);

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
      free (list -> str);
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

List * List_merge(List * lhs, 
		  List * rhs, 
		  int (*compar)(const char *, const char*))
		  
		  {
		    if (lhs == NULL)
		    {
		      return rhs;
		    }
		    if (rhs == NULL)
		    {
		      return lhs;
		    }
		    
		    List * temp_lhs = lhs;
		    List * temp_rhs = rhs;
		    List * merged = NULL;
		    List * temp_node = NULL;
		   
		    
		    while (temp_lhs != NULL && temp_rhs != NULL)
		    {
		      if (compar(temp_lhs -> str,temp_rhs -> str) <= 0)
		      {
			// make temp pointer for node to send
			temp_node = temp_lhs -> next; //set a temp node to the next value of the linked list
			temp_lhs -> next = NULL; // erase the next linked list so there is only one value to add to the list
			merged = List_append(merged,temp_lhs); // update the merged list
			temp_lhs = temp_node; // set the list back to the next value
		      }
		      else
		      {
			// make temp node
			temp_node = temp_rhs -> next;
			temp_rhs -> next = NULL;
			merged = List_append(merged,temp_rhs);
			temp_rhs = temp_node;
		      }
		      
		      }
			
		    
		    //leftovers
		    //send whole node to append to get the rest for when 1 is null
		    if (temp_lhs == NULL)
			{
			  merged = List_append(merged,temp_rhs);
			}
			if (temp_rhs == NULL)
			{
			  merged = List_append(merged,temp_lhs);
			  }

		    
		    return merged;
		    
		  }
		  
		  
List * List_sort(List * list, int (*compar)(const char *, const char*))
		  {
		    if (List_length(list) == 0 || List_length(list) == 1)
		    {
		      return list;
		    }
		    
		    List * sorted = NULL;
		    List * lhs = list;
		    List * rhs = NULL;
		    
		    rhs = List_split(lhs);
		    lhs = List_sort(lhs,compar);
		    rhs = List_sort(rhs,compar);
		    
		    sorted = List_merge(lhs,rhs,compar);
		    
		    return sorted;
		  }
		  
List * List_append(List * result,List * node)
{
  if (result == NULL)
  {
    return node;
  }
  if (node == NULL)
  {
    return result;
  }
  

  
  List * temp_list = result;
 
  while (result -> next != NULL)
  {
    result = result -> next;
  }
  result -> next = node;
  
  
  
  return (temp_list);
}

List * List_split(List * source)
{
  List * lhs = source;
  List * rhs = NULL;
  
  int length_list = List_length(source);
  int midpt = length_list / 2;
  int ind;
  
  for (ind = 0;ind < midpt - 1;ind++)
  {
    
    lhs = lhs -> next;
  }
    rhs = lhs -> next;
    lhs -> next = NULL; // does this change sourceList * 
  
 
  return rhs;
}
  
