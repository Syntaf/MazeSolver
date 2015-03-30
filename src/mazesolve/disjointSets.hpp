#ifndef DISJOINTSETS_H_
#define DISJOINTSETS_H_

class disjointSets {
    public:
        // Constructor ensures set size is no less than 10, and if less than 10 it will
        //      Internally set it to 10 anyways. Also allocates space for the ranks and
        //      links arrays as well as initializing them to their respective start values
        disjointSets(int=10);

        // Free memory from links and ranks 
        ~disjointSets();

        // Function to sum up the total count of links that are not equal to the value
        //      Initialized to them at start up. Returns count
        int entries() const;

        // Tests whether any links have been made, if none made returns true
        bool isEmpty() const;

        // Display information on disjoint sets
        void printSets() const;

        // Joins two sets together using ranks, must ensure that the union be called on
        //      two sets. If so it will then join the two sets
        int setUnion(int, int);
        
        // Finds the head node of the set passed
        int setFind(int);
    private:
        int setSize;        // size of sets
        int *links;         // set links
        int *ranks;         // set ranks
};

#endif
