#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint128 alphaTou128(const char * str)
{
  int ind = 0;
  uint128 return_val = 0;
  while (str[ind] >= '0' && str[ind] <= '9')
    {
      return_val *= 10;
      return_val += ((int)str[ind] - (int)'0');
      ind++;
    }
return(return_val);  
}

