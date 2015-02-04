//  Main program for testing

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <Python.h>

#include "config.h"
#include "mazeGen.hpp"

using namespace std;

const char * SCRIPT = "pySolve.py";

void parseInput(std::string input, int& row, int& col);

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
	string	stars, bars, dashes;
	string	fName = "mazeDataFile.txt";
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";
	bool	doPrint=false;

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
		std::cout << "done, generating maze...\n";
		obj.generate();
		std::cout << "done, creating data file...\n";
		obj.printMazeData(fName);
		std::cout << "done, calling python solver...\n";
        Py_Initialize();
            pName = PyUnicode_FromString(SCRIPT);
            pModule = PyImport_Import(pName);
            Py_DECREF(pName);

            if(pModule != NULL) {
                pFunc = PyObject_GetAttrString(pModule, "test");

                if(pFunc && PyCallable_Check(pFunc)) {
                    pArgs = PyTuple_New(1);
                    pValue = PyUnicode_FromString("data.out");
                    if(!pValue) {
                        Py_DECREF(pArgs);
                        Py_DECREF(pModule);
                        std::cout << "Cannot convert args...\n";
                        return -1;
                    }
                    PyTuple_SetItem(pArgs, 0, pValue);
                    Py_DECREF(pArgs);
                    if(pValue != NULL) {
                        std::cout << "Done...\n";
                        Py_DECREF(pValue);
                    } else {
                        Py_DECREF(pFunc);
                        Py_DECREF(pModule);
                        PyErr_Print();
                        std::cout << "Call failed\n";
                        return -1;
                    }
                } else {
                    if(PyErr_Occurred())
                        PyErr_Print();
                    std::cout << "Cannot find function " << SCRIPT << "...\n";
                }
                Py_XDECREF(pFunc);
                Py_DECREF(pModule);
            } else {
                PyErr_Print();
                std::cout << "Failed to load...\n";
                return -1;
            }
        Py_Finalize();
		std::cout << "done";
		if(doPrint){
			std::cout << ", printing solution...\n\n";
			obj.printMazeText();
		}else
			std::cout << "...\n";
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
