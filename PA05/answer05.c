#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"


void partitionhelper(int * buffer, int ind, int value, int (*testfun)(int value, int * array, int ind))
{
 // FUNCTION FROM TA HELP ROOM IN EE 206 FROM BRIAN ON MONDAY 10/7/14
 if (value == 0)
 {
   printpartition((int *) buffer, ind);
   return;
 }

 int nextval;
 for (nextval = 1; nextval <= value; ++nextval)
 {
   if (testfun(nextval, buffer, ind)) 
   {  
     buffer[ind] = nextval;
	 partitionhelper(buffer, ind + 1, value - nextval, testfun);
   }
 }
 return;
}

void printpartition(int * arr, int length)
{
 // Function from the Text Book with modifications
 int ind;
 printf("= ");
 for (ind = 0; ind < length - 1; ind++)
  {
   printf("%d + ", arr[ind]);
  }

  printf("%d\n",arr[length - 1]);
  return;
}

int useall(int value, int * arr, int ind)
{
  return(1);
}

int isincreasing(int value, int * arr, int ind)
{
  if (ind != 0){
  return(value > arr[ind - 1]);
  }
  else
  {
  return(1);
  }
}

int isdecreasing(int value, int * arr, int ind)
{
  if (ind != 0){
  return(value < arr[ind - 1]);
  }
  else
  {
  return(1);
  }
}

int isodd(int value, int * arr, int ind)
{
  return(value % 2 != 0);
}

int iseven(int value, int * arr, int ind)
{
  return(value % 2 == 0);
}

int isevenandodd(int value, int * arr, int ind)
{
  if (ind != 0){
  return((value % 2 == 0 && arr[ind - 1] % 2 != 0) || (value % 2 != 0 && arr[ind - 1] % 2 == 0));
  }
  else
  {
  return(1);
  }
}

int isprime(int value, int * arr, int ind)
{
  int outcome = 0;
  int factor;
  if (value == 1)
  {
  return(0);
  }
  
  for (factor = 2; factor < value; factor++)
  {
    if (value % factor == 0) { outcome = 1; 
	break;
	}
  }

  
  return(! outcome);
}

void partitionAll(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,useall);
  free(buffer); 
}

void partitionIncreasing(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,isincreasing);
  free(buffer); 
}
  
void partitionDecreasing(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,isdecreasing);
  free(buffer); 
}

void partitionOdd(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,isodd);
  free(buffer); 
}

void partitionEven(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,iseven);
  free(buffer); 
}

void partitionOddAndEven(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,isevenandodd);
  free(buffer); 
}

void partitionPrime(int value)
{
  int * buffer = malloc(value * sizeof(int));
  partitionhelper(buffer,0,value,isprime);
  free(buffer); 
}


/*int main()
{
  
  partitionAll(6);
  partitionIncreasing(6);
  partitionDecreasing(6);
  partitionOdd(6);
  partitionEven(6);
  partitionOddAndEven(6);
  partitionPrime(6);

  
  
  return(0);
}
*/
