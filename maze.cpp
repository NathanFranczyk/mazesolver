/* Your code here! */
#include "maze.h"
#include <iostream>
using namespace std;
SquareMaze::SquareMaze(){
  mazepath = DisjointSets();
  mazewidth = 0;
  mazeheight = 0;
}

void SquareMaze::makeMaze(int width, int height){

  //DisjointSets mazepath;
  mazepath.addelements(width*height);//make a disjointset for the possible paths;
  mazewidth = width;
  mazeheight = height;

//  vector<std::pair<bool,bool>> walls;

  for(int i = 0; i < width;i++){
    for(int j = 0; j < height; j++){
      walls.push_back(std::make_pair(1,1));
      //mazemap.insert(j * mazeheight + i);
      //walls[j*width + i].first = 1;
    //  walls[j*width+ i].second = 1;
      //make all of the walls up;
    }
  }


  int vectorit = 0;
  int randomnum = 0;
  int wallbreakcount = 0;
  int wallcount = (int)walls.size();
  while(wallbreakcount < wallcount -1){
    vectorit = rand() % (width * height);
    randomnum = (rand()) % 2; //if one, delete right wall, delete right wall

    if(vectorit+1 < width * height && randomnum && (mazepath.find(vectorit+1) != mazepath.find(vectorit)) && (vectorit+1) % width != 0 ){ //del right
      //random right or down wall selection cond. check if next box is in the set. make sure not on right wall
    //  mazemap[vectorit+1] = vectorit;
      walls[vectorit].second = 0;
      mazepath.setunion(vectorit+1,vectorit); //walls[0] represents beginning of maze
      wallbreakcount++;
    }
    else if( !randomnum &&  vectorit < (width * (height-1)) ){
      if(mazepath.find(vectorit+width) != mazepath.find(vectorit) ){
      //check if next box is in the set. make sure not on down wall
    //  mazemap[vectorit +width] = vectorit ;
      walls[vectorit].first = 0; //delete down
      mazepath.setunion(vectorit+width,vectorit);
      wallbreakcount++;
    }}
    //vectorit++;
    //vectorit = (vectorit) % ((int) walls.size()-1) ;



}//continue until one winding corridor

  return;



}


