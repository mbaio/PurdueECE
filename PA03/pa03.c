#include "answer03.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
  printf("\n\nNow Testing PA03. . . .\n");
  
  // strcat_ex
  //
  int n1val = 5;
  int n2val = 0;
  int n3val = 1;

  int *n1 = &n1val;
  int *n2 = &n2val;
  int *n3 = &n3val;

 

  char * dest1 = malloc(*n1 * sizeof(char));
  char * dest2 = malloc(*n2 * sizeof(char));
  char * dest3 = malloc(*n3 * sizeof(char));

  strcpy(dest1,"Hello");
  strcpy(dest2,"");
  strcpy(dest3," ");


  const char * src1 = " Man";
  const char * src2 = "Yo";
  const char * src3 = "Dubai";

  printf("\nFunction: strcat_ex");
printf("\nSending %s \t%s",dest1,src1);
printf("\nReceived %s",strcat_ex(&dest1,n1,src1));
//printf("\nSending %s, \t%d, \t%s, and receiving \t%s",dest2,*n2,src2,strcat_ex(&dest2,n2,src2));
//printf("\nSending %s, \t%d, \t%s, and receiving \t%s",dest3,*n3,src3,strcat_ex(&dest3,n3,src3));


  return 0;
}

