//#include "cube_parser.cpp"
#include "ThistleSolver.h"
#include "ColorSingmaster.h";

#include <windows.h> // use proper includes for your system
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/Gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#include <string>



class cube {
public:
	double colours[6][3] = { { 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } };

	cube(void) {}
	cube(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2)
	{
		/* Setup cube vertex data. */
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = x1;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = x2;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = y1;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = y2;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = z1;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = z2;

		///* Enable a single OpenGL light. */
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		//glEnable(GL_LIGHT0);
		//glEnable(GL_LIGHTING);

		/* Use depth buffering for hidden surface elimination. */
		glEnable(GL_DEPTH_TEST);
	}
	void drawBox(void)
	{

		int i;
		for (i = 0; i < 6; i++) {
			glBegin(GL_QUADS);
			glColor3f(colours[i][0], colours[i][1], colours[i][2]);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
	}

	void setColours(double a, double b, double c, int face) {
		colours[face][0] = a;
		colours[face][1] = b;
		colours[face][2] = c;
	}


	double* getColours(int face) {
		double * arr = new double[3];
		arr[0] = colours[face][0];
		arr[1] = colours[face][1];
		arr[2] = colours[face][2];
		return arr;
	}
	void rotate(bool direction, int face, bool side) {
		GLfloat store[8][4];
		if (face == XSIDE) {
			if (side == NAT) {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (xMatrix[direction][0][0] * v[i][0]) + (xMatrix[direction][0][1] * v[i][1]) + (xMatrix[direction][0][2] * v[i][2]) + (xMatrix[direction][0][3] * 1);
					b = (xMatrix[direction][1][0] * v[i][0]) + (xMatrix[direction][1][1] * v[i][1]) + (xMatrix[direction][1][2] * v[i][2]) + (xMatrix[direction][1][3] * 1);
					c = (xMatrix[direction][2][0] * v[i][0]) + (xMatrix[direction][2][1] * v[i][1]) + (xMatrix[direction][2][2] * v[i][2]) + (xMatrix[direction][2][3] * 1);
					d = (xMatrix[direction][3][0] * v[i][0]) + (xMatrix[direction][3][1] * v[i][1]) + (xMatrix[direction][3][2] * v[i][2]) + (xMatrix[direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
			else {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (xMatrix[!direction][0][0] * v[i][0]) + (xMatrix[!direction][0][1] * v[i][1]) + (xMatrix[!direction][0][2] * v[i][2]) + (xMatrix[!direction][0][3] * 1);
					b = (xMatrix[!direction][1][0] * v[i][0]) + (xMatrix[!direction][1][1] * v[i][1]) + (xMatrix[!direction][1][2] * v[i][2]) + (xMatrix[!direction][1][3] * 1);
					c = (xMatrix[!direction][2][0] * v[i][0]) + (xMatrix[!direction][2][1] * v[i][1]) + (xMatrix[!direction][2][2] * v[i][2]) + (xMatrix[!direction][2][3] * 1);
					d = (xMatrix[!direction][3][0] * v[i][0]) + (xMatrix[!direction][3][1] * v[i][1]) + (xMatrix[!direction][3][2] * v[i][2]) + (xMatrix[!direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
		}
		else if (face == YSIDE) {
			if (side == NAT) {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (yMatrix[direction][0][0] * v[i][0]) + (yMatrix[direction][0][1] * v[i][1]) + (yMatrix[direction][0][2] * v[i][2]) + (yMatrix[direction][0][3] * 1);
					b = (yMatrix[direction][1][0] * v[i][0]) + (yMatrix[direction][1][1] * v[i][1]) + (yMatrix[direction][1][2] * v[i][2]) + (yMatrix[direction][1][3] * 1);
					c = (yMatrix[direction][2][0] * v[i][0]) + (yMatrix[direction][2][1] * v[i][1]) + (yMatrix[direction][2][2] * v[i][2]) + (yMatrix[direction][2][3] * 1);
					d = (yMatrix[direction][3][0] * v[i][0]) + (yMatrix[direction][3][1] * v[i][1]) + (yMatrix[direction][3][2] * v[i][2]) + (yMatrix[direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
			else {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (yMatrix[!direction][0][0] * v[i][0]) + (yMatrix[!direction][0][1] * v[i][1]) + (yMatrix[!direction][0][2] * v[i][2]) + (yMatrix[!direction][0][3] * 1);
					b = (yMatrix[!direction][1][0] * v[i][0]) + (yMatrix[!direction][1][1] * v[i][1]) + (yMatrix[!direction][1][2] * v[i][2]) + (yMatrix[!direction][1][3] * 1);
					c = (yMatrix[!direction][2][0] * v[i][0]) + (yMatrix[!direction][2][1] * v[i][1]) + (yMatrix[!direction][2][2] * v[i][2]) + (yMatrix[!direction][2][3] * 1);
					d = (yMatrix[!direction][3][0] * v[i][0]) + (yMatrix[!direction][3][1] * v[i][1]) + (yMatrix[!direction][3][2] * v[i][2]) + (yMatrix[!direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
		}
		else if (face == ZSIDE) {
			if (side == NAT) {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (zMatrix[direction][0][0] * v[i][0]) + (zMatrix[direction][0][1] * v[i][1]) + (zMatrix[direction][0][2] * v[i][2]) + (zMatrix[direction][0][3] * 1);
					b = (zMatrix[direction][1][0] * v[i][0]) + (zMatrix[direction][1][1] * v[i][1]) + (zMatrix[direction][1][2] * v[i][2]) + (zMatrix[direction][1][3] * 1);
					c = (zMatrix[direction][2][0] * v[i][0]) + (zMatrix[direction][2][1] * v[i][1]) + (zMatrix[direction][2][2] * v[i][2]) + (zMatrix[direction][2][3] * 1);
					d = (zMatrix[direction][3][0] * v[i][0]) + (zMatrix[direction][3][1] * v[i][1]) + (zMatrix[direction][3][2] * v[i][2]) + (zMatrix[direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
			else {
				for (int i = 0; i < 8; i++) {
					GLfloat a, b, c, d;

					a = (zMatrix[!direction][0][0] * v[i][0]) + (zMatrix[!direction][0][1] * v[i][1]) + (zMatrix[!direction][0][2] * v[i][2]) + (zMatrix[!direction][0][3] * 1);
					b = (zMatrix[!direction][1][0] * v[i][0]) + (zMatrix[!direction][1][1] * v[i][1]) + (zMatrix[!direction][1][2] * v[i][2]) + (zMatrix[!direction][1][3] * 1);
					c = (zMatrix[!direction][2][0] * v[i][0]) + (zMatrix[!direction][2][1] * v[i][1]) + (zMatrix[!direction][2][2] * v[i][2]) + (zMatrix[!direction][2][3] * 1);
					d = (zMatrix[!direction][3][0] * v[i][0]) + (zMatrix[!direction][3][1] * v[i][1]) + (zMatrix[!direction][3][2] * v[i][2]) + (zMatrix[!direction][3][3] * 1);

					store[i][0] = a;
					store[i][1] = b;
					store[i][2] = c;
					store[i][3] = d;
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				v[i][j] = store[i][j];
			}
		}
	}

private:
	bool NAT = 0;
	bool REV = 1;
	int XSIDE = 0;
	int YSIDE = 1;
	int ZSIDE = 2;

	GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
		{ -1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 1.0, 0.0, 0.0 },
		{ 0.0, -1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, -1.0 } };
	GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
		{ 0, 1, 2, 3 },{ 3, 2, 6, 7 },{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },{ 5, 6, 2, 1 },{ 7, 4, 0, 3 } };
	GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
	GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };  /* Red diffuse light. */
	GLfloat light_position[4] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */
	//the devision here is equal to frames. Unfortunately it wont let me set it.
	float theta = M_PI_2 / 32;
	float xMatrix[2][4][4] = {
		{ { 1, 0, 0, 0 },
		{ 0, cos(theta), -sin(theta), 0 },
		{ 0, sin(theta), cos(theta), 0 },
		{ 0, 0, 0, 1 } } ,

		{ { 1, 0, 0, 0 },
		{ 0, cos(theta), sin(theta), 0 },
		{ 0, -sin(theta), cos(theta), 0 },
		{ 0, 0, 0, 1 } }
	};
	float yMatrix[2][4][4] = {
		{ { cos(theta), 0, -sin(theta), 0 },
		{ 0, 1, 0, 0 },
		{ sin(theta), 0, cos(theta), 0 },
		{ 0, 0, 0, 1 } },

		{ { cos(theta), 0, sin(theta), 0 },
		{ 0, 1, 0, 0 },
		{ -sin(theta), 0, cos(theta), 0 },
		{ 0, 0, 0, 1 } }
	};
	float zMatrix[2][4][4] = {
		{ { cos(theta), sin(theta), 0, 0 },
		{ -sin(theta), cos(theta), 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 } },

		{ { cos(theta), -sin(theta), 0, 0 },
		{ sin(theta), cos(theta), 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 } }
	};
};



//========================================================================================================================================================================

bool CW = 0;
bool CCW = 1;
int XSIDE = 0; //left and right
int YSIDE = 1; //top and bottom
int ZSIDE = 2; //front and back
bool NAT = 0; //top, left, front
bool REV = 1; //bottom, right, back

cube * backTopLeft, * backTopMiddle, * backTopRight;
cube * backMiddleLeft, * backMiddleMiddle, * backMiddleRight;
cube * backBottomLeft, * backBottomMiddle, * backBottomRight;
cube * middleTopLeft, * middleTopMiddle, * middleTopRight;
cube * middleMiddleLeft, * middleMiddleMiddle, * middleMiddleRight;
cube * middleBottomLeft, * middleBottomMiddle, * middleBottomRight;
cube * frontTopLeft, * frontTopMiddle, * frontTopRight;
cube * frontMiddleLeft, * frontMiddleMiddle, * frontMiddleRight;
cube * frontBottomLeft, * frontBottomMiddle, * frontBottomRight;

cube * temp;

cube c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27;

int wait_time;
//this is stored as an integer but serves as a boolean to state if the solution is curretnly running or complete
int solution_boolean = 0;
int string_length;
//this tells the display function what tic of a 90 degree rotation it is on
int animation_tic_count = 0;
//this tells the display function what index of the rotate vector it should change 
int current_string_index = 0;
//this is a string for testing purposes that shows cube face rotations
std::string temporary_string = "";
//this is the vector for rotating the cube based on temporary string which will eventually be the solution
std::vector<std::string> rotate_vector;
//this is the number of tics to do one 90 degree rotation. It needs modified in the cube aswell
int FRAMES = 32;
//used to ensure the user has entered the correct number of each colour
int test_r, test_g, test_b, test_o, test_w, test_y;

double* get_colour_from_user_from_char() {
	/*1.0, 0.0, 0.0 is red
	0.0, 1.0, 0.0 is green
	0.0, 0.0, 1.0 is blue
	1.0, 0.5, 0.0 is orange
	1.0, 1.0, 1.0 is white
	1.0, 1.0, 0.0 is yellow*/
	double * current = new double[3];
	int user_input;
	int valid=0;
	while(valid == 0){
		valid = 1;
		std::cout << "enter the colour\n";
		std::cout << "1=red 2=green 3=blue 4=orange 5=white 6=yellow\n";
		std::cin >> user_input;
	if (user_input == 1) {
		current[0] = 1;
		current[1] = 0;
		current[2] = 0;
		test_r++;
	}
	else if (user_input == 2){

		current[0] = 0;
		current[1] = 1;
		current[2] = 0;
		test_g++;
	}
	else if (user_input == 3) {
		current[0] = 0;
		current[1] = 0;
		current[2] = 1;
		test_b++;

	}
	else if (user_input == 4){

		current[0] = 1;
		current[1] = 0.5;
		current[2] = 0;
		test_o++;

	}
	else if (user_input == 5) {
		current[0] = 1;
		current[1] = 1;
		current[2] = 1;
		test_w++;
	}
	else if (user_input == 6){
		current[0] = 1;
		current[1] = 1;
		current[2] = 0;
		test_y++;

	}
	else{
		std::cout << "invalid input\n";
		valid = 0;
		}
	}
	return current;
}

void
init(void)
{
	//initilize global
	wait_time = 25;
	//initilized the 27 individual cubes.
	c1 = cube(-0.9, -0.32, 0.32, 0.9, 0.9, 0.32);
	c2 = cube(-0.3, 0.3, 0.32, 0.9, 0.9, 0.32);
	c3 = cube(0.32, 0.9, 0.32, 0.9, 0.9, 0.32);
	c4 = cube(-0.9, -0.32, -0.3, 0.3, 0.9, 0.32);
	c5 = cube(-0.3, 0.3, -0.3, 0.3, 0.9, 0.32);
	c6 = cube(0.32, 0.9, -0.3, 0.3, 0.9, 0.32);
	c7 = cube(-0.9, -0.32, -0.9, -0.32, 0.9, 0.32);
	c8 = cube(-0.3, 0.3, -0.9, -0.32, 0.9, 0.32);
	c9 = cube(0.32, 0.9, -0.9, -0.32, 0.9, 0.32);
	c10 = cube(-0.9, -0.32, 0.32, 0.9, 0.3, -0.3);
	c11 = cube(-0.3, 0.3, 0.32, 0.9, 0.3, -0.3);
	c12 = cube(0.32, 0.9, 0.32, 0.9, 0.3, -0.3);
	c13 = cube(-0.9, -0.32, -0.3, 0.3, 0.3, -0.3);
	c27 = cube(-0.3, 0.3, -0.3, 0.3, 0.3, -0.3);
	c14 = cube(0.32, 0.9, -0.3, 0.3, 0.3, -0.3);
	c15 = cube(-0.9, -0.32, -0.9, -0.32, 0.3, -0.3);
	c16 = cube(-0.3, 0.3, -0.9, -0.32, 0.3, -0.3);
	c17 = cube(0.32, 0.9, -0.9, -0.32, 0.3, -0.3);
	c18 = cube(-0.9, -0.32, 0.32, 0.9, -0.32, -0.9);
	c19 = cube(-0.3, 0.3, 0.32, 0.9, -0.32, -0.9);
	c20 = cube(0.32, 0.9, 0.32, 0.9, -0.32, -0.9);
	c21 = cube(-0.9, -0.32, -0.3, 0.3, -0.32, -0.9);
	c22 = cube(-0.3, 0.3, -0.3, 0.3, -0.32, -0.9);
	c23 = cube(0.32, 0.9, -0.3, 0.3, -0.32, -0.9);
	c24 = cube(-0.9, -0.32, -0.9, -0.32, -0.32, -0.9);
	c25 = cube(-0.3, 0.3, -0.9, -0.32, -0.32, -0.9);
	c26 = cube(0.32, 0.9, -0.9, -0.32, -0.32, -0.9);

	
	int valid = 0;
	while(valid == 0){
		test_r = test_b = test_g = test_o = test_w = test_y = 0;
		valid = 1;
		double * current = new double[3];


		//slots 1 through 9 face 1 top of cube

		current = get_colour_from_user_from_char();
		c18.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c19.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c20.setColours(current[0], current[1], current[2], 1);

		current = get_colour_from_user_from_char();
		c10.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c11.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c12.setColours(current[0], current[1], current[2], 1);

		current = get_colour_from_user_from_char();
		c1.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c2.setColours(current[0], current[1], current[2], 1);
		current = get_colour_from_user_from_char();
		c3.setColours(current[0], current[1], current[2], 1);
		

		//slots 1 through 9 face 3 bottom of cube

		current = get_colour_from_user_from_char();
		c7.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c8.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c9.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c15.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c16.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c17.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c24.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c25.setColours(current[0], current[1], current[2], 3);
		current = get_colour_from_user_from_char();
		c26.setColours(current[0], current[1], current[2], 3);


		//slots 1 through 9 face 5 front of cube

		current = get_colour_from_user_from_char();


		c1.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c2.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c3.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c4.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c5.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c6.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c7.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c8.setColours(current[0], current[1], current[2], 5);
		current = get_colour_from_user_from_char();

		c9.setColours(current[0], current[1], current[2], 5);

		//slots 1 through 9 face 2 right of cube

		current = get_colour_from_user_from_char();
		c3.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c12.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c20.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c6.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c14.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c23.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c9.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c17.setColours(current[0], current[1], current[2], 2);
		current = get_colour_from_user_from_char();
		c26.setColours(current[0], current[1], current[2], 2);
	


//slots 1 through 9 face 4s back of cube
	current = get_colour_from_user_from_char();
	c20.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c19.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c18.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c23.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c22.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c21.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c26.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c25.setColours(current[0], current[1], current[2], 4);
	current = get_colour_from_user_from_char();
	c24.setColours(current[0], current[1], current[2], 4);

	//slots 1 through 9 face 0 left of cube
	current = get_colour_from_user_from_char();
	c18.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c10.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c1.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c21.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c13.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c4.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c24.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c15.setColours(current[0], current[1], current[2], 0);
	current = get_colour_from_user_from_char();
	c7.setColours(current[0], current[1], current[2], 0);



	if (test_r != 9 || test_b != 9 || test_g != 9 || test_o != 9 || test_y != 9 || test_w != 9) {
		valid = 0;
		std::cout << test_r;
		std::cout << "\n";
		std::cout << test_b;
		std::cout << "\n";
		std::cout << test_g;
		std::cout << "\n";
		std::cout << test_o;
		std::cout << "\n";
		std::cout << test_y;
		std::cout << "\n";
		std::cout << test_w;
		std::cout << "\n";
	}

	}

	//assign the 27 cubes to meaningful address locations
	frontTopLeft = &c1;
	frontTopMiddle = &c2;
	frontTopRight = &c3;	
	frontMiddleLeft = &c4;	
	frontMiddleMiddle = &c5;
	frontMiddleRight = &c6;
	frontBottomLeft = &c7;
	frontBottomMiddle = &c8;
	frontBottomRight = &c9;

	middleTopLeft = &c10;
	middleTopMiddle = &c11;
	middleTopRight = &c12;
	middleMiddleLeft = &c13;
	middleMiddleMiddle = &c27;
	middleMiddleRight = &c14;
	middleBottomLeft = &c15;
	middleBottomMiddle = &c16;
	middleBottomRight = &c17;

	backTopLeft = &c18;
	backTopMiddle = &c19;
	backTopRight = &c20;
	backMiddleLeft = &c21;
	backMiddleMiddle = &c22;
	backMiddleRight = &c23;
	backBottomLeft = &c24;
	backBottomMiddle = &c25;
	backBottomRight = &c26;

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);

	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 10.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.);      /* up is in positive Y direction */

							/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);


	

}

void rotateFrontCW()
{
		//this handles the rotation for each portion of the cube
		// it is run FRAMES times before the sides are updtated
		frontTopLeft->rotate(CW, ZSIDE, NAT);
		frontTopMiddle->rotate(CW, ZSIDE, NAT);
		frontTopRight->rotate(CW, ZSIDE, NAT);
		frontMiddleLeft->rotate(CW, ZSIDE, NAT);
		frontMiddleMiddle->rotate(CW, ZSIDE, NAT);
		frontMiddleRight->rotate(CW, ZSIDE, NAT);
		frontBottomLeft->rotate(CW, ZSIDE, NAT);
		frontBottomMiddle->rotate(CW, ZSIDE, NAT);
		frontBottomRight->rotate(CW, ZSIDE, NAT);
	//only update the cube postions when we have reached the end of a 90 degree rotation
	if (animation_tic_count == FRAMES) {
		temp = frontTopLeft;
		frontTopLeft = frontBottomLeft;
		frontBottomLeft = frontBottomRight;
		frontBottomRight = frontTopRight;
		frontTopRight = temp;
		temp = frontTopMiddle;
		frontTopMiddle = frontMiddleLeft;
		frontMiddleLeft = frontBottomMiddle;
		frontBottomMiddle = frontMiddleRight;
		frontMiddleRight = temp;
	}
}
void rotateFrontCCW() {
		//this handles the rotation for each portion of the cube
		// it is run FRAMES times before the sides are updtated
		frontTopLeft->rotate(CCW, ZSIDE, NAT);
		frontTopMiddle->rotate(CCW, ZSIDE, NAT);
		frontTopRight->rotate(CCW, ZSIDE, NAT);
		frontMiddleLeft->rotate(CCW, ZSIDE, NAT);
		frontMiddleMiddle->rotate(CCW, ZSIDE, NAT);
		frontMiddleRight->rotate(CCW, ZSIDE, NAT);
		frontBottomLeft->rotate(CCW, ZSIDE, NAT);
		frontBottomMiddle->rotate(CCW, ZSIDE, NAT);
		frontBottomRight->rotate(CCW, ZSIDE, NAT);
		//only update the cube postions when we have reached the end of a 90 degree rotation		
		if (animation_tic_count == FRAMES) {
			temp = frontTopLeft;
			frontTopLeft = frontTopRight;
			frontTopRight = frontBottomRight;
			frontBottomRight = frontBottomLeft;
			frontBottomLeft = temp;

			temp = frontTopMiddle;
			frontTopMiddle = frontMiddleRight;
			frontMiddleRight = frontBottomMiddle;
			frontBottomMiddle = frontMiddleLeft;
			frontMiddleLeft = temp;
		}

}
void rotateBackCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		backTopLeft->rotate(CW, ZSIDE, REV);
		backTopMiddle->rotate(CW, ZSIDE, REV);
		backTopRight->rotate(CW, ZSIDE, REV);
		backMiddleLeft->rotate(CW, ZSIDE, REV);
		backMiddleMiddle->rotate(CW, ZSIDE, REV);
		backMiddleRight->rotate(CW, ZSIDE, REV);
		backBottomLeft->rotate(CW, ZSIDE, REV);
		backBottomMiddle->rotate(CW, ZSIDE, REV);
		backBottomRight->rotate(CW, ZSIDE, REV);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = backTopLeft;
			backTopLeft = backTopRight;
			backTopRight = backBottomRight;
			backBottomRight = backBottomLeft;
			backBottomLeft = temp;

			temp = backTopMiddle;
			backTopMiddle = backMiddleRight;
			backMiddleRight = backBottomMiddle;
			backBottomMiddle = backMiddleLeft;
			backMiddleLeft = temp;
		}

	}
void rotateBackCCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		backTopLeft->rotate(CCW, ZSIDE, REV);
		backTopMiddle->rotate(CCW, ZSIDE, REV);
		backTopRight->rotate(CCW, ZSIDE, REV);
		backMiddleLeft->rotate(CCW, ZSIDE, REV);
		backMiddleMiddle->rotate(CCW, ZSIDE, REV);
		backMiddleRight->rotate(CCW, ZSIDE, REV);
		backBottomLeft->rotate(CCW, ZSIDE, REV);
		backBottomMiddle->rotate(CCW, ZSIDE, REV);
		backBottomRight->rotate(CCW, ZSIDE, REV);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = backTopLeft;
			backTopLeft = backBottomLeft;
			backBottomLeft = backBottomRight;
			backBottomRight = backTopRight;
			backTopRight = temp;

			temp = backTopMiddle;
			backTopMiddle = backMiddleLeft;
			backMiddleLeft = backBottomMiddle;
			backBottomMiddle = backMiddleRight;
			backMiddleRight = temp;
		}

	}
void rotateLeftCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontTopLeft->rotate(CW, XSIDE, NAT);
		middleTopLeft->rotate(CW, XSIDE, NAT);
		backTopLeft->rotate(CW, XSIDE, NAT);
		frontMiddleLeft->rotate(CW, XSIDE, NAT);
		middleMiddleLeft->rotate(CW, XSIDE, NAT);
		backMiddleLeft->rotate(CW, XSIDE, NAT);
		frontBottomLeft->rotate(CW, XSIDE, NAT);
		middleBottomLeft->rotate(CW, XSIDE, NAT);
		backBottomLeft->rotate(CW, XSIDE, NAT);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = frontTopLeft;
			frontTopLeft = backTopLeft;
			backTopLeft = backBottomLeft;
			backBottomLeft = frontBottomLeft;
			frontBottomLeft = temp;

			temp = middleTopLeft;
			middleTopLeft = backMiddleLeft;
			backMiddleLeft = middleBottomLeft;
			middleBottomLeft = frontMiddleLeft;
			frontMiddleLeft = temp;
		}

	}
void rotateLeftCCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontTopLeft->rotate(CCW, XSIDE, NAT);
		middleTopLeft->rotate(CCW, XSIDE, NAT);
		backTopLeft->rotate(CCW, XSIDE, NAT);
		frontMiddleLeft->rotate(CCW, XSIDE, NAT);
		middleMiddleLeft->rotate(CCW, XSIDE, NAT);
		backMiddleLeft->rotate(CCW, XSIDE, NAT);
		frontBottomLeft->rotate(CCW, XSIDE, NAT);
		middleBottomLeft->rotate(CCW, XSIDE, NAT);
		backBottomLeft->rotate(CCW, XSIDE, NAT);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = frontTopLeft;
			frontTopLeft = frontBottomLeft;
			frontBottomLeft = backBottomLeft;
			backBottomLeft = backTopLeft;
			backTopLeft = temp;

			temp = middleTopLeft;
			middleTopLeft = frontMiddleLeft;
			frontMiddleLeft = middleBottomLeft;
			middleBottomLeft = backMiddleLeft;
			backMiddleLeft = temp;
		}
	}
void rotateRightCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontTopRight->rotate(CW, XSIDE, REV);
		middleTopRight->rotate(CW, XSIDE, REV);
		backTopRight->rotate(CW, XSIDE, REV);
		frontMiddleRight->rotate(CW, XSIDE, REV);
		middleMiddleRight->rotate(CW, XSIDE, REV);
		backMiddleRight->rotate(CW, XSIDE, REV);
		frontBottomRight->rotate(CW, XSIDE, REV);
		middleBottomRight->rotate(CW, XSIDE, REV);
		backBottomRight->rotate(CW, XSIDE, REV);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = frontTopRight;
			frontTopRight = frontBottomRight;
			frontBottomRight = backBottomRight;
			backBottomRight = backTopRight;
			backTopRight = temp;

			temp = middleTopRight;
			middleTopRight = frontMiddleRight;
			frontMiddleRight = middleBottomRight;
			middleBottomRight = backMiddleRight;
			backMiddleRight = temp;
		}
	}
void rotateRightCCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontTopRight->rotate(CCW, XSIDE, REV);
		middleTopRight->rotate(CCW, XSIDE, REV);
		backTopRight->rotate(CCW, XSIDE, REV);
		frontMiddleRight->rotate(CCW, XSIDE, REV);
		middleMiddleRight->rotate(CCW, XSIDE, REV);
		backMiddleRight->rotate(CCW, XSIDE, REV);
		frontBottomRight->rotate(CCW, XSIDE, REV);
		middleBottomRight->rotate(CCW, XSIDE, REV);
		backBottomRight->rotate(CCW, XSIDE, REV);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = frontTopRight;
			frontTopRight = backTopRight;
			backTopRight = backBottomRight;
			backBottomRight = frontBottomRight;
			frontBottomRight = temp;

