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

  char * str1 = malloc(15*sizeof(char));
  char * str2 = malloc(15*sizeof(char));

  strcpy(str1,"hello my name");
  strcpy(str2,"Yo dawg lol ha");
  

  char * delims1 = malloc(2*sizeof(char));
  char * delims2 = malloc(2*sizeof(char));
  
  strcpy(delims1," ");
  strcpy(delims2," ");

  int arrlen1val = 0;
  int arrlen2val = 0;

  int * len1 = &arrlen1val;
  int * len2 = &arrlen2val;

  char ** answer1 = explode(str1,delims1,len1);
  char ** answer2 = explode(str2,delims2,len2);
 
  free(str1);
  free(str2);
  free(delims1);
  free(delims2);


  
 
 
 
 return 0;
}

