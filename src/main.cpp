//  Main program for testing

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <sstream>
#include <time.h>

#include "config.h"
#include "mazeGen.hpp"

using namespace std;

bool parseInput(std::string input, int& row, int& col);

int main(int argc, char *argv[])
{
    // always writes to "mazeDataFile.txt"
	const string fName = "mazeDataFile.txt";
	bool doPrint = false;

	cout << "Maze Generator v" << VERSION_MAJOR << "." << VERSION_MINOR << endl;
	cout << endl;

    // shortcut to enable printing
	if (argc == 2){
		if (string(argv[1]) == "-p"){
			doPrint = true;
			std::cout << "Console print enabled\n";
		}
	}else{
        // give the user another chance to enable console print
		char ans;
		std::cout << "Console print is disabled by default( -p cmd arg ), Enable?(Y/N): ";
		std::cin >> ans;
		if(toupper(ans) == 'Y'){
			doPrint = true;
			std::cout << "Console print enabled\n";
		}else if(toupper(ans) == 'N'){
			std::cout << "Console print disabled\n";
		}else
            std::cout << "Unrecognized input... disabling console print\n";
	}
    // ignore the line feed read in by CIN so our first loop doesn't read a \n and exit right away
	std::cin.ignore(256, '\n');
	std::cout << "\n\n------------------------------------------------------------------\n";

	int rows, cols;
	std::string input;
    // loop indefintely
	while(true){
        // parse user input
		std::cout << "Enter the number of ROWS and COLS(return to exit): ";
		std::getline(cin, input);
		if(input == "")
			break;
		if(!parseInput(input, rows, cols)) {
            std::cout << "unrecognized input... exiting\n";
            break;
        }
		if(rows < 5 || cols < 5){
			while(true) {
				rows < 5 ? std::cout << "Rows cannot be less than 5" : std::cout << "Cols cannot be less than 5";
				std::cout << ". Renter ROWS followed by the number of COLS(e.g. 5 15): ";
                std::getline(cin, input);
				if(!parseInput(input, rows, cols))
                    continue;
				if(rows >= 5 && cols >= 5)
					break;
			}
		}
        // create maze
		std::cout << "\ncreating maze...\n";
		mazeGen obj(rows, cols);
		std::cout << "done, generating maze...\n";
        // generate solvable maze
		obj.generate();
        // if console print enabled print blank maze
        if(doPrint){
            std::cout << std::endl;
            obj.printMazeText();
            std::cout << std::endl;
        }
        // create file
		std::cout << "done, creating data file...\n";
		obj.printMazeData(fName);
        // read file and print solution
		std::cout << "done, printing solution...\n\n";
	    obj.findPath();
       std::cout << std::endl;
	}
	return 0;
}

bool parseInput(std::string input, int& row, int& col)
{
	std::stringstream ss(input);
	ss >> row >> col;
    return !ss.fail();
}
