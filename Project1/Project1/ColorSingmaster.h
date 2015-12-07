#pragma once

using namespace std;
#include <string>

#ifndef COLOR_MAPPER_H
#define COLOR_MAPPER_H

/*
	The optimal Rubik's cube solver is based on Singmaster 
*/
class ColorSingmaster {
public:

	// Singmaster input is based on popular notation; a simple index lookup can be used here.
	// http://www.cs.columbia.edu/~sedwards/classes/2013/4840/reports/RCS.pdf
	// Transformation is based on algorithm proposed in the above paper / report; since the format is almost
	// linearly mapped there are

	string getSingmasterStringFromColorMap(int colorMap[6][9]) {
		string bufferedTransform = "";
		
		// Some notes here:
		
		// 1) We subtract 1 from each colour as we plan on normalizing our values from [1..6] and not from [0..5]
		// on the mapping. Therefore, we need to make sure they fix in the array indexed bounds


		// 4 is middle here, consider the following linear layout mapped to a 2D grid (3x3):

		// 0 1 2
		// 3 4 5
		// 6 7 8
		char centerColorPosition[6];
		for (int i = 0; i < 6; i++)
			centerColorPosition[colorMap[i][4] - 1] = CENTER_COLOR_POSITION[i];

		for (int i = 0; i < 12; i++)
		{
			char first =
				centerColorPosition[colorMap[SIDE_INDEX_1[i]][SIDE_INDEX_2[i]] - 1];
			char second =
				centerColorPosition[colorMap[SIDE_INDEX_3[i]][SIDE_INDEX_4[i]] - 1];
			bufferedTransform += first;
			bufferedTransform += second;
			bufferedTransform += " ";
		}

		for (int i = 0; i < 8; i++)
		{
			char first =
				centerColorPosition[colorMap[CORNER_INDEX_1[i]][CORNER_INDEX_2[i]] - 1];
			char second =
				centerColorPosition[colorMap[CORNER_INDEX_3[i]][CORNER_INDEX_4[i]] - 1];
			char third =
				centerColorPosition[colorMap[CORNER_INDEX_5[i]][CORNER_INDEX_6[i]] - 1];

			bufferedTransform += first;
			bufferedTransform += second;
			bufferedTransform += third;
			bufferedTransform += " ";
		}
		
		// Remove the stray space (don't need it and the solver won't like it)
		bufferedTransform.pop_back();

		return bufferedTransform;
	}

private:
	
	// Lookups provided by the above paper / report; explanation not provided so one will be provided here to illustrate understanding
	// of these tables (they are not unique and cannot be, therefore they have been copied as is as they are about as semantic as you
	// can get)

	// The Singmaster / Thistle notation indicates the cubes edges and sides by their location relative to a face (hence, FRUBLD).
	
	// This map essentially allows us to map a face letter to the cube of a certain center colour. See the first upper loop.
	// We need this information to be able to tell where we are overall in the faces.
	const char CENTER_COLOR_POSITION[6] = { 'F', 'R', 'U', 'B', 'L', 'D' };
	
	// These tables indicate the all possible permutations for co-ordinate pairs of a given side index.
	// Split into two groups (one for each pair making up the side defintion)

	// For example, consider the side pairs (face = 2, cube = 7)  and then face = 0 and cube = 1

	// 0 1 2
	// 3 4 5
	// 6 7 8

	// Note how 7 and 1 touch? They form the pair at those indexes, forming the tuple at the lookup table above.
	// If this was a "perfect" solve cube, then you would get UF, to picture this, consider the 2D plane mapped above
	// like so (U = Upper, and F = Forward). Notice how they "connect" at the bottom? We essentially return the faces that
	// "connect" at this point. For the solved cube, which we know from Michael Reid is:
	// UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
	// then the first tuple must be UF since they connect on the face axis (on a side, not a corner)
	
	// 0 1 2
	// 3 4 5
	// 6 7 8
	// ---------
	// 0 1 2
	// 3 4 5
	// 6 7 8

	const int SIDE_INDEX_1[12] = { 2,2,2,2,5,5,5,5,0,0,3,3 };
	const int SIDE_INDEX_2[12] = { 7,5,1,3,3,1,5,7,5,3,3,5 };

	const int SIDE_INDEX_3[12] = { 0,1,3,4,0,1,3,4,1,4,1,4 };
	const int SIDE_INDEX_4[12] = { 1,1,1,1,7,7,7,7,3,5,5,3 };


	// The process is identical for below, we just simply need more lookups. The same concept applies, however. 
	// Simply grab the tuples (Face2, Cube8) for the first character and then map out all the tuples against their
	// center cube colours. 

	const int CORNER_INDEX_1[8] = { 2,2,2,2,5,5,5,5 };
	const int CORNER_INDEX_2[8] = { 8,2,0,6,0,6,8,2 };

	const int CORNER_INDEX_3[8] = { 0,1,3,4,1,0,4,3 };
	const int CORNER_INDEX_4[8] = { 2,2,2,2,6,6,6,6 };
	
	const int CORNER_INDEX_5[8] = { 1,3,4,0,0,4,3,1 };
	const int CORNER_INDEX_6[8] = { 0,0,0,0,8,8,8,8 };

};

#endif //COLOR_MAPPER_H