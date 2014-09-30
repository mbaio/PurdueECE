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
    if (strcmp(argv[ind],"-v") == 0) { choice_v = 1; v_index = ind; }
	else if (strcmp(argv[ind],"-n") == 0) { choice_n = 1; n_index = ind; }
	else if (strcmp(argv[ind],"-q") == 0) { choice_q = 1; q_index = ind; }
  }


  
  FILE * fptr;
  char c = ' ';
  char line[125];
  int ind_line = 0;
  int line_number = 0;
  int found_pattern;
  int return_code;

  for (ind = 1; ind < argc - 1; ind++)
  {
	if (ind != v_index && ind != n_index && ind != q_index)
	{
      fptr = fopen(argv[ind], "r");
	  if (fptr == NULL)
	   {
		 fprintf(stderr,"Grep cannot open %s",argv[ind]);
	 	 return EXIT_FAILURE;
	   }

	   while ((c = fgetc(fptr)) != EOF)
	   {
		 c = ' ';
		 fseek(fptr,-1,SEEK_CUR);
		 while (c != '\n')
		 {
		   c = fgetc(fptr);

		   if (c != '\n') { 
		     line[ind_line] = c; 
		     ind_line++;
		   }
		 }
		 line[ind_line] = '\0';
		 line_number++;
		 ind_line = 0;

		 found_pattern = strstr(line,argv[argc - 1]);

		 if (choice_v && ! found_pattern)
		 {
			return_code = 0; //not sure about this
			if (! choice_q)
			{
				if (choice_n)
				{
					fprintf(stdout,"\n%d: %s",line_number,line);
				}
				else
				{
					fprintf(stdout,"\n%s",line);
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
					fprintf(stdout,"\n%d: %s",line_number,line);
				}
				else
				{
					fprintf(stdout,"\n%s",line);
				}
			}
		 }
		 if (feof(fptr)) { break; }
	  }
    }
  }
  
	


return EXIT_SUCCESS;
}