			temp = middleTopRight;
			middleTopRight = backMiddleRight;
			backMiddleRight = middleBottomRight;
			middleBottomRight = frontMiddleRight;
			frontMiddleRight = temp;
		}

}
void rotateTopCW() {

	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontTopLeft->rotate(CW, YSIDE, NAT);
		frontTopMiddle->rotate(CW, YSIDE, NAT);
		frontTopRight->rotate(CW, YSIDE, NAT);
		middleTopLeft->rotate(CW, YSIDE, NAT);
		middleTopMiddle->rotate(CW, YSIDE, NAT);
		middleTopRight->rotate(CW, YSIDE, NAT);
		backTopLeft->rotate(CW, YSIDE, NAT);
		backTopMiddle->rotate(CW, YSIDE, NAT);
		backTopRight->rotate(CW, YSIDE, NAT);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {
			temp = frontTopLeft;
			frontTopLeft = frontTopRight;
			frontTopRight = backTopRight;
			backTopRight = backTopLeft;
			backTopLeft = temp;

			temp = frontTopMiddle;
			frontTopMiddle = middleTopRight;
			middleTopRight = backTopMiddle;
			backTopMiddle = middleTopLeft;
			middleTopLeft = temp;
		}
}
void rotateTopCCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
	frontTopLeft->rotate(CCW, YSIDE, NAT);
	frontTopMiddle->rotate(CCW, YSIDE, NAT);
	frontTopRight->rotate(CCW, YSIDE, NAT);
	middleTopLeft->rotate(CCW, YSIDE, NAT);
	middleTopMiddle->rotate(CCW, YSIDE, NAT);
	middleTopRight->rotate(CCW, YSIDE, NAT);
	backTopLeft->rotate(CCW, YSIDE, NAT);
	backTopMiddle->rotate(CCW, YSIDE, NAT);
	backTopRight->rotate(CCW, YSIDE, NAT);
	//only update the cube postions when we have reached the end of a 90 degree rotation
	if (animation_tic_count == FRAMES) {
		temp = frontTopLeft;
		frontTopLeft = backTopLeft;
		backTopLeft = backTopRight;
		backTopRight = frontTopRight;
		frontTopRight = temp;

		temp = frontTopMiddle;
		frontTopMiddle = middleTopLeft;
		middleTopLeft = backTopMiddle;
		backTopMiddle = middleTopRight;
		middleTopRight = temp;
	}
}
void rotateBottomCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
	frontTopLeft->rotate(CCW, YSIDE, REV);
	frontTopMiddle->rotate(CCW, YSIDE, REV);
	frontTopRight->rotate(CCW, YSIDE, REV);
	middleTopLeft->rotate(CCW, YSIDE, REV);
	middleTopMiddle->rotate(CCW, YSIDE, REV);
	middleTopRight->rotate(CCW, YSIDE, REV);
	backTopLeft->rotate(CCW, YSIDE, REV);
	backTopMiddle->rotate(CCW, YSIDE, REV);
	backTopRight->rotate(CCW, YSIDE, REV);
	//only update the cube postions when we have reached the end of a 90 degree rotation
	if (animation_tic_count == FRAMES) {
		temp = frontTopLeft;
		frontTopLeft = frontTopRight;
		frontTopRight = backTopRight;
		backTopRight = backTopLeft;
		backTopLeft = temp;

		temp = frontTopMiddle;
		frontTopMiddle = middleTopRight;
		middleTopRight = backTopMiddle;
		backTopMiddle = middleTopLeft;
		middleTopLeft = temp;
	}
}
void rotateBottomCCW() {
	//this handles the rotation for each portion of the cube
	// it is run FRAMES times before the sides are updtated
		frontBottomLeft->rotate(CCW, YSIDE, REV);
		frontBottomMiddle->rotate(CCW, YSIDE, REV);
		frontBottomRight->rotate(CCW, YSIDE, REV);
		middleBottomLeft->rotate(CCW, YSIDE, REV);
		middleBottomMiddle->rotate(CCW, YSIDE, REV);
		middleBottomRight->rotate(CCW, YSIDE, REV);
		backBottomLeft->rotate(CCW, YSIDE, REV);
		backBottomMiddle->rotate(CCW, YSIDE, REV);
		backBottomRight->rotate(CCW, YSIDE, REV);
		//only update the cube postions when we have reached the end of a 90 degree rotation
		if (animation_tic_count == FRAMES) {

			temp = frontBottomLeft;
			frontBottomLeft = frontBottomRight;
			frontBottomRight = backBottomRight;
			backBottomRight = backBottomLeft;
			backBottomLeft = temp;

			temp = frontBottomMiddle;
			frontBottomMiddle = middleBottomRight;
			middleBottomRight = backBottomMiddle;
			backBottomMiddle = middleBottomLeft;
			middleBottomLeft = temp;
		}
}


