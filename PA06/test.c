#include "answer06.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int next_space(char **, char, int, int, int, int *,int *);
int find_start(char **,int);
void print_directions2(char, int);
int recursion_func(char, char **, int,int,int,int);

int main()
{
   
  char ** maze = malloc(10 * sizeof(char *));
  maze[0] = malloc(11 * sizeof(char));
  maze[1] = malloc(11 * sizeof(char));
  maze[2] = malloc(11 * sizeof(char));
  maze[3] = malloc(11 * sizeof(char));
  maze[4] = malloc(11 * sizeof(char));
  maze[5] = malloc(11 * sizeof(char));
  maze[6] = malloc(11 * sizeof(char));
  maze[7] = malloc(11 * sizeof(char));
  maze[8] = malloc(11 * sizeof(char));
  maze[9] = malloc(11 * sizeof(char));
		   //0123456789
  strcpy(maze[0],"XXXXX XXXX");
  strcpy(maze[1],"XXXXX XX X");
  strcpy(maze[2],"XX    XX X");
  strcpy(maze[3],"XX XXXXX X");
  strcpy(maze[4],"XX       X");
  strcpy(maze[5],"XX XX XX X");
  strcpy(maze[6],"XX XXXXX X");
  strcpy(maze[7],"X  XX    X");
  strcpy(maze[8],"X XXX XXXX");
  strcpy(maze[9],"XXXXX XXXX");
  
 
  int w = 10;
  int h = 10;
  

  
  
  print_directions(maze,w,h);
  
  free(maze[0]);
  free(maze[1]);
  free(maze[2]);
  free(maze[3]);
  free(maze[4]);
  free(maze[5]);
  free(maze[6]);
  free(maze[7]);
  free(maze[8]);
  free(maze[9]);
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
  recursion_func(direction,maze,w-1,h-1,start,0);
}

int recursion_func(char direction,char ** maze,int w,int h,int x, int y)
{
  //sleep(1);
  int spaces = 0;
  int next;
  int answer;
 
  do {
    //printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",maze[0],maze[1],maze[2],maze[3],maze[4],maze[5],maze[6],maze[7],maze[8],maze[9]);
    next = next_space(maze,direction,w,h,x,&y,&spaces);
    //printf("\nSpaces = %d",spaces);
    if (next == 3) {spaces++;}
    if (next == 1 || next == 3)
    { break; }
    spaces++;
    if (direction == 'N') { y--; }
    if (direction == 'E') { x++; }
    if (direction == 'S') { y++; }
    if (direction == 'W') { x--; }
    
  } while (next == 0);
  if (next == 1 || next == 3)
  {
    
    //printf("\n-----FOUND END-----");
    //printf("\nAt found end: [y][x] = [%d][%d]",y,x);
    //printf("\n%s\n%s\n%s\n%s\n%s\n",maze[0],maze[1],maze[2],maze[3],maze[4]);
    print_directions2(direction,spaces);
    //printf("\n");
    while (1){
    if (direction == 'N') { 
      
      y += spaces;
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('S',spaces);
      break; }
    if (direction == 'E') { 
      
      x -= spaces;
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('W',spaces);
      break; }
    if (direction == 'S') { 
      
      y -= spaces; 
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('N',spaces);
      break; }
    if (direction == 'W') { 
      
      x += spaces; 
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('E',spaces);
      break; }
    }
    
    //printf("\n\n\n\n\n");
  }
  if (next == 2)
  {
    
    //printf("\n------FOUND JUNCTION-----");
    //printf("\nAt found junction: [y][x] = [%d][%d]",y,x);
    print_directions2(direction,spaces);
    //printf("\n\n\n");
    if (maze[y-1][x] != '.' && maze[y-1][x] != 'X') {answer = recursion_func('N',maze,w,h,x,y); }//y += answer;}//printf("\nS %d",answer); }
    if (maze[y][x+1] != '.' && maze[y][x+1] != 'X') {answer = recursion_func('E',maze,w,h,x,y); }//x -= answer;}//printf("\nW %d",answer);}
    if (maze[y+1][x] != '.' && maze[y+1][x] != 'X') {answer = recursion_func('S',maze,w,h,x,y); }//y -= answer;} //printf("\nN %d",answer);}
    if (maze[y][x-1] != '.' && maze[y][x-1] != 'X') {answer = recursion_func('W',maze,w,h,x,y); }//x += answer;}//printf("\nE %d",answer);}
    while (1){
    if (direction == 'N') { 
      
      y += spaces;
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('S',spaces);
      break; }
    if (direction == 'E') { 
      
      x -= spaces;
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('W',spaces);
      break; }
    if (direction == 'S') { 
      
      y -= spaces; 
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('N',spaces);
      break; }
    if (direction == 'W') { 
      
      x += spaces; 
      //printf("\nMoving back to previous junction: [y][x] = [%d][%d]",y,x);
      print_directions2('E',spaces);
      break; }
    }
    
  }
  
    
 answer = spaces; 
}

int next_space(char ** maze, char direction, int w, int h, int x, int * y, int * spaces) // returns 1 if next space is end of path, 0 if it is okay, 3 if found end, and 2 if it is a junction
{
  
  if (maze[*y][x] != 'X')
  {
    maze[*y][x] = '.';
  }
  if (direction == 'N' && (maze[*y-1][x+1] == ' ' || maze[*y-1][x-1] == ' ')) {  return 2; }
  if (direction == 'E' && (maze[*y+1][x+1] == ' ' || maze[*y-1][x+1] == ' ')) {  return 2; }
  if (direction == 'S' && (maze[*y+1][x+1] == ' ' || maze[*y+1][x-1] == ' ')) {  return 2; }
  if (direction == 'W' && (maze[*y-1][x-1] == ' ' || maze[*y+1][x-1] == ' ')) {  return 2; }
 
  
  if (direction == 'S' && (maze[*y+1][x] == ' ' && (*y+1 == h)))
  {
    maze[*y+1][x] = '.';
    *spaces++;
    
    return 3;
  }
  if (direction == 'N' && (maze[*y-1][x] == 'X' || maze[*y-1][x] == '.'))
  {
    
    return 1;
  }
  if (direction == 'E' && (maze[*y][x+1] == 'X' || maze[*y][x+1] == '.'))
  {
    
    return 1;
  }
  if (direction == 'S' && (maze[*y+1][x] == 'X' || maze[*y+1][x] == '.')) 
  {
    
    return 1;
  }
  if (direction == 'W' && (maze[*y][x-1] == 'X' || maze[*y][x-1] == '.'))
  {
    
    return 1;
  }
  
  

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
