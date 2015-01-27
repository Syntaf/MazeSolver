#ifndef MAZEGEN_H_
#define MAZEGEN_H_

#include <string>

class mazeGen
{
  public:
    mazeGen(int=5, int=5);
    ~mazeGen();
    void getSize(int &, int &) const;
    void generate();
    bool printMazeData(const std::string) const;
    void printMazeText() const;
    void randomize();
  private:
    int arrSize;
    int rows;
    int cols;
    int **walls;
};

#endif
