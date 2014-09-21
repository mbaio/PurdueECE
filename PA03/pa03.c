#include "answer03.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
  
  int n1val = 6;
  int n2val = 6;
  int n3val = 0;

  int *n1 = &n1val;
  int *n2 = &n2val;
  int *n3 = &n3val;

 

  char * dest1 = malloc(*n1 * sizeof(char));
  char * dest2 = malloc(*n2 * sizeof(char));
  char * dest3 = malloc(*n3 * sizeof(char));

  strcpy(dest1,"Hello ");
  strcpy(dest2,"Bitch ");
  strcpy(dest3,"");


  const char * src1 = "Man";
  const char * src2 = "Yo";
  const char * src3 = "Dubai";

  *dest1 = strcat_ex(&dest1,n1,src1);
  *dest2 = strcat_ex(&dest2,n2,src2);
  *dest3 = strcat_ex(&dest3,n3,src3);

  free(dest1);
  free(dest2);
  free(dest3);

  return 0;
}

