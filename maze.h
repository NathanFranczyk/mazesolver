/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "dsets.h"
#include  "png.h"
#include <queue>
#include <map>
using std::vector;
using std::map;
using std::queue;

class SquareMaze{
public:
  SquareMaze();
  //~SquareMaze();
  // clearmaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();
  //bool canTravel(int x, int y, int dir) const;
  //void setWall(int x, int y, int dir, bool exists);
  //vector<int> solveMaze();
  //PNG* drawMaze() const;
  //PNG* drawMazeWithSolution();
  int exit;
  vector<std::pair<bool, bool>> walls;
  //map<int, int> mazemap;
//private:
  DisjointSets mazepath;
  int mazewidth;
  int mazeheight;
  vector<int> mazesol;


};

#endif
