#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void partitionhelper(int * buffer, int ind, int value, int (*testfun)(int value, int * array, int ind))
{
 // FUNCTION FROM TA HELP ROOM IN EE 206 FROM BRIAN ON MONDAY
 if (value == 0)
 {
   printpartition  // fill in print function
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
}

int useall(int value, int * arr, int ind)
{
  return(1);
}

int isincreasing(int value, int * arr, int ind)
{
  return(value > arr[ind - 1]);
}

int isdecreasing(int value, int * arr, int ind)
{
  return(value < arr[ind - 1]);
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
  return((value % 2 == 0 && arr[ind - 1] % 2 != 0) || (value % 2 != 0 && arr[ind - 1] % 2 == 0));
}

int isprime(int value, int * arr, int ind)
{
  return
}
