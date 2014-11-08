#ifndef DISJOINTSETS_H_
#define DISJOINTSETS_H_

class disjointSets {
  public:
    disjointSets(int=10);
    ~disjointSets();
    int entries() const;
    bool isEmpty() const;
    void printSets() const;
    int setUnion(int, int);
    int setFind(int);
  private:
    int setSize;
    int *links;
    int *ranks;
};

#endif