bool SquareMaze::canTravel	(	int 	x, int 	y, int 	dir )		const{
  int rowmajcoord = y*mazewidth +  x;
  if(y > mazeheight || x > mazewidth){
    return false;
  }
  if(dir==0){
    if(walls[rowmajcoord].second == 0){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir == 1){
    if(walls[rowmajcoord].first ==0){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir == 2){
    if( walls[rowmajcoord-1].second == 0 ){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir ==3){
    if(walls[rowmajcoord-mazewidth].first == 0){
      return true;
    }
    else{
      return false;
    }
  }


  return false;
}


void SquareMaze::setWall	(	int x,int 	y,int 	dir,bool 	exists )	{
  if(y > mazeheight || x >mazewidth || x < 0 || y < 0){
    return;
  }
  if(dir == 0){
  walls[y*mazewidth + x].second = exists;
  }
  if(dir == 1 ){
    walls[y*mazewidth +x].first = exists;
  }
  return;
}

vector<int> SquareMaze::solveMaze(){
  int curpos;
  //vector<int> visited;
  //vector<int> directions;
  mazesol.clear();
  queue<int> cell;
  vector<int> path;
  vector<int> distances;
  vector<int> retpath;
  for(int i = 0; i < mazewidth*mazeheight; i++){
    path.push_back(-1);
    distances.push_back(0);
    //negative direction means unvisited;
  }
  int dir = 0;

  //Do a BST
  //right zero
  //down one//left 2 up 3

    cell.push(0);
    int curcel;
    int curx;
    int cury;
  while(!cell.empty()){
    curcel = cell.front();
    curx = curcel % mazewidth;
    cury  = curcel / mazewidth;
    if(curcel+1 % mazewidth  != 0){ //TRY A RIGHT MOVE
        if(canTravel(curx,cury,0) && distances[curcel+1] == 0){
          distances[curcel+1] = distances[curcel] + 1;
          cell.push(curcel + 1 );
          path[curcel+1] = 0; //this is how i got to this cell. I took a right
        }
    }
    if(curcel < mazewidth*(mazeheight-1) ){ //TRY A DOWN MOVE
        if(canTravel(curx,cury,1) && distances[curcel+mazewidth] == 0){
          distances[curcel+mazewidth] = distances[curcel]+1;
          cell.push(curcel + mazewidth);
          path[curcel+mazewidth] = 1;//this is how i got to this cell. I took a down
        }
    }
    if(curcel %mazewidth != 0){ // TRY A LEFT MOVE
        if(canTravel(curx,cury,2) && distances[curcel-1] == 0){
          distances[curcel-1] = distances[curcel] +1;
          cell.push(curcel-1);
          path[curcel-1] = 2;
        }
    }
    if(curcel >= mazewidth){ //TRY A UP MOVE
        if(canTravel(curx,cury,3) && distances[curcel-mazewidth] == 0){
          distances[curcel-mazewidth] = distances[curcel] +1;
          cell.push(curcel-mazewidth);
          path[curcel-mazewidth] = 3;
        }
    }
    cell.pop();
  }
  int j = 0;
  int maxdist = 0;
  int bottom = mazewidth* (mazeheight-1);
  for(int i = 0; i < mazewidth; i++){
    if(distances[bottom+i] > maxdist){
      maxdist = distances[bottom+i];
      j = i;
    }
  }//gets index of exit box;
  exit = bottom + j;
  curcel = exit;
  for(int i = 0; i< maxdist; i++){
    mazesol.push_back(-1);
    retpath.push_back(-1);
  }
  int i = maxdist;
  while(curcel!=0){
    if(path[curcel] == 0){
      mazesol[i-1] = 0;
      curcel = curcel-1;
      retpath[i-1] = 0;
    }
    else if(path[curcel] ==1){
      mazesol[i-1] = 1;
      curcel=curcel-mazewidth;
      retpath[i-1] = 1;
    }
    else if(path[curcel] == 2){
      mazesol[i-1] = 2;
      curcel=curcel+1;
      retpath[i-1] = 2;
    }
    else if(path[curcel] == 3){
      mazesol[i-1] = 3;
      curcel = curcel+mazewidth;
      retpath[i-1] = 3;
    }
    i--;
  }
  return retpath;

}


PNG * SquareMaze::drawMaze	(		)	const{
  PNG* newpng = new PNG(mazewidth*10 +1, mazeheight*10 +1);
  int x = 0;
  int y = 0;
  for(int i = 0; i < (int)mazewidth*10; i ++){
    if(i >0 && i < 10)
      continue;
    ((*newpng)(i,0))->red = 0;
    ((*newpng)(i,0))->green = 0;
    ((*newpng)(i,0))->blue = 0;
//*((*newpng)(i,0)).alpha = 0;
  }
  for(int y = 0; y < (int)mazeheight*10;y ++){
    ((*newpng)(0,y))->red = 0;
    ((*newpng)(0,y))->green = 0;
    ((*newpng)(0,y))->blue = 0;
  //  *((*newpng)(0,y)).alpha = 0;
  }
  for(int i = 0; i < (int)walls.size(); i++){
    x = i % mazewidth;
    y = (i - x) / mazeheight;

    if(walls[i].first == 1){//down wall there
      for(int j = 0; j <= 10; j++){
      ((*newpng)(x*10+j,(y+1)*10))-> red = 0;
      ((*newpng)(x*10+j,(y+1)*10))-> green = 0;
      ((*newpng)(x*10+j,(y+1)*10))-> blue = 0;
      }
    }
    if(walls[i].second == 1){ //right wall there
      for(int j = 0; j <= 10; j++){
        ((*newpng)((x+1)*10,y*10+j))-> red = 0;
        ((*newpng)((x+1)*10,y*10+j))-> green = 0;
        ((*newpng)((x+1)*10,y*10+j))-> blue = 0;
        //*((*newpng)(x*10+j,y*10+j)). alpha= 0;
      }

    }
  }
  ((*newpng)((mazewidth*10),mazeheight*10))-> red = 0;
  ((*newpng)((mazewidth*10),mazeheight*10))-> green = 0;
  ((*newpng)((mazewidth*10),mazeheight*10))-> blue = 0;
  return newpng;
}

PNG * SquareMaze::drawMazeWithSolution	(		)	{

  vector<int> thismazesol = solveMaze();
  walls[exit].first = 0; //opens the exit for the maze
  PNG* mazesolpic = drawMaze();




  int curpos = 0;
  int x = 0;
  int y = 0;
  for(int i = 0; i < (int) thismazesol.size();i++){

      x = curpos % mazewidth;
      y = curpos / mazewidth;
      if(thismazesol[i] == 0){
        for(int j = 0; j <= 10; j++){
          ((*mazesolpic)(x*10 +j +5,y*10 +5))-> red = 255;
          ((*mazesolpic)(x*10 +j +5,y*10 +5))-> green = 0;
          ((*mazesolpic)(x*10 +j +5,y*10 +5))-> blue = 0;
          //  ((*mazesolpic)(x*10 +j +5,y*10 +5))-> alpha = 0;
          //cout<<"right"<<endl;
        }
        curpos++;
      }
      else if(thismazesol[i] == 1){
        for(int j = 0; j <=10; j++){
          ((*mazesolpic)(x*10 +5,y*10 +j +5))-> red = 255;
          ((*mazesolpic)(x*10 +5,y*10 +j +5))-> blue = 0;
          ((*mazesolpic)(x*10 +5,y*10 +j +5))-> green = 0;
        }
        curpos+=mazewidth;
      }
      else if(thismazesol[i] == 2){
        for(int j = 10; j >= 0; j--){
          ((*mazesolpic)(x*10 -j +5,y*10 +5))-> red = 255;
          ((*mazesolpic)(x*10 -j +5,y*10 +5))-> green = 0;
          ((*mazesolpic)(x*10 -j +5,y*10 +5))-> blue = 0;
        }
        curpos--;
      }
      else if(thismazesol[i] == 3){
        for (int j = 10 ; j>= 0 ;j--){
            ((*mazesolpic)(x*10 +5,y*10 -j +5))-> red = 255;
            ((*mazesolpic)(x*10 +5,y*10 -j +5))-> green = 0;
            ((*mazesolpic)(x*10 +5,y*10 -j +5))-> blue = 0;
        }
        curpos-=mazewidth;
      }
  }
  (*mazesolpic)(0,mazeheight*10 +1)->red = 0;
  (*mazesolpic)(0,mazeheight*10 +1)->green = 0;
  (*mazesolpic)(0,mazeheight*10 +1)->blue = 0;
  return mazesolpic;
}




  //~SquareMaze();
  /*
  mazewidth = width;
  mazeheight = height;
  maze.addelements(width*height);
  //creates n disjoint elements in vector
  //this is an empty maze

  for(int i = 0; i < width;i++){
    for(int j = 0; j < height; j++){
      walls[j*width + i].first = 1;
      walls[j*width+ i].second = 1;
      //make all of the walls up;
    }
  }
  int major = 0;
  while(maze.elems.size()!= 1){
    if(maze.find(major) == -1 ) {//empty set

    }
  }

  //First of the pair is the down
  //Second of the pair is the right walls

  int randomnum = 0;
  int vectorit = 0;
  while(walls.size() > vectorit){
    randomnum = rand() % 2; //if one, delete right wall, left, delete right wall
    if(randomnum){ //del right
      walls[vectorit].second = 0;
    }
    else{
      walls[vectorit].first = 0; //delete down
    }
    vectorit ++;
  }
*/
