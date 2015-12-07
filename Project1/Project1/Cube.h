//
/**
* Vaughan Hilts: <HILT2740@mylaurier.ca>
* CP 411 - Graphics Programming
* ID: 120892740
*/
//

#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include <string.h>


using namespace std;

/*
* // http://loki.ist.unomaha.edu/~jtrimm/project/images/turnnotation.png

You need to make sure you understand the above to understand the notation used here.
All of the labels have been shortened to the first letter of each label in the enums below for brevity.
In all cases, the letters are not listed in any particular order, i.e: FRU is the same as FUR.

With this in mind, there's more detail below at: http://ruwix.com/the-rubiks-cube/notation/advanced/
*/


class Cube {
public:

	// Swap macro
	char TEMP;
	#define SWAP(a,b) TEMP=a;a=b;b=TEMP;


	char *positions = new char[20];
	char *orientations = new char[20];

	char *perm = "AIBJTMROCLDKSNQPEKFIMSPRGJHLNTOQAGCEMTNSBFDHORPQ";

	Cube() {
		// Reset the cube values
		for (int i = 0; i < 20; i++) {
			positions[i] = 0;
			orientations[i] = 0;
		}
	}

	Cube(string s) {

		string buf;
		string goodSoln[20];
		std::stringstream ss(s); // Insert the string into a stream

		int i = 0;
		while (ss >> buf) {
			goodSoln[i] = buf;
			i++;
		}

		int f;
		int j = 0;
		int k = 0;
		int pc;
		int mor;
		const char *faces = "RLFBUD";

		// Magic hash; http://tomas.rokicki.com/cubecontest/jaap.txt
		const char *bithash = "TdXhQaRbEFIJUZfijeYV";

		// ASCII lookup table for chatacter lookup => offset by the gap values
		const char *order = "AECGBFDHIJKLMSNTROQP";

		int CHAR_OFFSET = 65; // A

		int val[20];
		for (k = 0; k<20; k++) {
			val[k] = k<12 ? 2 : 3;
		}

		for (int i = 0; i < 20; i++) {
			// All zeroes
			f = pc = k = mor = 0;

			for (; f < val[i]; f++) {
				j = strchr(faces, goodSoln[i][f]) - faces;
				// keep track of principal facelet for orientation
				if (j > k) {
					k = j;
					mor = f;
				}
				//construct bit hash code
				pc += 1 << j;
			}
			// find which cubelet it belongs, i.e. the label for this piece
			for (f = 0; f < 20; f++)
				if (pc == bithash[f] - 64) break;

			positions[order[i] - CHAR_OFFSET] = f;
			orientations[order[i] - CHAR_OFFSET] = mor%val[i];
		}

		for (int i = 0; i < 20; i++) {
			printf("%d %d\n", positions[i], orientations[i]);

		}
	}

	/**
	* Mutates the state of the cube.
	* Thanks for Jaap for these below definitions
	*/
	void move(int move) {
		char *p = perm + 8 * move, i = 8;
		//cycle the edges
		cycle(positions, p);
		cycle(orientations, p);
		//cycle the corners
		cycle(positions, p + 4);
		cycle(orientations, p + 4);
		//twist corners if RLFB
		if (move < 4)
			for (; --i>3;) twist(p[i], i & 1);
		//flip edges if FB
		if (move < 2)
			for (i = 4; i--;) twist(p[i], 0);
	}

	// Cycles 4 pieces in array p, the piece indices given by a[0..3].
	void cycle(char*p, char*a) {
		SWAP(p[*a - 65], p[a[1] - 65]);
		SWAP(p[*a - 65], p[a[2] - 65]);
		SWAP(p[*a - 65], p[a[3] - 65]);
	}

	void twist(int i, int a) {
		
		// Recompute hash table here; we don't cache it
		int val[20];
		int k = 0;
		for (k = 0; k < 20; k++) {
			val[k] = k<12 ? 2 : 3;
		}

		// Hash values are passed in but offsetting is performed by simply subtracting away the ASCII base value
		// Which is A, or 65, giving you the normalized value.
		i -= 65;

		orientations[i] = (orientations[i] + a + 1) % val[i];
	}



	// Thank you for Dr. Kociembra and Jaap for this table
	// http://kociemba.org/cube.htm
	// Jaap originally wrote this table parser. Original annoations are left behind fofr posterity.

	int getTablePosition(int tableIndex) {
		int i = -1, n = 0;
		switch (tableIndex) {
			// case 0 does nothing so returns 0
		case 1://edgeflip
			   // 12 bits, set bit if edge is flipped
			for (; ++i<12;) n += orientations[i] << i;
			break;
		case 2://cornertwist
			   // get base 3 number of 8 digits - each digit is corner twist
			for (i = 20; --i>11;) n = n * 3 + orientations[i];
			break;
		case 3://middle edge choice
			   // 12 bits, set bit if edge belongs in Um middle slice
			for (; ++i<12;) n += (positions[i] & 8) ? (1 << i) : 0;
			break;
		case 4://ud slice choice
			   // 8 bits, set bit if UD edge belongs in Fm middle slice
			for (; ++i<8;) n += (positions[i] & 4) ? (1 << i) : 0;
			break;
		case 5://tetrad choice, twist and parity
			int corn[8], j, k, l, corn2[4];
			// 8 bits, set bit if corner belongs in second tetrad.
			// also separate pieces for twist/parity determination
			k = j = 0;
			for (; ++i<8;)
				if ((l = positions[i + 12] - 12) & 4) {
					corn[l] = k++;
					n += 1 << i;
				}
				else corn[j++] = l;
				//Find permutation of second tetrad after solving first
				for (i = 0; i<4; i++) corn2[i] = corn[4 + corn[i]];
				//Solve one piece of second tetrad
				for (; --i;) corn2[i] ^= corn2[0];

				// encode parity/tetrad twist
				n = n * 6 + corn2[1] * 2 - 2;
				if (corn2[3]<corn2[2])n++;
				break;
		case 6://two edge and one corner orbit, permutation
			n = permtonum(positions) * 576 + permtonum(positions + 4) * 24 + permtonum(positions + 12);
			break;
		case 7://one edge and one corner orbit, permutation
			n = permtonum(positions + 8) * 24 + permtonum(positions + 16);
			break;
		}
		return n;
	}

