#ifndef MAZEGEN_H_
#define MAZEGEN_H_

#include <string>

class mazeGen
{
    public:
        // Constructor assigns variables rows and cols to the parameters
        //      passed and sets the disjoint set size as well as calculates
        //      the amount of walls needed for the program. Most importantly
        //      the constructor will allocate the walls array
        mazeGen(int=5, int=5);

        // Destructor frees memeory allocated by the constructor inside the
        //      walls variable
        ~mazeGen();

        // Get function sets the value of param 1 & 2 to the corresponding
        //      rows and cols values. Constant as no values are to be changed
        void getSize(int &, int &) const;

        // Bread and butter functino of mazeGen. This function will randomize the 
        //      walls array (which was initially in order) and create a disjoint 
        //      set object. Then the function will loop through the disjoint set
        //      size and join any sets together by checking the union between the
        //      two. If they are not unioned then the disjoint set will join them.
        //      this ensures that the maze IS solvable!
        void generate();

        //  This will print all maze data into a file, which is this case in the maze
        //      itself. Opens a file defined at compile time and writes the maze to
        //      that given file.
        bool printMazeData(const std::string) const;

        // Simple function to print the maze to the console, very similar to printMazeData
        //      but instead uses cout as opposed to fstream
        void printMazeText() const;

        // The solver for this class, uses the A* implementation but does some very important
        //      data manipulation first. Once the maze is 'ready' to be passed the A* is called
        //      from astar.hpp and a string is returned containing the solved path to the end of
        //      the maze
        void findPath();

        // Takes the walls array and randomizes the array, needed for the creation of a solvable 
        //      maze through disjoint sets
        void randomize();
    private:
        int arrSize;    // size of disjoint sets object 
        int rows;       // amount of rows in maze
        int cols;       // amount of cols in maze
        int **walls;    // walls array for creation of maze
};

#endif
