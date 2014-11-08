#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "mazeGen.h"
#include "disjointSets.h"

bool comp (int *i, int *j) { return i[0] < j[0]; }

mazeGen::mazeGen(int t_rows, int t_cols):
  rows(t_rows),
  cols(t_cols)
{
  if(rows < 5)
    rows = 5;
  if(cols < 5)
    cols = 5;

  //the amount of walls needed
  int wallsCount = rows * (cols-1) + cols * (rows-1);
  //create class variable arrSize to save calculation time
	arrSize = wallsCount;
  int horiz = rows * (cols-1);

	//initialize each element of walls with an array (x,y)
  walls = new int*[wallsCount];
  for(int i = 0; i < wallsCount; i++){
    walls[i] = new int[2];
  }

	//place all horizonally connected walls into the array,
	//making sure edges do not connect with other edges on a
	//new row
  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols-1; c++){
      int s = r > 0 ? -1*r : 0;
      walls[r*cols+c+s][0] = r*cols+c;
      walls[r*cols+c+s][1] = r*cols+c+1;
    }
  }
	//place all vertically connected walls into the array,
	//make sure edges do not connect with other edges on a
	//new column
  for(int c = 0; c < cols; c++){
    for(int r = 0; r < rows-1; r++){
      int s = c > 0 ? -1*c : 0;
      walls[horiz+c*rows+r+s][0] = c+r*cols;
      walls[horiz+c*rows+r+s][1] = c+r*cols+cols;
    }
  }
}

mazeGen::~mazeGen()
{
	//free memory
  for(int i = 0; i < rows; i++){
    if(walls[i] != NULL)
      delete [] walls[i];
  }
  if(walls != NULL)
    delete [] walls;
}

void mazeGen::getSize(int & t_rows, int & t_cols) const
{
  t_rows = rows;
  t_cols = cols;
}

void mazeGen::generate()
{
	//randomize walls array
  randomize();
	//create disjoint set and loop through walls, if 
	//the wall is not connect to the next wall, destory
	//the wall with (-1,-1)
  disjointSets d(arrSize);
  for(int i = 0; i+1 < arrSize; i++){
    int s1 = d.setFind(walls[i][0]);
    int s2 = d.setFind(walls[i][1]);
    if(s1 != s2){
      d.setUnion(s1, s2);
      walls[i][0] = walls[i][1] = -1;
    }
  }
}

bool mazeGen::printMazeData(const std::string filename) const
{
	//open file and output contents of walls array, ONLY
	//write walls that are valid(not -1)
  std::ofstream outFile(filename.c_str());
  outFile << "ROWS " << rows << " COLS " << cols << std::endl;
  for(int i = 0; i < arrSize; i++)
    if(walls[i][0] != -1 && walls[i][1] != -1)
		outFile << "WALL " << walls[i][0] << " " << walls[i][1] << std::endl;
  outFile.close();
}

void mazeGen::printMazeText() const
{
	//print maze out in text form
	//print first row with one opening
	std::cout << "+  +";
	for(int i = 0; i < cols-1; i++)
		std::cout << "--+";
	std::cout << std::endl;

	//begin looking through every column and place a '|' when a wall appears
	for(int i = 1, r = 0; i < rows*2;r += (i-1) % 2, i++) {
		if(i % 2 == 0) {
			std::cout << "+";
			for(int j = 0; j < cols; j++) {
				bool fnd = false;
				for(int h = 0; h < arrSize; h++) {
					if(walls[h][0] == j+r*cols && walls[h][1] == j+r*cols+cols) {
						std::cout << "--+";
						fnd = true;
						break;
					}
				}
				if(!fnd)
					std::cout << "  +";
			}
		}else{
			std::cout << "|";
			for(int j = 0; j < cols-1; j++) {				
				bool fnd = false;
				for(int h = 0; h < arrSize; h++) {
					if(walls[h][0] == r*cols+j && walls[h][1] == r*cols+j+1) {
						std::cout << "  |";
						fnd = true;
						break;
					}
				}
				if(!fnd)
					std::cout << "   ";
			}
		}
		if(i % 2 != 0) {
			std::cout << "  |";
		}
		std::cout << std::endl;
	}

	//print out bottom bounding line
	for(int i = 0; i < cols-1; i++)
		std::cout << "+--";
	std::cout << "+  +";
	std::cout << std::endl;
}

void mazeGen::randomize()
{
	//the array so generate() wont have to do
	//anything special
  for(int i = arrSize-1;i > 0;i--){
    int j = rand() % (i+1);
		//swap
    int tmp = walls[i][0];
    int tmp2 = walls[i][1];

    walls[i][0] = walls[j][0];
    walls[i][1] = walls[j][1];

    walls[j][0] = tmp;
    walls[j][1] = tmp2;
  }

 }

