#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char ** argv)
{
  int ind;
  int choice_v = 0;
  int choice_n = 0;
  int choice_q = 0;
  int v_index = 0;
  int n_index = 0;
  int q_index = 0;




  for (ind = 1; ind < argc; ind++)
  {
    if (strcmp(argv[ind],"-v") == 0 || strcmp(argv[ind],"--invert-match") == 0)  { choice_v = 1; v_index = ind; }
	else if (strcmp(argv[ind],"-n") == 0 || strcmp(argv[ind],"--line-number") == 0) { choice_n = 1; n_index = ind; }
	else if (strcmp(argv[ind],"-q") == 0 || strcmp(argv[ind],"--quiet") == 0) { choice_q = 1; q_index = ind; }
	else if (strcmp(argv[ind],"--help") == 0) 
	
	{
	printf("\nUsage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.");
  return 1;

  }
  else if (argv[ind][0] == '-' && (argv[ind][1] != 'v' || argv[ind][1] != 'n' || argv[ind][1] != 'q'))
  {
    fprintf(stderr,"No such option");
	return 2;
  
  }
  }


  
  FILE * fptr = stdin;
  char line[2000];
  int line_number = 0;
  char * found_pattern = NULL;
  int return_code = 1;

	   while (fgets(line,2000,fptr))
	   {
		 line_number++;

		 found_pattern = strstr(line,argv[argc - 1]); //try no casts

		 if (choice_v && ! found_pattern)
		 {
			return_code = 0; //not sure about this
			if (! choice_q)
			{
				if (choice_n)
				{
					fprintf(stdout,"%d: %s",line_number,line);
				}
				else
				{
					fprintf(stdout,"%s",line);
				}
			}
		 }
		 if (! choice_v && found_pattern)
		 {
			return_code = 0; //not sure about this
			if (! choice_q)
			{
				if (choice_n)
				{
					fprintf(stdout,"%d: %s",line_number,line);
				}
				else
				{
					fprintf(stdout,"%s",line);
				}
			}
		 }
		 if (feof(fptr)) { break; }
	  }
    
  
 fclose(stdin); 
	
//printf("\nreturn_code = %d\n",return_code);

return return_code;
}

