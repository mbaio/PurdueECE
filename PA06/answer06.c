#include "answer06.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int next_space(char **, char, int, int, int, int *);
int find_start(char **,int);
void print_directions2(char, int);
void recursion_func(char, char **, int,int,int,int);

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
  
  /*int x = 3;
  int y = 0;
  int next;
  int ind;
  for (ind = 0; ind < 5; ind++)
  {
    next = next_space(maze,'S',w,h,x,&y);
    y++;
  }
  free(maze[0]);
  free(maze[1]);
  free(maze[2]);
  free(maze[3]);
  free(maze[4]);
  free(maze);
  return (0);
  */
  
  
  print_directions(maze,w,h);
  
  free(maze[0]);
  free(maze[1]);
  free(maze[2]);
  free(maze[3]);
  free(maze[4]);
  free(maze);
  
  return(0);
}
void print_directions2(char direction,int spaces)
{
  printf("\n%c %d",direction,spaces);
}

void print_directions(char ** maze,int w,int h)
{
  int start = find_start(maze,w);
  char direction = 'S';
  recursion_func(direction,maze,w,h,start,0);
}

void recursion_func(char direction,char ** maze,int w,int h,int x, int y)
{
  sleep(1);
  int spaces = 0;
  int next;
 
  do {
    
    next = next_space(maze,direction,w,h,x,&y);
    if (next == 1)
    { break; }
    spaces++;
    if (direction == 'N') { y--; }
    if (direction == 'E') { x++; }
    if (direction == 'S') { y++; }
    if (direction == 'W') { x--; }
    
  } while (next == 0);
  if (next == 1)
  {
    
    printf("\n-----FOUND END-----");
    printf("\nAt found end: [y][x] = [%d][%d]",y,x);
    printf("\n%s\n%s\n%s\n%s\n%s\n",maze[0],maze[1],maze[2],maze[3],maze[4]);
    print_directions2(direction,spaces);
    printf("\n");
    if (direction == 'N') { direction == 'S'; y += spaces; }
    if (direction == 'E') { direction == 'W'; x -= spaces; }
    if (direction == 'S') { direction == 'N'; y -= spaces; }
    if (direction == 'W') { direction == 'E'; x += spaces; }
    printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
    print_directions2(direction,spaces);
    printf("\n\n\n\n\n");
  }
  if (next == 2)
  {
    
    printf("\n------FOUND JUNCTION-----");
    printf("\nAt found junction: [y][x] = [%d][%d]",y,x);
    print_directions2(direction,spaces);
    printf("\n\n\n");
    if (maze[y-1][x] != '.' && maze[y-1][x] != 'X') {recursion_func('N',maze,w,h,x,y); }
    if (maze[y][x+1] != '.' && maze[y][x+1] != 'X') {recursion_func('E',maze,w,h,x,y); }
    if (maze[y+1][x] != '.' && maze[y+1][x] != 'X') {recursion_func('S',maze,w,h,x,y); }
    if (maze[y][x-1] != '.' && maze[y][x-1] != 'X') {recursion_func('W',maze,w,h,x,y); }
  }
  
    
  
}

int next_space(char ** maze, char direction, int w, int h, int x, int * y) // returns 1 if next space is end of path, 0 if it is okay, 3 if found end, and 2 if it is a junction
{
  printf("\nmaze[y+1][x] = %c, y = %d, x = %d, current = %c",maze[*y+1][x],*y,x,maze[*y][x]);
  if (maze[*y][x] != 'X')
  {
    maze[*y][x] = '.';
  }
  if (direction == 'N' && (maze[*y-1][x+1] == ' ' || maze[*y-1][x-1] == ' ')) { printf("\nReturned 2"); return 2; }
  if (direction == 'E' && (maze[*y+1][x+1] == ' ' || maze[*y-1][x+1] == ' ')) { printf("\nReturned 2"); return 2; }
  if (direction == 'S' && (maze[*y+1][x+1] == ' ' || maze[*y+1][x-1] == ' ')) { printf("\nReturned 2"); return 2; }
  if (direction == 'W' && (maze[*y-1][x-1] == ' ' || maze[*y+1][x-1] == ' ')) { printf("\nReturned 2"); return 2; }
 
  
  if (direction == 'S' && (maze[*y+1][x] == ' ' && (*y+1 == h)))
  {
    maze[*y+1][x] = '.';
    printf("\nReturned 1");
    return 1;
  }
  if (direction == 'N' && (maze[*y-1][x] == 'X' || maze[*y-1][x] == '.'))
  {
    printf("\nReturned 1");
    return 1;
  }
  if (direction == 'E' && (maze[*y][x+1] == 'X' || maze[*y][x+1] == '.'))
  {
    printf("\nReturned 1");
    return 1;
  }
  if (direction == 'S' && (maze[*y+1][x] == 'X' || maze[*y+1][x] == '.')) 
  {
    printf("\nReturned 1");
    return 1;
  }
  if (direction == 'W' && (maze[*y][x-1] == 'X' || maze[*y][x-1] == '.'))
  {
    printf("\nReturned 1");
    return 1;
  }
  
  
 printf("\nReturned 0");
  return 0;
}

int find_start(char ** maze,int w)
{
  int ind;
  for (ind = 0;ind < w; ind++)
  {
    if (maze[0][ind] == ' ')
    {
      return(ind);
    }
  }
  return EXIT_FAILURE;
}