	// End Jaap port contribution

private:

	vector<vector<int>> moveTable = {
		{ 0, 8, 1, 9, 19, 12, 17, 14 }, // F
		{ 2, 11, 3, 10, 18, 13, 16, 15 }

		, // B
		{ 4, 10, 5, 8, 12, 18, 15, 17 }, // R
		{ 6, 9, 7, 11, 13, 19, 14, 16 }, // L
		{ 0, 6, 2, 4, 12, 19, 13, 18 }, // U
		{ 1, 5, 3, 7, 14, 17, 15, 16 }  // D
	};


	// convert permutation of 4 chars to a number in range 0..23
	// ported method
	int permtonum(char* p) {
		int n = 0;
		for (int a = 0; a<4; a++) {
			n *= 4 - a;
			for (int b = a; ++b<4; )
				if (p[b]<p[a]) n++;
		}
		return n;
	}


	void twistOrientations(int move) {
		auto mt = moveTable[move];
		//Corners: affected in the moves R,L,F,B.
		if (move<4) {
			// cubies on positions 5,7 get +2 (CCW rotation)
			orientations[mt[7]] = (orientations[mt[7]] + 2) % 3;
			orientations[mt[5]] = (orientations[mt[5]] + 2) % 3;
			// cubies on positions 4,6 get +1 (CW rotation)
			orientations[mt[6]] = (orientations[mt[6]] + 1) % 3;
			orientations[mt[4]] = (orientations[mt[4]] + 1) % 3;
		}
		//Edges: affected in the moves F,B
		if (move<2) {
			for (int i = 0; i < 4; i++) {
				//flip the edge
				orientations[mt[i]] = 1 - orientations[mt[i]];
			}
		}

	}

	void cyclePositions(int move) {
		auto mt = moveTable[0]; //move table for given move.
		int tmp;
		int tmp2;

		//edges
		tmp = positions[mt[3]];
		tmp2 = orientations[mt[3]]; //of course, we also need to update the orientations order accordingly
		for (int i = 3; i > 0; i--) {
			positions[mt[i]] = positions[mt[i - 1]];
			orientations[mt[i]] = orientations[mt[i - 1]];
		}
		positions[mt[0]] = tmp;
		orientations[mt[0]] = tmp2;

		//corners
		tmp = positions[mt[7]];
		tmp2 = orientations[mt[7]];
		for (int i = 7; i > 4; i--) {
			positions[mt[i]] = positions[mt[i - 1]];
			orientations[mt[i]] = orientations[mt[i - 1]];
		}
		positions[mt[4]] = tmp;
		orientations[mt[4]] = tmp2;
	}


	string colorsToCubie(int one, int two, int three, int sides[6][9]) {

		string str = "";
		str += getSideNameByCenterColor(one, sides);
		str += getSideNameByCenterColor(two, sides);
		if (three != -1)
			str += getSideNameByCenterColor(three, sides);

		return str;
	}


	char getSideNameByCenterColor(int colorId, int sides[6][9]) {

		// 0 1 2
		// 3 4 5
		// 7 8 9
		int CENTER = 4;

		// up, down, left, right, front, back
		string sideMap = "UDLRFB";

		for (int i = 0; i < 6; i++) {
			if (sides[i][CENTER] == colorId) {
				return sideMap.at(i);
			}
		}

	}

	int getNameIndex(string name) {
		string vals[] = {
			"UF", "DF", "UB", "DB", "UR", "DR", "UL", "DL", "FR", "FL", "BR", "BL",
			"UFR", "UBL", "DFL", "DBR", "DLB", "DRF", "URB", "ULF"
		};

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < name.length(); j++) {
				if (vals[i].find(name.at(j)) == string::npos)
					break;
				if (j + 1 == name.length()) {
					return i;
				}
			}
		}

		// Give up... failure
		return -1;

	}

	string getName(string name) {
		string vals[] = {
			"UF", "DF", "UB", "DB", "UR", "DR", "UL", "DL", "FR", "FL", "BR", "BL",
			"UFR", "UBL", "DFL", "DBR", "DLB", "DRF", "URB", "ULF"
		};

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < name.length(); j++) {
				if (vals[i].find(name.at(j)) == string::npos)
					break;
				if (j + 1 == name.length()) {
					return vals[i];
				}
			}
		}

		// Give up... failure
		return "";

	}


	int orientCube(int index, string name) {
		// corners have 3 possible orientations, egeds only 2.
		int modulu = index > 11 ? 3 : 2;

		int last = 0; //the last facelet index that was used to update this cubie's orientation.
		int orient = 0;
		for (int idx = 0; idx < modulu; idx++) {
			string face = name.at(idx) + "";
			/*
			* When coming to determine a cubie's orientation, we look at its facelets in the order given
			* by its location name. For example, if the UFL cubie is found at the UFR location, we will call it ULF.
			* We now look at the "highest rank" representative of the cubie. The ranking order is RLFBUD. So in our
			* example the highest rank of ULF is U. The orientation will be the index of U in the string "ULF", which is 0.
			*/
			int i = string("RLFBUD").find(face);
			if (i > last) {
				last = i;
				orient = idx;
			}
		}
		return orient;
	}

};

#endif //RUBIK_CUBE_H
