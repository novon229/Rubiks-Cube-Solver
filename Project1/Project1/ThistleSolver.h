#pragma once
//
/**
* Vaughan Hilts: <HILT2740@mylaurier.ca>
* CP 411 - Graphics Programming
* ID: 120892740
*
* Based on the work of http://tomas.rokicki.com/cubecontest/jaap.txt
*/
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Cube.h"

using namespace std;

#ifndef RUBIK_THISTLESOLVER_H
#define RUBIK_THISTLESOLVER_H


class ThistleSolver {

private:

	int* tables[8];
	int tableSizes[8] = { 1, 4096, 6561, 4096, 256, 1536, 13824, 576 };

	int* moveamount;
	int* move;

	Cube* workingCube;

public:

	ThistleSolver() {
		// Fetch the tables
		// http://www.jaapsch.net/puzzles/thistle.htm
		// Precomputed tables make for less dull code... generating using algorithm on that page to save runtime performance
		// just like back in the old graphics days ;)
		loadTables();
	}


	Cube* getCubeFromInput(string s) {
		return new Cube(s);
	}

	/**
	* Gets a solution string for the given color input given.
	*/
	string getSolutionFor(string colorInput) {

		// Create memory slots
		move = new int[52]; // God's Number is technically 20 but we are far from supreme.
		moveamount = new int[52];
		string moveStr = "";

		workingCube = getCubeFromInput(colorInput);

		// Four phases
		for (int stage = 0; stage < 4; stage++) {
			printf("\nStage: %d\n", stage);

			int move = 0;
			bool status = true;
			while (status) {
				status = !depthSearch(move, 0, 9, stage);
				if (status) {
					move++;
				}
			}

			// Move set... loop did some funny buisness
			printf("released: %d\n", move);

			for (int v = 0; v < move; v++) {
				moveStr += "FBRLUD"[this->move[v]]; // hack to the FBRLUD
				moveStr += toString(moveamount[v]); // hack to the moveStr
				moveStr += " ";
			}
		}

		// Erase the last nasty character.. unless the cube is solver, then don't worry about it
		if(moveStr.length() != 0)
			moveStr.pop_back();

		return moveStr;
	}


	bool checkTableForMoreMoves(Cube* c, int movesLeft, int stage) {
		for (int i = 0; i < 2; i++) {

			int* table_grab = tables[stage * 2 + i];

			// Each pruning stage has 2 tables (8/2 = 4 phases)
			int index = c->getTablePosition(stage * 2 + i);
			int value = table_grab[index];


			// printf("Position: %d: |  Value: %d\n", index, value);

			// The table contains information for each cube configuration about how to solve it
			int neededMoves = value - 1;
			if (neededMoves > movesLeft) {
				// printf("Short circuitng...\n");
				return true;
			}
		}

		return false;
	}

	/**
	* Returns true if a solution was found, given the depth. Otherwise, returns
	*/
	bool depthSearch(int movesLeft, int movesCompleted, int lastMoveMade, int stage) {

		if (checkTableForMoreMoves(workingCube, movesLeft, stage)) {
			// printf("%d\n", movesLeft);
			return false;
		}

		if (movesLeft == 0) {
			return true;
		}

		// Not yet solved... attempt to solve each face
		for (int i = 6; i--;) {
			// do not repeat same face, nor do opposite after DLB.
			if (i - lastMoveMade && (i - lastMoveMade + 1 || i | 1)) {

				move[movesCompleted] = i;
				// printf("Move: %d\n", i);

				for (int j = 0; ++j<4;) {
					//do move and remember it
					workingCube->move(i);
					moveamount[movesCompleted] = j;
					//Check if phase only allows half moves of this face
					if ((j == 2 || i >= stage * 2) && depthSearch(movesLeft - 1, movesCompleted + 1, i, stage)) return true;
				}
				workingCube->move(i);
			}
		}             // Repeat move, just ignore


		return false;
	}


	template <typename T>
	string toString(T Number)
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	}

	void loadTables() {
		// Allocate enough memory for each table size
		for (int i = 0; i < 8; i++) {
			tables[i] = new int[tableSizes[i]];
		}

		// Load the table data
		std::ifstream input("table.dat");

		int currentTableIndex = -1;
		int k = 0;
		int* currentTable = NULL;

		for (std::string line; getline(input, line); )
		{
			if (line == "t") {
				// swap table to the next table
				currentTableIndex++;
				currentTable = tables[currentTableIndex];
				k = 0;
			}
			else {
				// import data into the table
				currentTable[k] = stoi(line);
				k++;
			}
		}
	}

};


#endif //RUBIK_THISTLESOLVER_H