std::vector<std::string> rubix_parser(std::string inputs)
{	// declare num for use later
	int num;
	// declare rotations to contain additions later
	std::vector<std::string> rotations;
	// declare current as a temporary string variable
	std::string current;
	//for loop. start at zero count up by threes to jump "c# " characters
	for (size_t current_index = 0; current_index<inputs.size(); current_index = current_index + 3) {
		//covert the char value from the string to an integer by subtracting ASCI 0
		num = inputs[current_index + 1] - '0';
		//take a 1 character substring of the current char so that we maintain string type
		current = inputs.substr(current_index, 1);
		//algorithm specifies number of rotations
		// for each rotation add it to the end of the vector
		for (int y = 0; y<num; y++)
			rotations.push_back(current);
	}
	return rotations;
}

void rotation_instructions(std::string rot_instructs) {

		//Map the character of the instuction string to the correct rotate function
		//R calls rotate right counter clockwise
		if (rot_instructs == "R") {
			rotateRightCW();
		}
		//L calls rotate left counter clockwise
		else if (rot_instructs == "L") {
			rotateLeftCW();
		}
		//U calls rotate top counter clockwise
		else if (rot_instructs == "U") {
			rotateTopCW();
		}
		//D calls rotate bottom counter clockwise
		else if (rot_instructs == "D") {
			rotateBottomCW();
		}
		//F calls rotate front counter clockwise
		else if (rot_instructs == "F") {
			rotateFrontCW();
		}
		//B calls rotate back counter clockwise
		else if (rot_instructs == "B") {
			rotateBackCW();
		}
		
}
int colour_interp(double *current) {
	/*1.0, 0.0, 0.0 is red
	0.0, 1.0, 0.0 is green
	0.0, 0.0, 1.0 is blue
	1.0, 0.5, 0.0 is orange
	1.0, 1.0, 1.0 is white
	1.0, 1.0, 0.0 is yellow*/
	if (current[0] == 1 && current[1] == 0 && current[2] == 0) {
		return 1;
	}
	else if (current[0] == 0 && current[1] == 1 && current[2] == 0) {
		return 2;
	}
	if (current[0] == 0 && current[1] == 0 && current[2] == 1) {
		return 3;
	}
	else if (current[0] == 1 && current[1] == 0.5 && current[2] == 0) {
		return 4;
	}
	if (current[0] == 1 && current[1] == 1 && current[2] == 1) {
		return 5;
	}
	else if (current[0] == 1 && current[1] == 1 && current[2] == 0) {
		return 6;
	}
	else return 7;
}
int** cube_state() {
	std::vector<int> cube_position_colour;
	int current;
	
	
	//---------------Top face
	int** arr = 0;
	arr = new int*[6];
	for (int h = 0; h < 6; h++)
	{
		arr[h] = new int[9];
	}
		
	arr[2][0]= colour_interp(frontTopLeft->getColours(1));
	arr[2][1] = colour_interp(frontTopMiddle->getColours(1));
	arr[2][2] = colour_interp(frontTopRight->getColours(1));
	//middle top row
	arr[2][3] = colour_interp(middleTopLeft->getColours(1));
	arr[2][4] = colour_interp(middleTopMiddle->getColours(1));
	arr[2][5] = colour_interp(middleTopRight->getColours(1));

	//back top row
	arr[2][6] = colour_interp(backTopLeft->getColours(1));
	arr[2][7] = colour_interp(backTopMiddle->getColours(1));
	arr[2][8] = colour_interp(backTopRight->getColours(1));

	
	//--------bottom of the cube
	//bottom front row
	arr[5][0] = colour_interp(frontBottomLeft->getColours(3));
	arr[5][1] = colour_interp(frontBottomMiddle->getColours(3));
	arr[5][2] = colour_interp(frontBottomRight->getColours(3));

	//bottom middle row
	arr[5][3] = colour_interp(middleBottomLeft->getColours(3));
	arr[5][4] = colour_interp(middleBottomMiddle->getColours(3));
	arr[5][5] = colour_interp(middleBottomRight->getColours(3));

	//bottom front row
	arr[5][6] = colour_interp(backBottomLeft->getColours(3));
	arr[5][7] = colour_interp(backBottomMiddle->getColours(3));
	arr[5][8] = colour_interp(backBottomRight->getColours(3));

	
	//------------------front face

	//top front row
	arr[0][0] = colour_interp(frontTopLeft->getColours(5));
	arr[0][1] = colour_interp(frontTopMiddle->getColours(5));
	arr[0][2] = colour_interp(frontTopRight->getColours(5));
	//middle front row
	arr[0][3] = colour_interp(frontMiddleLeft->getColours(5));
	arr[0][4] = colour_interp(frontMiddleMiddle->getColours(5));
	arr[0][5] = colour_interp(frontMiddleRight->getColours(5));
	//bottom front row
	arr[0][6] = colour_interp(frontBottomLeft->getColours(5));
	arr[0][7] = colour_interp(frontBottomMiddle->getColours(5));
	arr[0][8] = colour_interp(frontBottomRight->getColours(5));

	arr[1][0] = colour_interp(frontTopRight->getColours(2));
	arr[1][1] = colour_interp(middleTopRight->getColours(2));
	arr[1][2] = colour_interp(backTopRight->getColours(2));

	//middle back row
	arr[1][3] = colour_interp(frontMiddleRight->getColours(2));
	arr[1][4] = colour_interp(middleMiddleRight->getColours(2));
	arr[1][5] = colour_interp(backMiddleRight->getColours(2));

	//bottom back row
	arr[1][6] = colour_interp(frontBottomRight->getColours(2));
	arr[1][7] = colour_interp(middleBottomRight->getColours(2));
	arr[1][8] = colour_interp(backBottomRight->getColours(2));

	
	arr[3][0] = colour_interp(backTopLeft->getColours(4));
	arr[3][1] = colour_interp(backTopMiddle->getColours(4));
	arr[3][2] = colour_interp(backTopRight->getColours(4));

	//middle back row
	arr[3][3] = colour_interp(backMiddleLeft->getColours(4));
	arr[3][4] = colour_interp(backMiddleMiddle->getColours(4));
	arr[3][5] = colour_interp(backMiddleRight->getColours(4));

	//bottom back row
	arr[3][6] = colour_interp(backBottomLeft->getColours(4));
	arr[3][7] = colour_interp(backBottomMiddle->getColours(4));
	arr[3][8] = colour_interp(backBottomRight->getColours(4));


	//---------left face of the cube
	//top back row
	arr[4][0] = colour_interp(frontTopLeft->getColours(0));
	arr[4][1] = colour_interp(middleTopLeft->getColours(0));
	arr[4][2] = colour_interp(backTopLeft->getColours(0));

	//middle back row
	arr[4][3] = colour_interp(frontMiddleLeft->getColours(0));
	arr[4][4] = colour_interp(middleMiddleLeft->getColours(0));
	arr[4][5] = colour_interp(backMiddleLeft->getColours(0));

	//bottom back row
	arr[4][6] = colour_interp(frontBottomLeft->getColours(0));
	arr[4][7] = colour_interp(middleBottomLeft->getColours(0));
	arr[4][8] = colour_interp(backBottomLeft->getColours(0));
	
	//----------------------------------
	return arr;

}

