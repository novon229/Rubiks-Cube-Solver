#pragma once

using namespace std;
#include <string>
#include "enums.h"

#ifndef COLOR_MAPPER_H
#define COLOR_MAPPER_H

/*
	The optimal Rubik's cube solver is based on Singmaster 
*/
class ColorSingmaster {
public:


	// Returns whether or not the cube we have created is valid
	bool isCubeValid(int colorMap[6][9]) {
		// http://math.stackexchange.com/questions/127577/how-to-tell-if-a-rubiks-cube-is-solvable
		// http://www.math.harvard.edu/~jjchen/docs/Group%20Theory%20and%20the%20Rubik's%20Cube.pdf
		// 2/3 of these cases can actually be caught by checking two other conditions:
		// 1) Each cube must only have 9 of each colour
		// 2) The center colour of each cube must be unique and must appear once
		// We implement this simpler algorithm as a proof of concept.

		int colorCounts[6];
		int centerColors[6];

		for (int i = 0; i < 6; i++) {
			colorCounts[i] = 0;
			centerColors[i] = 1;
		}

		for (int face = 0; face < 6; face++) {
			for (int cube = 0; cube < 9; cube++) {
				int colorIndex = colorMap[face][cube];
				colorCounts[colorIndex - 1]++;

				// Exceeded the 9 color count rule
				if (colorCounts[colorIndex - 1] > 9)
					return false;

				// center cube
				// 0 1 2
				// 3 4 5
				// 6 7 8
				if (cube == 4) {
					centerColors[colorIndex - 1]--;
					if (centerColors[colorIndex - 1] == -1) {
						return false;
					}
				}
			}
		}
		return true;
	}

	char getSideNameByCenterColor(int colorId, int sides[6][9]) {
			// 0 1 2
			// 3 4 5
			// 7 8 9
			int CENTER = 4;

			// up, down, left, right, front, back
			string sideMap = "FRUBLD";
		
			for (int i = 0; i < 6; i++) {
			if (sides[i][CENTER] == colorId) {
				return sideMap.at(i);
			}
		}
	}

	string colorsToCubie(int one, int two, int three, int sides[6][9]) {
		string str = "";
		str += getSideNameByCenterColor(one, sides);
		str += getSideNameByCenterColor(two, sides);
		if (three != -1)
		 str += getSideNameByCenterColor(three, sides);
		return str;
		
	}

	// Singmaster input is based on popular notation; a simple index lookup can be used here.
	// http://www.cs.columbia.edu/~sedwards/classes/2013/4840/reports/RCS.pdf
	// Transformation is based on algorithm proposed in the above paper / report; since the format is almost
	// linearly mapped there are

	string getSingmasterStringFromColorMap(int colorMap[6][9]) {
		
		// 20 data points
		string data[20];
		
		// FRUBLD
		int* front = colorMap[0];
		int* right = colorMap[1];
		int* up = colorMap[2];
		int* back = colorMap[3];
		int* left = colorMap[4];
		int* down = colorMap[5];

		data[UF] = colorsToCubie(up[7], front[1], -1, colorMap);
		data[DF] = colorsToCubie(down[1], front[7], -1, colorMap);
		data[UB] = colorsToCubie(up[1], back[1], -1, colorMap);
		data[DB] = colorsToCubie(down[7], back[7], -1, colorMap);
		data[UR] = colorsToCubie(up[5], right[1], -1, colorMap);
		data[DR] = colorsToCubie(down[5], right[7], -1, colorMap);
		data[UL] = colorsToCubie(up[3], left[1], -1, colorMap);
		data[DL] = colorsToCubie(down[3], left[7], -1, colorMap);
		data[FR] = colorsToCubie(front[5], right[3], -1, colorMap);
		data[FL] = colorsToCubie(front[3], left[5], -1, colorMap);
		data[BR] = colorsToCubie(back[3], right[5], -1, colorMap);
		data[BL] = colorsToCubie(back[5], left[3], -1, colorMap);

		// Corner cubies
		data[UFR] = colorsToCubie(up[8], front[2], right[0], colorMap);
		data[UBL] = colorsToCubie(up[0], back[2], left[0], colorMap);
		data[DFL] = colorsToCubie(down[0], front[6], left[8], colorMap);
		data[DBR] = colorsToCubie(down[8], back[6], right[8], colorMap);
		data[DLB] = colorsToCubie(down[6], left[6], back[8], colorMap);
		data[DRF] = colorsToCubie(down[2], right[6], front[8], colorMap);
		data[URB] = colorsToCubie(up[2], right[2], back[0], colorMap);
		data[ULF] = colorsToCubie(up[6], left[2], front[0], colorMap);

		string bufferedTransform = "";

		for (string s : data) {
			bufferedTransform += s + " ";
		}

		// Remove the stray space (don't need it and the solver won't like it)
		bufferedTransform.pop_back();

		return bufferedTransform;
	}

private:
	
	// The singmaster order of a "solved" cube.
	int UF = 0;
	int UR = 1;
	int UB = 2;
	int UL = 3;
	int DF = 4;
	int DR = 5;
	int DB = 6;
	int DL = 7;
	int FR = 8;
	int FL = 9;
	int BR = 10;
	int BL = 11;

	int UFR = 12;
	int URB = 13;
	int UBL = 14;
	int ULF = 15;
	int DRF = 16;
	int DFL = 17;
	int DLB = 18;
	int DBR = 19;

};

#endif //COLOR_MAPPER_H