#include "answer06.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int next_space(char **, char, int, int, int, int);

int main()
{
   
  char ** maze = malloc(5 * sizeof(char *));
  maze[0] = malloc(6 * sizeof(char));
  maze[1] = malloc(6 * sizeof(char));
  maze[2] = malloc(6 * sizeof(char));
  maze[3] = malloc(6 * sizeof(char));
  maze[4] = malloc(6 * sizeof(char));
  
  strcpy(maze[0],"XXX X");
  strcpy(maze[1],"X   X");
  strcpy(maze[2],"X X X");
  strcpy(maze[3],"X X X");
  strcpy(maze[4],"XXX X");
  
  
 
  int w = 4;
  int h = 4;
  int x = 3;
  int y = 0;
  char direction = 'S';
  int ind;
  printf("\nbefore call");
  for (y = 0; y < 4; y++)
  {
    printf("\nresult = %d\n",next_space(maze,direction,w,h,x,y));
  }
  printf("\n%s\n%s\n%s\n%s\n%s\n",maze[0],maze[1],maze[2],maze[3],maze[4]);
  
  free(maze[0]);
  free(maze[1]);
  free(maze[2]);
  free(maze[3]);
  free(maze[4]);
  free(maze);
  
  return(0);
}
  

void print_directions(char ** maze,int w,int h)
{
  
  
  
  
}

int next_space(char ** maze, char direction, int w, int h, int x, int y) // returns 1 if next space is a ., , or X.  Also fills each space passed with a .
{
  printf("\nmaze[y+1][x] = %c, y = %d, x = %d, current = %c",maze[y+1][x],y,x,maze[y][x]);
  maze[y][x] = '.';
  if (direction == 'N' && (maze[y-1][x] == 'X' || maze[y-1][x] == '.' || maze[y-1][x] == ' ' && (y-1 == h || x == w || y-1 == 0 || x == 0)))
  {
    printf("\nin N");
    return 1;
  }
  if (direction == 'E' && (maze[y][x+1] == 'X' || maze[y][x+1] == '.' || maze[y][x+1] == ' ' && (y == h || x+1 == w || y == 0 || x+1 == 0)))
  {
    printf("\nin E");
    return 1;
  }
  if (direction == 'S' && (maze[y+1][x] == 'X') || (maze[y+1][x] == '.') || (maze[y+1][x] == ' ' && (y+1 == h || x == w || y+1 == 0 || x == 0)))
  {
    printf("\nin S");
    return 1;
  }
  if (direction == 'W' && (maze[y][x-1] == 'X' || maze[y][x-1] == '.' || maze[y][x-1] == ' ' && (y == h || x-1 == w || y == 0 || x-1 == 0)))
  {
    printf("\nin W");
    return 1;
  }
  
   
  return 0;
}
    
