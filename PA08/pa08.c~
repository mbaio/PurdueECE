#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer08.h"

int main()
{
  List * lhs = List_createNode("1");
  lhs -> next = List_createNode("2");
  lhs -> next->next = List_createNode("3");
  lhs -> next->next->next = List_createNode("4");
  List * appended = NULL;

  List * rhs = List_split(lhs);

  while (lhs != NULL)
  {
    printf("\nLHS = %s",lhs->str);
    lhs = lhs->next;
  }
  while (rhs != NULL)
  {
    printf("\n\nRHS = %s",rhs->str);
    rhs = rhs -> next;
  }
  
  lhs = NULL;
  rhs = NULL;
  
  lhs = List_createNode("1");
  lhs -> next = List_createNode("2");
  rhs = List_createNode("3");
  rhs -> next = List_createNode("4");
 
  appended = List_append(lhs,rhs);
  
  while (appended != NULL)
  {
    printf("\n\nappended = %s",appended->str);
    appended = appended -> next;
  }
  

return 0;
}
