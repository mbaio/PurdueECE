#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer03.h"
// did it go?

int comp(const void *, const void *);
int compC(const void *, const void *);

char * strcat_ex(char ** dest, int * n, const char * src)
{
    //Testing
	//printf("Testing strcat_ex\n\nParameters: %s\t%d\t%s\n",*dest,(int)*n,src);
	
	size_t lendest = 0;

	if (*dest != NULL)
	{
	 lendest = strlen(*dest);
	}

	size_t lensrc = strlen(src);

	if (*dest == NULL || *n <= lendest + lensrc + 1)
	  {
		*n =  1 + (2 * (lendest + lensrc)); 																	
		char * buffer = malloc(*n * sizeof (char));
	    *buffer = '\0';

	   // if (buffer == NULL)
	//	{
//		return 0;
//		}

		if (*dest != NULL)
		{
		strcpy(buffer,*dest);
		}

	    //printf("buffer = %s\n",buffer);
		free(*dest);
		*dest = buffer;

		//printf("dest = %s\n",*dest);
	  }

	
	strcat(*dest,src);


    

	//Testing
	//printf("\nReturn string = %s\n",*dest);
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
	  length_return_array++;;
	}

	element++;
  }
  *arrLen = length_return_array + 1;

  // I think above is correct
  //
  char ** dest = malloc((*arrLen + 1) * sizeof(char *));

  int ind = 0; // which word I will be accessing
  element = (char *)str; // set back to the start
  char * start = (char *)str; // where the search will start
  int length_word; // how many characters the word is without delimiter

  while (ind < *arrLen)
  {
	if (strchr(delims, *element))
	{
	  length_word =  element - start;
	  dest[ind] = malloc((length_word + 1) * sizeof(char)); // length + 1 because of delimitter
	  memcpy(dest[ind],start, (length_word) * sizeof(char));
	  dest[ind][length_word] = '\0'; // to finish that word
	 
	 
      ind++; //go to the next word
	  start = start + length_word + 1;
	  element = start - 1;
	 
	}

	element++;
  }

  //if (*arrLen > 0)
 // {
  //  dest[*arrLen + 1] = malloc(1 * sizeof(char));
//	dest[*arrLen + 1][0] = '\0';
 // }
  

  return dest;
  

}
char * implode(char ** strArr, int len, const char * glue)
{
  int ind = 0;
  int len_return = 0;
  int n = 1;

  for (ind = 0; ind < len; ind++)
  {
    len_return += strlen(strArr[ind]) + strlen(glue);

  }

  len_return -= strlen(glue);


  char * str_return = NULL;

  for (ind = 0; ind < len; ind++)
  {
    strcat_ex(&str_return,&n,strArr[ind]);
	// add if for last glue
	if ( ind != len - 1)
	{
	strcat_ex(&str_return,&n,glue);
	}

  }

  char * nullstring = "\0";

  strcat_ex(&str_return,&n,nullstring);

  

  
/*
  int ind;
  char * str_return = NULL;
  int str_length;

  for (ind = 0; ind < len - 1; ind++)
  {
    str_return = strcat_ex(&str_return,&str_length,strArr[ind]);
	str_return = strcat_ex(&str_return,&str_length,glue);
  }

  str_return = strcat_ex(&str_return,&str_length, strArr[len-1]);
*/




return str_return;
}


int comp(const void * first, const void * second)
{
  const char ** add_first = (const char **) first;
  const char ** add_second = (const char **) second;

  return strcmp(*add_first, *add_second);

}



void sortStringArray(char ** arrString, int len)
{
  qsort(arrString, len, sizeof(char *), comp);
  return;

}

int compC(const void * first, const void * second)
{
  const char * point_first = (char *) first;
  const char * point_second = (char *) second;

  return(* point_first - * point_second);


}

void sortStringCharacters(char * str)
{
  int length_str = strlen(str);
  qsort(str,length_str,sizeof(char),compC);
  return;
}

void destroyStringArray(char ** strArr, int len)
{
  int ind = 0;

  if (strArr == NULL)
  {
  return;
  }

  for (ind = 0; ind < len; ind++)
  {
    free(strArr[ind]);
  }

  free(strArr);
  return;

}


