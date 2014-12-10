#include "answer12.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// int main(int argc, char * * argv)
// {
//     const char * str = "47";
//     uint128 w = alphaTou128(str);
//     char * w_str = u128ToString(w);
//     printf("Testing %s is Prime: %s",str,primalityTestParallel(w, 4) ? "TRUE" : "FALSE");
//     free(w_str);
//     return EXIT_SUCCESS;
// }
typedef struct 
{
  int start;
  int end;
  int isprime;
  uint128 value;
}Data;

void close_threads(pthread_t * thread_array, int num_threads, Data * data_array);
void * isPrime(void * ptr);

uint128 alphaTou128(const char * str)
{
  int ind = 0;
  uint128 return_val = 0;
 for (ind = 0; ind < strlen(str); ind++)
    {
      if (str[ind] >= '0' && str[ind] <= '9')
      {
	return_val *= 10;
	return_val += ((int)str[ind] - (int)'0');
      }
      else if (str[ind] != ' ')
	return return_val;
    }
return(return_val);  
}

char * u128ToString(uint128 value)
{
  int count = 0;
  uint128 temp = value;
  while (temp > 0)
  {
    count++;
    temp = temp / 10;
  }
  if (value == 0)
  {
    char * return_str = malloc(sizeof(char) * 2);
    return_str[0] = '0';
    return_str[1] = '\0';
    return return_str;
  }
  
  if (value / 10 == 0)
    count = 1;
  char * return_str = malloc(sizeof(char) * (count + 1));
  if (return_str == NULL)
    return NULL;
  return_str[count] = '\0';
  int ind = count - 1;
  while (value > 0)
  {
    return_str[ind] = (char) (value % 10 + '0');
    value = value / 10;
    ind--;
  }
  return return_str;
}



int primalityTestParallel(uint128 value, int n_threads)
{
  pthread_t * thread_array = malloc(sizeof(pthread_t) * n_threads);
  int ind = 0;
  Data * data_array = malloc(sizeof(Data) * n_threads);
  int num_vals = (ceil((sqrt((float) value) / n_threads))); //int num_vals = ceil((sqrt((float) value) + 1 + n_threads) / n_threads);
  int return_value = 1;
  data_array[0].start = 3;
  data_array[0].end = 3 + num_vals;
  data_array[0].value = value;
  
  for (ind = 0; ind < n_threads; ind++)
  {
    
    data_array[ind].start = num_vals * ind;
    data_array[ind].end = num_vals * (ind + 1);
    data_array[ind].value = value;
    if (ind == n_threads)
      data_array[ind].end = num_vals * (ind + 1) + 1;
    pthread_create(&thread_array[ind],NULL,isPrime, &data_array[ind]);
    //pthread_join(thread_array[ind],NULL);
    //printf("Thread %d found %d\n",ind,data_array[ind].isprime);
  }
  for (ind = 0; ind < n_threads; ind++)
  {
    pthread_join(thread_array[ind],NULL);
  }
  for (ind = 0; ind < n_threads; ind++)
  {
    //printf("data_array[%d] = %d\n",ind,data_array[ind].isprime);
    if (data_array[ind].isprime == 0)
    {
      //close_threads(thread_array, n_threads, data_array);
      return_value = 0;
    }
  }
  close_threads(thread_array, n_threads,data_array);
  //free(thread_array);
  //free(data_array);
  //printf("return value %d\n",return_value);
  return return_value;
}

void close_threads(pthread_t * thread_array, int num_threads, Data * data_array)
{
//   int ind;
//   for (ind = 0; ind < num_threads; ind++)
//   {
//     pthread_join(thread_array[ind],NULL);
//   }
  free(thread_array);
  free(data_array);
  return;
}
  
void * isPrime(void * ptr)
{
  //printf("in is prime\n");
  Data * data = (Data *) ptr;
  data -> isprime = 1; 
  if (data -> value == 3 || data -> value == 2 || data -> value == 1)
    return NULL;
  if (data -> value % 2 == 0)
  {
    //printf("test");
    data -> isprime = 0;
    return NULL;
  }
  
  if (data -> start < 3)
    data -> start = 3;
  
  int ind;
  for (ind = data -> start; ind < data -> end; ind++)
  {
    if (data -> value % ind == 0)
    {
      //printf("Found Even when testing %d\n",ind);
      data -> isprime = 0;
      return NULL;
    }
  }
  
  return NULL;
}
  
  


