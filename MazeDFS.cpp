#include "Maze1.h"
#include <iostream>
#include <cassert>

using namespace std;

// vladislav ignatov 3/10/2016

Maze1::~Maze1()
{
  for (int i = 0; i < size; i++){
		delete[] M[i];
	}
	delete[] M;

}

void Maze1::find_exit()
// Use the DFS method to fill the path stack with the exit path Positions
// If there is no path to the exit, then after execution of this function
// the stack path should be empty
// This function does no input and no output
{
  // FILL IN THE CODE FOR THIS METHOD
  Position nbr, current;
  direction d;
  
  //cout << '(' << current.row << ',' << current.col << ')';
  current = nbr = start;
	M[current.row][current.col] = VISITED;
	path.push(start);
 
 while(!(path.empty())){
 //for (int x = 1; x < 5000; x++){
 if (path.empty()){
          return;
				}
		for (d = DOWN; d != NONE; d = next_direction(d))
		{
			nbr = current.Neighbor(d);
			if (M[nbr.row][nbr.col] == OPEN)
			{
				if (nbr == exitpos){
					path.push(nbr);
          return;
				}
				else{
					M[nbr.row][nbr.col] = VISITED;
					path.push(nbr);
					current = path.top();
                  
					break;
				}
			}
		}
    if (d == NONE){
					path.pop();
					current = path.top();
          
          d = DOWN;
          
				}
	}
}
 
