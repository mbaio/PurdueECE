#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer03.h"

// test again
char * strcat_ex(char ** dest, int * n, const char * src)
{
	if (*dest == NULL || *n < strlen(*dest) + strlen(src) + 1)
	{
	int size = 1 + 2 * (*n + strlen(src));
	char * buffer = malloc(size * sizeof (char));
	*n = size;
	strcpy(buffer,*dest);
	free(*dest);
	*dest = buffer;
	strcat(*dest,src);
	}
	else
	{
	char * buffer = malloc(*n * sizeof(char));
	strcpy(buffer,*dest);
	free(*dest);
	*dest = buffer;
	strcat(*dest,src);
	}

    return *dest;


}

char ** explode(const char *str, const char *delims, int * arrLen)
{
  int count = 0;
  int index;
  char * itr;
  char * start;

  for (index = 0; str[index] != '\0'; index++)
  {
    if (strchr(str[index],delims))
	{
	  if (count = 0)
	  {
	  int last = index;
	  }

	  count++;
    }
  }

  char ** dest = malloc(count * sizeof(char *));


  index = 0;

  while (*itr != '\0')
  {
    start = itr;
	if (strchr(*itr,delims))
	{
	  memcpy(dest[word],start,itr-start);
	  dest
	}
  

    itr++;
  }
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


