#include "Maze2.h"
#include <iostream>
#include <cassert>

using namespace std;

// Vladislav Ignatov 3/19/2016

void Maze2::find_exit()
{
   // Use the BFS method to fill the array of predecessors
  Position nbr, current;
  direction d;
  
  M[start.row][start.col] = VISITED;
	Q.push(start);
  
  while(!Q.empty())
  {
   d = DOWN;
   current = Q.front();
   Q.pop();
    
   for (d = DOWN; d != NONE; d = next_direction(d))
	 {
    nbr = current.Neighbor(d);
    if(nbr == exitpos)
    {
     pred[nbr.row][nbr.col] = current;
     return;
    }
    
    if (M[nbr.row][nbr.col] == OPEN)
    {
     Q.push(nbr);
     pred[nbr.row][nbr.col] = current;
     M[nbr.row][nbr.col] = VISITED;
    }
    
   }
  }  
}