void myKeyboard(unsigned char key, int x, int y)
{
	//when e is pressed and we aren't currently running the solution start the solution function
	if (key == 'e' && solution_boolean==0) {
		int** state = cube_state();
		std::cout << "---------------------------\n";

		// FRUBLD is the ordering required for our colour mapper
		int colorMap[6][9];
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 9; y++) {
				colorMap[x][y] = state[x][y];
			}
		}


		ColorSingmaster mapper = ColorSingmaster();
		string mapped = mapper.getSingmasterStringFromColorMap(colorMap);
		cout << mapped;

		ThistleSolver solver = ThistleSolver();
		string soln = solver.getSolutionFor(mapped);
		cout << soln;

		solution_boolean += 1;
		rotate_vector = rubix_parser(soln);
	
	}
	
}
void rotationKeys(int key, int x, int y) {
	//when the right key is held down increment the wait time by 2
	//waiting is used in sleep and slows down the animation
	if (key == GLUT_KEY_RIGHT) {
		wait_time = wait_time + 2;
	}
	//holding down right decreases the wait time to a minimum of 3
	//This speeds up the animation
	else if (key == GLUT_KEY_LEFT) {
		if (wait_time > 3) {
			wait_time = wait_time - 2;
		}
	}
	//holding up will rotate the camera
	else if (key == GLUT_KEY_UP) {
		glRotatef(-15, 1.0, 1.0, 1.0);
	}
	//holding down will rotate the camera in the oposite direction
	else if (key == GLUT_KEY_DOWN) {
		glRotatef(15, 1.0, 1.0, 1.0);
	}

}

