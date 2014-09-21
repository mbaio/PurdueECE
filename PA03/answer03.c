#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer03.h"

char * strcat_ex(char ** dest, int * n, const char * src)
{
    //Testing
	printf("Testing strcat_ex\n\nParameters: %s\t%d\t%s\n",*dest,(int)*n,src);
	
	size_t lendest = *dest == NULL ? 0 : strlen(*dest);
	size_t lensrc = strlen(src);

	if (*dest == NULL || *n <= lendest + lensrc + 1)
	  {
		*n =  1 + (2 * (lendest + lensrc)); 																	
		char * buffer = malloc(*n * sizeof (char));
	
	
	
		strcpy(buffer,*dest);
		
	    printf("buffer = %s\n",buffer);
		free(*dest);
		*dest = buffer;
		printf("dest = %s\n",*dest);
	  }
	strcat(*dest,src);


    

	//Testing
	printf("\nReturn string = %s\n",*dest);
	return *dest;


}

char ** explode(const char *str, const char *delims, int * arrLen)
{
  char * element =(char *) str;
  int length_return_array = 0;
  while ( *element != '\0')
  {  
  	if (strchr(delims, *element))
	{
	  length_array++;;
	}

	element++;
  }
  *arrLen = length_return_array + 1;

  // I think above is correct
  //
  char ** dest = malloc((*arrLen + 1) * sizeof(char *));

  int index_ = 0; // which word I will be accessing
  element = (char *)str; // set back to the start
  char * start = (char *)str; // where the search will start
  int length_word; // how many characters the word is

  while (index_ < *arrLen)
  {
	if (strchr(delims, *element))
	{
	  length_word =  element - start;
	  dest[index_] = malloc((length_word + 1) * sizeof(char)); // length + 1 because of delimitter
	  memcpy(dest[index_],start, length_word * sizeof(char));
	  dest[index_][length_word] = '\0'; // to finish that word
	  index_++; //go to the next word
	  start = start + length_word + 1;
	  element = start;
	 
	}

	element++;
  }

  if (*arrLen > 0)
  {
    dest[*arrLen] = malloc(1 * sizeof(char));
	dest[*arrLen][0] = '\0';
  }

  return dest;
  

}
char * implode(char ** strArr, int len, const char * glue)
{
return 0;
}

void sortStringArray(char ** arrString, int len)
{
}

void sortStringCharacters(char * str)
{
}

void destroyStringArray(char ** strArr, int len)
{
}


