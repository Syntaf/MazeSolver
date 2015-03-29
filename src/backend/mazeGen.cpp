#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "astar.hpp"
#include "mazeGen.hpp"
#include "disjointSets.hpp"
 
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
  std::ofstream outFile(filename.c_str());
  if(!outFile.is_open())
    return false;
    
  outFile << "+  +";
    for(int i = 0; i < cols-1; i++)
        outFile << "--+";
    outFile << std::endl;

    //begin looking through every column and place a '|' when a wall appears
    for(int i = 1, r = 0; i < rows*2;r += (i-1) % 2, i++) {
        if(i % 2 == 0) {
            outFile << "+";
            for(int j = 0; j < cols; j++) {
                bool fnd = false;
                for(int h = 0; h < arrSize; h++) {
                    if(walls[h][0] == j+r*cols && walls[h][1] == j+r*cols+cols) {
                        outFile << "--+";
                        fnd = true;
                        break;
                    }
                }
                if(!fnd)
                    outFile << "  +";
            }
        }else{
            outFile << "|";
            for(int j = 0; j < cols-1; j++) {				
                bool fnd = false;
                for(int h = 0; h < arrSize; h++) {
                    if(walls[h][0] == r*cols+j && walls[h][1] == r*cols+j+1) {
                        outFile << "  |";
                        fnd = true;
                        break;
                    }
                }
                if(!fnd)
                    outFile << "   ";
            }
        }
        if(i % 2 != 0) {
            outFile << "  |";
        }
        outFile << std::endl;
    }

    //print out bottom bounding line
    for(int i = 0; i < cols-1; i++)
        outFile << "+--";
    outFile << "+  +";
    outFile << std::endl;
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

void mazeGen::findPath()
{
    // create vector for reading in file, 1 char = 1 block on maze
    std::vector< std::vector<char> > maze_map;
    typedef std::istreambuf_iterator<char> buf_iter;
    std::fstream file("mazeDataFile.txt");
    std::vector<char> tmp;                      // create a vector that we can use to create the boarders
    maze_map.push_back(tmp);                    // push back top wall, this will initially be empty
    tmp.push_back('|');                         // create left wall for each row
    for(buf_iter i(file), e; i != e; ++i) {     // loop file
        char c = *i;                            // get char
        if(c == '\n') {                         // if end of line, new row
            tmp.push_back('|');                 // create right wall
            maze_map.push_back(tmp);            // push row in
            tmp.clear();                        // clear tmp
            tmp.push_back('|');                 // re add new left wall
        } else {
            tmp.push_back(c);                   // push char into row
        }    
    }
    tmp.clear();                                // clear tmp
    std::fill_n(back_inserter(maze_map[0]), maze_map[1].size(), '-');
    std::fill_n(back_inserter(tmp), maze_map[1].size(), '-');
    maze_map.push_back(tmp);                    

    // call A* algorithm to determine most efficient path to end
    std::string route = AStar::findPath(2, 1, maze_map.size()-2, maze_map[0].size()-3, AStar::makeReadyMap(maze_map));
    
    //parse the string and print contents
    int x = 0;
    int y = 0;
    for(int i = 0; i < route.length(); i++) {
        char c = route[i];
        int j = atoi(&c);
        x = x + dx[j];
        y = y + dy[j];
        // 2 and 1 are our offsets since we started at 2 and 1
        maze_map[x+2][y+1] = 'x';
    }
    maze_map[1][2] = 'x';

    // print our solved map not including boarders
    for(int i = 1; i < maze_map.size()-1; i++) {
        for(int j = 1; j < maze_map[0].size()-1; j++) { 
            std::cout << maze_map[i][j];
        }
        std::cout << std::endl;
    }
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

