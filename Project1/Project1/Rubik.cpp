
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
#include <thread>
//#include "cube_parser.cpp"
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
	float theta = M_PI_2 / 16;
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
int solution_boolean = 0;
int string_length;
int animation_tic_count = 0;
int current_string_index = 0;
std::string temporary_string = "U9 B9 F9 D9 L9 R9";
std::vector<std::string> rotate_vector;
void
init(void)
{
	//initilize global
	wait_time = 500;

	//double colours[6][3] = { {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0},  {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.5, 0.0} };
	c1 = cube(-0.9, -0.32, 0.32, 0.9, 0.9, 0.32);
	c1.setColours(0.0, 1.0, 0.0, 0);
	c1.setColours(1.0, 1.0, 0.0, 1);
	c1.setColours(1.0, 0.5, 0.0, 5);
	frontTopLeft = &c1;

	//frontTopLeft.setColours(1.0, 1.0, 1.0, 2);
	//frontTopLeft.setColours(1.0, 0.0, 0.0, 3);
	//frontTopLeft.setColours(0.0, 0.0, 1.0, 4);

	c2 = cube(-0.3, 0.3, 0.32, 0.9, 0.9, 0.32);
	c2.setColours(1.0, 1.0, 0.0, 1);
	c2.setColours(1.0, 0.5, 0.0, 5);
	frontTopMiddle = &c2;

	c3 = cube(0.32, 0.9, 0.32, 0.9, 0.9, 0.32);
	c3.setColours(1.0, 1.0, 0.0, 1);
	c3.setColours(1.0, 1.0, 1.0, 2);
	c3.setColours(1.0, 0.5, 0.0, 5);
	frontTopRight = &c3;	

	c4 = cube(-0.9, -0.32, -0.3, 0.3, 0.9, 0.32);
	c4.setColours(0.0, 1.0, 0.0, 0);
	c4.setColours(1.0, 0.5, 0.0, 5);
	frontMiddleLeft = &c4;	

	c5 = cube(-0.3, 0.3, -0.3, 0.3, 0.9, 0.32);
	c5.setColours(1.0, 0.5, 0.0, 5);
	frontMiddleMiddle = &c5;

	c6 = cube(0.32, 0.9, -0.3, 0.3, 0.9, 0.32);
	c6.setColours(1.0, 1.0, 1.0, 2);
	c6.setColours(1.0, 0.5, 0.0, 5);
	frontMiddleRight = &c6;

	c7 = cube(-0.9, -0.32, -0.9, -0.32, 0.9, 0.32);
	c7.setColours(0.0, 1.0, 0.0, 0);
	c7.setColours(1.0, 0.0, 0.0, 3);
	c7.setColours(1.0, 0.5, 0.0, 5);
	frontBottomLeft = &c7;

	c8 = cube(-0.3, 0.3, -0.9, -0.32, 0.9, 0.32);
	c8.setColours(1.0, 0.0, 0.0, 3);
	c8.setColours(1.0, 0.5, 0.0, 5);
	frontBottomMiddle = &c8;

	c9 = cube(0.32, 0.9, -0.9, -0.32, 0.9, 0.32);
	c9.setColours(1.0, 1.0, 1.0, 2);
	c9.setColours(1.0, 0.0, 0.0, 3);
	c9.setColours(1.0, 0.5, 0.0, 5);
	frontBottomRight = &c9;

	c10 = cube(-0.9, -0.32, 0.32, 0.9, 0.3, -0.3);
	c10.setColours(0.0, 1.0, 0.0, 0);
	c10.setColours(1.0, 1.0, 0.0, 1);
	middleTopLeft = &c10;

	c11 = cube(-0.3, 0.3, 0.32, 0.9, 0.3, -0.3);
	c11.setColours(1.0, 1.0, 0.0, 1);
	middleTopMiddle = &c11;

	c12 = cube(0.32, 0.9, 0.32, 0.9, 0.3, -0.3);
	c12.setColours(1.0, 1.0, 0.0, 1);
	c12.setColours(1.0, 1.0, 1.0, 2);
	middleTopRight = &c12;

	c13 = cube(-0.9, -0.32, -0.3, 0.3, 0.3, -0.3);
	c13 .setColours(0.0, 1.0, 0.0, 0);
	middleMiddleLeft = &c13;

	c27 = cube(-0.3, 0.3, -0.3, 0.3, 0.3, -0.3);
	middleMiddleMiddle = &c27;

	c14 = cube(0.32, 0.9, -0.3, 0.3, 0.3, -0.3);
	c14.setColours(1.0, 1.0, 1.0, 2);
	middleMiddleRight = &c14;

	c15 = cube(-0.9, -0.32, -0.9, -0.32, 0.3, -0.3);
	c15.setColours(0.0, 1.0, 0.0, 0);
	c15.setColours(1.0, 0.0, 0.0, 3);
	middleBottomLeft = &c15;

	c16 = cube(-0.3, 0.3, -0.9, -0.32, 0.3, -0.3);
	c16.setColours(1.0, 0.0, 0.0, 3);
	middleBottomMiddle = &c16;

	c17 = cube(0.32, 0.9, -0.9, -0.32, 0.3, -0.3);
	c17.setColours(1.0, 1.0, 1.0, 2);
	c17.setColours(1.0, 0.0, 0.0, 3);
	middleBottomRight = &c17;

	c18 = cube(-0.9, -0.32, 0.32, 0.9, -0.32, -0.9);
	c18.setColours(0.0, 1.0, 0.0, 0);
	c18.setColours(1.0, 1.0, 0.0, 1);
	c18.setColours(0.0, 0.0, 1.0, 4);
	backTopLeft = &c18;

	c19 = cube(-0.3, 0.3, 0.32, 0.9, -0.32, -0.9);
	c19.setColours(1.0, 1.0, 0.0, 1);
	c19.setColours(0.0, 0.0, 1.0, 4);
	backTopMiddle = &c19;

	c20 = cube(0.32, 0.9, 0.32, 0.9, -0.32, -0.9);
	c20.setColours(1.0, 1.0, 0.0, 1);
	c20.setColours(1.0, 1.0, 1.0, 2);
	c20.setColours(0.0, 0.0, 1.0, 4);
	backTopRight = &c20;

	c21 = cube(-0.9, -0.32, -0.3, 0.3, -0.32, -0.9);
	c21.setColours(0.0, 1.0, 0.0, 0);
	c21.setColours(0.0, 0.0, 1.0, 4);
	backMiddleLeft = &c21;

	c22 = cube(-0.3, 0.3, -0.3, 0.3, -0.32, -0.9);
	c22.setColours(0.0, 0.0, 1.0, 4);
	backMiddleMiddle = &c22;

	c23 = cube(0.32, 0.9, -0.3, 0.3, -0.32, -0.9);
	c23.setColours(1.0, 1.0, 1.0, 2);
	c23.setColours(0.0, 0.0, 1.0, 4);
	backMiddleRight = &c23;

	c24 = cube(-0.9, -0.32, -0.9, -0.32, -0.32, -0.9);
	c24.setColours(0.0, 1.0, 0.0, 0);
	c24.setColours(1.0, 0.0, 0.0, 3);
	c24.setColours(0.0, 0.0, 1.0, 4);
	backBottomLeft = &c24;

	c25 = cube(-0.3, 0.3, -0.9, -0.32, -0.32, -0.9);
	c25.setColours(1.0, 0.0, 0.0, 3);
	c25.setColours(0.0, 0.0, 1.0, 4);
	backBottomMiddle = &c25;

	c26 = cube(0.32, 0.9, -0.9, -0.32, -0.32, -0.9);
	c26.setColours(1.0, 1.0, 1.0, 2);
	c26.setColours(1.0, 0.0, 0.0, 3);
	c26.setColours(0.0, 0.0, 1.0, 4);
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
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CW, ZSIDE, NAT);
		frontTopMiddle->rotate(CW, ZSIDE, NAT);
		frontTopRight->rotate(CW, ZSIDE, NAT);
		frontMiddleLeft->rotate(CW, ZSIDE, NAT);
		frontMiddleMiddle->rotate(CW, ZSIDE, NAT);
		frontMiddleRight->rotate(CW, ZSIDE, NAT);
		frontBottomLeft->rotate(CW, ZSIDE, NAT);
		frontBottomMiddle->rotate(CW, ZSIDE, NAT);
		frontBottomRight->rotate(CW, ZSIDE, NAT);
	}
	 
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
void rotateFrontCCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CCW, ZSIDE, NAT);
		frontTopMiddle->rotate(CCW, ZSIDE, NAT);
		frontTopRight->rotate(CCW, ZSIDE, NAT);
		frontMiddleLeft->rotate(CCW, ZSIDE, NAT);
		frontMiddleMiddle->rotate(CCW, ZSIDE, NAT);
		frontMiddleRight->rotate(CCW, ZSIDE, NAT);
		frontBottomLeft->rotate(CCW, ZSIDE, NAT);
		frontBottomMiddle->rotate(CCW, ZSIDE, NAT);
		frontBottomRight->rotate(CCW, ZSIDE, NAT);
	}

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
void rotateBackCW() {
	for (int i = 0; i < 16; i++) {
		backTopLeft->rotate(CW, ZSIDE, REV);
		backTopMiddle->rotate(CW, ZSIDE, REV);
		backTopRight->rotate(CW, ZSIDE, REV);
		backMiddleLeft->rotate(CW, ZSIDE, REV);
		backMiddleMiddle->rotate(CW, ZSIDE, REV);
		backMiddleRight->rotate(CW, ZSIDE, REV);
		backBottomLeft->rotate(CW, ZSIDE, REV);
		backBottomMiddle->rotate(CW, ZSIDE, REV);
		backBottomRight->rotate(CW, ZSIDE, REV);
	}

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
void rotateBackCCW() {
	for (int i = 0; i < 16; i++) {
		backTopLeft->rotate(CCW, ZSIDE, REV);
		backTopMiddle->rotate(CCW, ZSIDE, REV);
		backTopRight->rotate(CCW, ZSIDE, REV);
		backMiddleLeft->rotate(CCW, ZSIDE, REV);
		backMiddleMiddle->rotate(CCW, ZSIDE, REV);
		backMiddleRight->rotate(CCW, ZSIDE, REV);
		backBottomLeft->rotate(CCW, ZSIDE, REV);
		backBottomMiddle->rotate(CCW, ZSIDE, REV);
		backBottomRight->rotate(CCW, ZSIDE, REV);
	}

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
void rotateLeftCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CW, XSIDE, NAT);
		middleTopLeft->rotate(CW, XSIDE, NAT);
		backTopLeft->rotate(CW, XSIDE, NAT);
		frontMiddleLeft->rotate(CW, XSIDE, NAT);
		middleMiddleLeft->rotate(CW, XSIDE, NAT);
		backMiddleLeft->rotate(CW, XSIDE, NAT);
		frontBottomLeft->rotate(CW, XSIDE, NAT);
		middleBottomLeft->rotate(CW, XSIDE, NAT);
		backBottomLeft->rotate(CW, XSIDE, NAT);
	}
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
void rotateLeftCCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CCW, XSIDE, NAT);
		middleTopLeft->rotate(CCW, XSIDE, NAT);
		backTopLeft->rotate(CCW, XSIDE, NAT);
		frontMiddleLeft->rotate(CCW, XSIDE, NAT);
		middleMiddleLeft->rotate(CCW, XSIDE, NAT);
		backMiddleLeft->rotate(CCW, XSIDE, NAT);
		frontBottomLeft->rotate(CCW, XSIDE, NAT);
		middleBottomLeft->rotate(CCW, XSIDE, NAT);
		backBottomLeft->rotate(CCW, XSIDE, NAT);
	}
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
void rotateRightCW() {
	for (int i = 0; i < 16; i++) {
		frontTopRight->rotate(CW, XSIDE, REV);
		middleTopRight->rotate(CW, XSIDE, REV);
		backTopRight->rotate(CW, XSIDE, REV);
		frontMiddleRight->rotate(CW, XSIDE, REV);
		middleMiddleRight->rotate(CW, XSIDE, REV);
		backMiddleRight->rotate(CW, XSIDE, REV);
		frontBottomRight->rotate(CW, XSIDE, REV);
		middleBottomRight->rotate(CW, XSIDE, REV);
		backBottomRight->rotate(CW, XSIDE, REV);
	}
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
void rotateRightCCW() {
	for (int i = 0; i < 16; i++) {
		frontTopRight->rotate(CCW, XSIDE, REV);
		middleTopRight->rotate(CCW, XSIDE, REV);
		backTopRight->rotate(CCW, XSIDE, REV);
		frontMiddleRight->rotate(CCW, XSIDE, REV);
		middleMiddleRight->rotate(CCW, XSIDE, REV);
		backMiddleRight->rotate(CCW, XSIDE, REV);
		frontBottomRight->rotate(CCW, XSIDE, REV);
		middleBottomRight->rotate(CCW, XSIDE, REV);
		backBottomRight->rotate(CCW, XSIDE, REV);
	}
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
void rotateTopCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CW, YSIDE, NAT);
		frontTopMiddle->rotate(CW, YSIDE, NAT);
		frontTopRight->rotate(CW, YSIDE, NAT);
		middleTopLeft->rotate(CW, YSIDE, NAT);
		middleTopMiddle->rotate(CW, YSIDE, NAT);
		middleTopRight->rotate(CW, YSIDE, NAT);
		backTopLeft->rotate(CW, YSIDE, NAT);
		backTopMiddle->rotate(CW, YSIDE, NAT);
		backTopRight->rotate(CW, YSIDE, NAT);
	}

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
void rotateTopCCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CCW, YSIDE, NAT);
		frontTopMiddle->rotate(CCW, YSIDE, NAT);
		frontTopRight->rotate(CCW, YSIDE, NAT);
		middleTopLeft->rotate(CCW, YSIDE, NAT);
		middleTopMiddle->rotate(CCW, YSIDE, NAT);
		middleTopRight->rotate(CCW, YSIDE, NAT);
		backTopLeft->rotate(CCW, YSIDE, NAT);
		backTopMiddle->rotate(CCW, YSIDE, NAT);
		backTopRight->rotate(CCW, YSIDE, NAT);
	}

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
void rotateBottomCW() {
	for (int i = 0; i < 16; i++) {
		frontTopLeft->rotate(CCW, YSIDE, REV);
		frontTopMiddle->rotate(CCW, YSIDE, REV);
		frontTopRight->rotate(CCW, YSIDE, REV);
		middleTopLeft->rotate(CCW, YSIDE, REV);
		middleTopMiddle->rotate(CCW, YSIDE, REV);
		middleTopRight->rotate(CCW, YSIDE, REV);
		backTopLeft->rotate(CCW, YSIDE, REV);
		backTopMiddle->rotate(CCW, YSIDE, REV);
		backTopRight->rotate(CCW, YSIDE, REV);
	}

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
void rotateBottomCCW() {
	for (int i = 0; i < 16; i++) {
		frontBottomLeft->rotate(CCW, YSIDE, REV);
		frontBottomMiddle->rotate(CCW, YSIDE, REV);
		frontBottomRight->rotate(CCW, YSIDE, REV);
		middleBottomLeft->rotate(CCW, YSIDE, REV);
		middleBottomMiddle->rotate(CCW, YSIDE, REV);
		middleBottomRight->rotate(CCW, YSIDE, REV);
		backBottomLeft->rotate(CCW, YSIDE, REV);
		backBottomMiddle->rotate(CCW, YSIDE, REV);
		backBottomRight->rotate(CCW, YSIDE, REV);
	}

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
		if (rot_instructs == "R") {
			rotateRightCCW();
		}
		else if (rot_instructs == "L") {
			rotateLeftCCW();
		}
		else if (rot_instructs == "U") {
			rotateTopCCW();
		}
		else if (rot_instructs == "D") {
			rotateBottomCCW();
		}
		else if (rot_instructs == "F") {
			rotateFrontCCW();
		}
		else if (rot_instructs == "B") {
			rotateBackCCW();
		}
		
}

void loop_solution() {
	//idea is this will be replaced with a call to the solver
	
}
void myKeyboard(unsigned char key, int x, int y)
{
	//preliminary rotations attempt
	if (key == 'e' && solution_boolean==0) {
		solution_boolean += 1;		
		//std:: thread t1(loop_solution);
	}
	
}
void rotationKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		//rotateFrontCCW();
		wait_time = wait_time + 10;
	}
	else if (key == GLUT_KEY_LEFT) {
		//rotateLeftCCW();
		if (wait_time > 10) {
			wait_time = wait_time - 10;
		}
	}
	else if (key == GLUT_KEY_UP) {
		//rotateTopCCW();
	}
	else if (key == GLUT_KEY_DOWN) {
		glRotatef(15, 1.0, 1.0, 1.0);
	}
	//glutPostRedisplay();

}

void
display(void)
{
	if (solution_boolean == 1)
	{
		rotate_vector = rubix_parser(temporary_string);
		if (current_string_index < rotate_vector.size()) {
			rotation_instructions(rotate_vector[current_string_index]);
			current_string_index += 1;
			Sleep(wait_time);
		}
		else {
			current_string_index = 0;
			solution_boolean = 0;
		}
	}
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
	glutPostRedisplay();
}

int
main(int argc, char **argv)
{
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


