#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  int index = 1;
  
  if (argc == 1)
  {
  printf("\n");
  return EXIT_SUCCESS;
  }

  
  while (index < argc)
  {

   printf("%s ",argv[index]);
   index++;
  }




 return EXIT_SUCCESS;
}
