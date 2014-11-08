//  Main program for testing

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <sstream>
#include <time.h>

#include "config.h"
#include "mazeGen.hpp"
#include "cls.hpp"

using namespace std;

void parseInput(std::string input, int& row, int& col);

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	string	stars, bars, dashes;
	string	fName;
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";
	bool	doPrint=false;

	//clear screen;
	system("cls");
	cout << "Maze Generator" << unbold << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Check argument

	if (argc == 2){
		if (string(argv[1]) == "-p"){
			doPrint = true;
			std::cout << "Console print enabled\n";
		}
	}else{
		char ans;
		std::cout << "Console print is disabled by default( -p cmd arg ), Enable?(Y/N): ";
		std::cin >> ans;
		if(toupper(ans) == 'Y'){
			doPrint = true;
			std::cout << "Console print enabled\n";
		}else{
			std::cout << "Console print disabled\n";
		}
	}
	std::cin.ignore(256, '\n');
	std::cout << "\n\n------------------------------------------------------------------\n";
// ------------------------------------------------------------------
//  Begin loop
	int rows, cols;
	std::string input;
	while(true){
		std::cout << "Enter the number of ROWS and COLS(return to exit): ";
		std::getline(cin, input);
		if(input == "")
			break;
		parseInput(input, rows, cols);
		//ask for input until user gets it right
		if(rows < 5 || cols < 5){
			while(true) {
				rows < 5 ? std::cout << "Rows cannot be less than 5" : std::cout << "Cols cannot be less than 5";
				std::cout << ". Renter ROWS followed by the number of COLS(e.g. 5 15): ";
				std::cin >> rows >> cols;
				if(rows >= 5 && cols >= 5)
					break;
			}
		}
		std::cout << "\ncreating maze...\n";
		mazeGen obj(rows, cols);
		std::cout << "generating maze...\n";
		obj.generate();
		std::cout << "generating done";
		if(doPrint){
			std::cout << ", printing...\n\n";
			obj.printMazeText();
		}else
			std::cout << "...\n";

		std::cout << "\ndone, creating data file...\n";
		fName = "mazeFile.txt";
		obj.printMazeData(fName);
	}
// *****************************************************************
//  All done.
	std::cout << "\nexiting...\n";
	return 0;
}

void parseInput(std::string input, int& row, int& col)
{
	std::stringstream ss(input);
	ss >> row >> col;
}