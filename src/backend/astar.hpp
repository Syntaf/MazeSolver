//astar.hpp
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

void printMap(std::vector<std::vector<int> > &map)
{
    for(int r = 0; r < map.size(); r++) {
        for(int c = 0; c < map[0].size(); c++) {
            std::cout << map[r][c];
        }
        std::cout << std::endl;
    }
}

const int dir=4;
static int dx[dir] = {1, 0, -1, 0};
static int dy[dir] = {0, 1, 0, -1};

class node
{
	public:

  	    node(int xp, int yp, int d, int p):
            xPos(xp),
			yPos(yp),
			level(d),
			priority(p)
		{}

		int getxPos() const {return xPos;}
		int getyPos() const {return yPos;}
		int getLevel() const {return level;}
		int getPriority() const {return priority;}

		void updatePriority(const int &xDest, const int &yDest);
		void nextLevel(const int &i);								//give better priority to going straight instead of diagonal
		const int &estimate(const int &xDest, const int &yDest);	//estimate function for the remaining distance to the goal

	private:
		int xPos;		//x position
		int yPos;		//y position
		int level;		//total distance already traveled to reach node
		int priority;	//priority = level + remaining distance estimate

};

void node::updatePriority(const int &xDest, const int &yDest)
{
	priority = level + estimate(xDest, yDest) * 10;
}

void node::nextLevel(const int &i)
{
	level += i % 2 == 0 ? 10 : 14;
}

const int& node::estimate(const int& xDest, const int& yDest)
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	d = static_cast<int>(sqrt(xd * xd + yd * yd));

	return d;
}

//for determining priority of queue
bool operator<(const node &a, const node &b)
{
    return a.getPriority() > b.getPriority();
}
namespace AStar {
    //A-star algorithm
    //returns a string of direction digits
    std::string findPath( const int &xStart, const int &yStart,
                     const int xFinish, const int &yFinish,
                     std::vector< std::vector<int>> map)
    {
	    //shortcut for size of array entered
        const int n = map.size();
        const int m = map[0].size();
	    //arrays used for A-star algorithm
        std::vector<std::vector<int> > closed_nodes_map(n, std::vector<int>(m));
        std::vector<std::vector<int> > open_nodes_map(n, std::vector<int>(m));
        std::vector<std::vector<int> > dir_map(n, std::vector<int>(m));

	    //other variables needed during algorithm
        std::priority_queue<node> pq[2];
        int pqi=0;
        node* n0;
        node* m0;
        int i, j, x, y, xdx, ydy;
        char c;

	    //set all node maps to zero
        for(y = 0; y < m; y++) {
            for(x = 0; x < n; x++) { 
                dir_map[x][y] = 0;
                closed_nodes_map[x][y] = 0;
                open_nodes_map[x][y] = 0;
            }
        }
        x = 0; y = 0;
	    //create start node and push into list of open nodes
        n0 = new node(xStart, yStart, 0, 0);
        n0->updatePriority(xFinish, yFinish);
        pq[pqi].push(*n0);
        open_nodes_map[x][y] = n0->getPriority(); //mark on map
	    //run through priority queue
        while(!pq[pqi].empty()) {
		    //get the current node w/ highest priority
		    // from list of open nodes
            n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                          pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		    //shortcuts
            x = n0->getxPos();
            y = n0->getyPos();

		    //remove node from open list
            pq[pqi].pop();
            open_nodes_map[x][y] = 0;
		    //mark node as closed
            closed_nodes_map[x][y] = 1;

		    //quit searching when the goal state is reached
            if(x == xFinish && y == yFinish) {
			    //generate path from finish to start by
			    //following the directions
                std::string path="";
                while(!(x == xStart && y == yStart)) {
                    j = dir_map[x][y];
                    c = '0' + (j + dir / 2) % dir;
                    path = c + path;
                    x += dx[j];
                    y += dy[j];
                }
			    //garbage collection
                delete n0;
			    //empty lower leftover nodes
                while(!pq[pqi].empty())
                    pq[pqi].pop();
                return path;
            }

		    //generate modes in all possible directions
            for(i = 0; i < dir; i++) {
			    //more shortcuts
                xdx = x + dx[i];
                ydy = y + dy[i];


                if(!(xdx < 0 || xdx > n-1 || ydy < 0 || ydy > m-1 ||
				     map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1)) {
				    //create child node
                    m0 = new node( xdx, ydy, n0->getLevel(),
                            n0->getPriority());
                    m0->nextLevel(i);
                    m0->updatePriority(xFinish, yFinish);

				    //if not in open list, add into that
                    if(open_nodes_map[xdx][ydy] == 0) {
                        open_nodes_map[xdx][ydy] = m0->getPriority();
                        pq[pqi].push(*m0);
					    //mark its parent node direction
                        dir_map[xdx][ydy]=(i + dir / 2) % dir;
                    }else if(open_nodes_map[xdx][ydy] > m0->getPriority()) {
					    //update node priority
                        open_nodes_map[xdx][ydy] = m0->getPriority();
					    //update parent direction info
                        dir_map[xdx][ydy] = (i + dir / 2) % dir;

					    //replace the node by emplacing one pq
					    //to the other one except the node to be
					    //replaced will be ignored and the new node
					    //will be pushed instead
                        while(!(pq[pqi].top().getxPos() == xdx &&
                                pq[pqi].top().getyPos() == ydy)) {
                            pq[1-pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
					    //remove wanted node
                        pq[pqi].pop();

					    //empty the larger size pq to the smaller one
                        if(pq[pqi].size() > pq[1- pqi].size())
                            pqi = 1 - pqi;
                        while(!pq[pqi].empty()) {
                            pq[1-pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
                        pqi=1-pqi;
					    //add better node instead
                        pq[pqi].push(*m0);
                    }
                    else
                        delete m0;
                }
            }
            delete n0;
        }
        return "";
    }

    std::vector<std::vector<int> > makeReadyMap(const std::vector<std::vector<char> >& map)
    {
        std::vector<std::vector<int> > resmap(map.size());
        for(int r = 0; r < map.size(); r++) {
            for(int c = 0; c < map[0].size(); c++) {
                if(map[r][c] != ' ') {
                    resmap[r].push_back(1);
                }else{
                    resmap[r].push_back(0);
                }
            }
        }
        
        return resmap;
    }

}