void
display(void)
{
	//handle calculations of a solution
	if (solution_boolean == 1)
	{	//while we haven't reached the end of the string and solution is triggered we run a single calculation per frame
		if (current_string_index < rotate_vector.size()) {
			//animation tics up to the number of frames currently 32
			animation_tic_count += 1;
			rotation_instructions(rotate_vector[current_string_index]);
			//when animation_tic_count reaches frames it has completed a 90 degree rotation
			if (animation_tic_count == FRAMES) {
				//move to the next rotation value
				current_string_index += 1;
				//reset the tic counter
				animation_tic_count = 0;
			}
		}
		else {
			//when the entire solution has been done reset the solution boolean and string index
			//if keyboard based scrambling is implemented this will allow the program to resolve the cube
			current_string_index = 0;
			solution_boolean = 0;
		}
	}
	//draw the current boxes into the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	c1.drawBox();
	c2.drawBox();
	c3.drawBox();

	c4.drawBox();
	c5.drawBox();
	c6.drawBox();

	c7.drawBox();
	c8.drawBox();
	c9.drawBox();

	c10.drawBox();
	c11.drawBox();
	c12.drawBox();

	c13.drawBox();
	c14.drawBox();
	c15.drawBox();

	c16.drawBox();
	c17.drawBox();
	c18.drawBox();

	c19.drawBox();
	c20.drawBox();
	c21.drawBox();

	c22.drawBox();
	c23.drawBox();
	c24.drawBox();

	c25.drawBox();
	c26.drawBox();
	c27.drawBox();

	glutSwapBuffers();
}


void redisplay() {
	//this redisplay function calls display
	//it is triggered whenever the program is idle
	glutPostRedisplay();
	//putting a sleep here allows us to slow the animation down
	Sleep(wait_time);

}

bool runTestSuite() {

	string testCases[] = {
		"UR UB UL UF DF DR DB DL FR FL BR BL URB UBL ULF UFR DRF DFL DLB DBR"
	};

	string testCaseSolutions[] = {
		"U1 U2" // This maps to the first
	};

	int i = 0;
	for (auto testCase : testCases) {
		ThistleSolver solver = ThistleSolver();
		string solution = solver.getSolutionFor(testCase);
		if (solution != testCaseSolutions[i]) {
			return false;
		}
		i++;
	}

	return true;
}

int main(int argc, char **argv)
{	
	// Test bench for unit testing...
	bool didTestsPass = runTestSuite();

	if (didTestsPass) {
		cout << "All tests passed. Changeset OK.\n";
	}
	else {
		cout << "A test failure occured. Change not OK.\n";
		return -1;
	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Rubik's Cube");
	glutDisplayFunc(display);
	glutSpecialFunc(rotationKeys);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(redisplay);

	//string temp should be replaced with the data from the cube solver;
	
	init();


	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}


