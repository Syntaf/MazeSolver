#include <iostream>
#include <iomanip>
#include "disjointSets.h"

disjointSets::disjointSets(int param):
  setSize(param)
{
	//dont allow sets smaller than 10
  if(setSize < 10)
    setSize = 10;
  ranks = new int[setSize];
  links = new int[setSize];
  for(int i = 0; i < setSize; i++) {
    links[i] = -1;
    ranks[i] = 1;
  }
}

disjointSets::~disjointSets()
{
	//free memory
  if(links != NULL)
    delete [] links;
  if(ranks != NULL)
    delete [] ranks;
}

int disjointSets::entries() const
{
	//return amount of entires currently in data
	//structure, uses a simple loop to count
  int cnt = 0;
  for(int i = 0; i < setSize; i++) {
    if(links[i] != -1)
      cnt++;
  }
  return cnt;
}

bool disjointSets::isEmpty() const
{
	//checks if anything is inside the
	//data structure
  for(int i = 0; i < setSize; i++)
    if(links[i] != -1)
      return false;
  return true;
}

void disjointSets::printSets() const
{
	//format and print the set to console
  std::cout << std::right;
  std::cout << "index:   ";
  for(int i = 0; i < setSize; i++) {
    std::cout << std::setw(3) << i;
  }
  std::cout << "\nlinks:   ";
  for(int i = 0; i < setSize; i++) {
    std::cout << std::setw(3) << links[i];
  }
  std::cout << "\nranks:   ";
  for(int i = 0; i < setSize; i++) {
    std::cout << std::setw(3) << ranks[i];
  }
  std::cout << std::endl;
}

int disjointSets::setUnion(int s1, int s2)
{
	//join two sets together, using ranks
  int p, c;
  if(links[s1] != -1 || links[s2] != -1) {
    std::cout << "Union must be called on a set\n";
    return -100;
  }
  if(ranks[s1] > ranks[s2]) {
    p = s1;
    c = s2;
  } else {
    p = s2;
    c = s1;
  }
  links[c] = p;
  if(ranks[s1] == ranks[s2])
    ranks[p]++;
  return p;
}

int disjointSets::setFind(int p)
{
	//recursivly find p, return root
  if(links[p] == -1)
    return p;
  links[p] = setFind(links[p]);
  return links[p];
}
