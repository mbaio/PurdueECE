#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
  int arg_stdin = 0;
  int ind = 1;

  for (ind = 1; ind < argc; ind++)
  {
    if (strcmp(argv[ind],"--help") == 0)
	{
	  
		printf("\nUsage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\ncat-lite README   Print the file README to standard output.\ncat-lite f - g    Print f's contents, then standard input,\n                  then g's contents.\ncat-lite          Copy standard input to standard output.\n");

	

	return EXIT_SUCCESS;
	}
  }

  for (ind = 1; ind < argc; ind++)
  {
    if (strcmp(argv[ind],"-") == 0 )
	{
	  arg_stdin = ind;
	}
  }
  
  ind = 1;

  char c;
  FILE * fptr;
  for (ind = 1; ind < argc; ind++)
  {
    if (ind != arg_stdin)
	{
	  fptr = fopen(argv[ind],"r");
	  if (fptr == NULL)
      {
	    fprintf(stdout,"cat cannot open %s\n",argv[ind]);
	    return EXIT_FAILURE;
	  }
    
      while (! feof(fptr))
	  {
        c = fgetc(fptr);
	    if ((int) c >= 0 && (int) c <= 127)
	    {
	    fputc(c,stdout);
	    }

	  }


	  fclose(fptr);
	}
    else	 
	{
      char output[100];
	  fscanf(stdin,"%s",output);
	  fprintf(stdout,output);
	}
  }
  


 return EXIT_SUCCESS;
}
