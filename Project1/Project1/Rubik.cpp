
#include <windows.h> // use proper includes for your system
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/Gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

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
	float theta = M_PI_4 / 8;
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
int XSIDE = 0;
int YSIDE = 1;
int ZSIDE = 2;
bool NAT = 0;
bool REV = 1;

cube backTopLeft, backTopMiddle, backTopRight;
cube backMiddleLeft, backMiddleMiddle, backMiddleRight;
cube backBottomLeft, backBottomMiddle, backBottomRight;
cube middleTopLeft, middleTopMiddle, middleTopRight;
cube middleMiddleLeft, middleMiddleMiddle, middleMiddleRight;
cube middleBottomLeft, middleBottomMiddle, middleBottomRight;
cube frontTopLeft, frontTopMiddle, frontTopRight;
cube frontMiddleLeft, frontMiddleMiddle, frontMiddleRight;
cube frontBottomLeft, frontBottomMiddle, frontBottomRight;


void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	backTopLeft.drawBox();
	backTopMiddle.drawBox();
	backTopRight.drawBox();

	backMiddleLeft.drawBox();
	backMiddleMiddle.drawBox();
	backMiddleRight.drawBox();

	backBottomLeft.drawBox();
	backBottomMiddle.drawBox();
	backBottomRight.drawBox();

	middleTopLeft.drawBox();
	middleTopMiddle.drawBox();
	middleTopRight.drawBox();

	middleMiddleLeft.drawBox();
	middleMiddleMiddle.drawBox();
	middleMiddleRight.drawBox();

	middleBottomLeft.drawBox();
	middleBottomMiddle.drawBox();
	middleBottomRight.drawBox();

	frontTopLeft.drawBox();
	frontTopMiddle.drawBox();
	frontTopRight.drawBox();

	frontMiddleLeft.drawBox();
	frontMiddleMiddle.drawBox();
	frontMiddleRight.drawBox();

	frontBottomLeft.drawBox();
	frontBottomMiddle.drawBox();
	frontBottomRight.drawBox();

	glutSwapBuffers();
}

void
init(void)
{
	//double colours[6][3] = { {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0},  {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.5, 0.0} };
	frontTopLeft = cube(-0.9, -0.32, 0.32, 0.9, 0.9, 0.32);
	frontTopLeft.setColours(0.0, 1.0, 0.0, 0);
	frontTopLeft.setColours(1.0, 1.0, 0.0, 1);
	frontTopLeft.setColours(1.0, 0.5, 0.0, 5);

	//frontTopLeft.setColours(1.0, 1.0, 1.0, 2);
	//frontTopLeft.setColours(1.0, 0.0, 0.0, 3);
	//frontTopLeft.setColours(0.0, 0.0, 1.0, 4);

	frontTopMiddle = cube(-0.3, 0.3, 0.32, 0.9, 0.9, 0.32);
	frontTopMiddle.setColours(1.0, 1.0, 0.0, 1);
	frontTopMiddle.setColours(1.0, 0.5, 0.0, 5);

	frontTopRight = cube(0.32, 0.9, 0.32, 0.9, 0.9, 0.32);
	frontTopRight.setColours(1.0, 1.0, 0.0, 1);
	frontTopRight.setColours(1.0, 1.0, 1.0, 2);
	frontTopRight.setColours(1.0, 0.5, 0.0, 5);

	frontMiddleLeft = cube(-0.9, -0.32, -0.3, 0.3, 0.9, 0.32);
	frontMiddleLeft.setColours(0.0, 1.0, 0.0, 0);
	frontMiddleLeft.setColours(1.0, 0.5, 0.0, 5);

	frontMiddleMiddle = cube(-0.3, 0.3, -0.3, 0.3, 0.9, 0.32);
	frontMiddleMiddle.setColours(1.0, 0.5, 0.0, 5);

	frontMiddleRight = cube(0.32, 0.9, -0.3, 0.3, 0.9, 0.32);
	frontMiddleRight.setColours(1.0, 1.0, 1.0, 2);
	frontMiddleRight.setColours(1.0, 0.5, 0.0, 5);

	frontBottomLeft = cube(-0.9, -0.32, -0.9, -0.32, 0.9, 0.32);
	frontBottomLeft.setColours(0.0, 1.0, 0.0, 0);
	frontBottomLeft.setColours(1.0, 0.0, 0.0, 3);
	frontBottomLeft.setColours(1.0, 0.5, 0.0, 5);

	frontBottomMiddle = cube(-0.3, 0.3, -0.9, -0.32, 0.9, 0.32);
	frontBottomMiddle.setColours(1.0, 0.0, 0.0, 3);
	frontBottomMiddle.setColours(1.0, 0.5, 0.0, 5);

	frontBottomRight = cube(0.32, 0.9, -0.9, -0.32, 0.9, 0.32);
	frontBottomRight.setColours(1.0, 1.0, 1.0, 2);
	frontBottomRight.setColours(1.0, 0.0, 0.0, 3);
	frontBottomRight.setColours(1.0, 0.5, 0.0, 5);

	middleTopLeft = cube(-0.9, -0.32, 0.32, 0.9, 0.3, -0.3);
	middleTopLeft.setColours(0.0, 1.0, 0.0, 0);
	middleTopLeft.setColours(1.0, 1.0, 0.0, 1);

	middleTopMiddle = cube(-0.3, 0.3, 0.32, 0.9, 0.3, -0.3);
	middleTopMiddle.setColours(1.0, 1.0, 0.0, 1);

	middleTopRight = cube(0.32, 0.9, 0.32, 0.9, 0.3, -0.3);
	middleTopRight.setColours(1.0, 1.0, 0.0, 1);
	middleTopRight.setColours(1.0, 1.0, 1.0, 2);

	middleMiddleLeft = cube(-0.9, -0.32, -0.3, 0.3, 0.3, -0.3);
	middleMiddleLeft.setColours(0.0, 1.0, 0.0, 0);

	middleMiddleMiddle = cube(-0.3, 0.3, -0.3, 0.3, 0.3, -0.3);

	middleMiddleRight = cube(0.32, 0.9, -0.3, 0.3, 0.3, -0.3);
	middleMiddleRight.setColours(1.0, 1.0, 1.0, 2);

	middleBottomLeft = cube(-0.9, -0.32, -0.9, -0.32, 0.3, -0.3);
	middleBottomLeft.setColours(0.0, 1.0, 0.0, 0);
	middleBottomLeft.setColours(1.0, 0.0, 0.0, 3);

	middleBottomMiddle = cube(-0.3, 0.3, -0.9, -0.32, 0.3, -0.3);
	middleBottomMiddle.setColours(1.0, 0.0, 0.0, 3);

	middleBottomRight = cube(0.32, 0.9, -0.9, -0.32, 0.3, -0.3);
	middleBottomRight.setColours(1.0, 1.0, 1.0, 2);
	middleBottomRight.setColours(1.0, 0.0, 0.0, 3);

	backTopLeft = cube(-0.9, -0.32, 0.32, 0.9, -0.32, -0.9);
	backTopLeft.setColours(0.0, 1.0, 0.0, 0);
	backTopLeft.setColours(1.0, 1.0, 0.0, 1);
	backTopLeft.setColours(0.0, 0.0, 1.0, 4);

	backTopMiddle = cube(-0.3, 0.3, 0.32, 0.9, -0.32, -0.9);
	backTopMiddle.setColours(1.0, 1.0, 0.0, 1);
	backTopMiddle.setColours(0.0, 0.0, 1.0, 4);

	backTopRight = cube(0.32, 0.9, 0.32, 0.9, -0.32, -0.9);
	backTopRight.setColours(1.0, 1.0, 0.0, 1);
	backTopRight.setColours(1.0, 1.0, 1.0, 2);
	backTopRight.setColours(0.0, 0.0, 1.0, 4);

	backMiddleLeft = cube(-0.9, -0.32, -0.3, 0.3, -0.32, -0.9);
	backMiddleLeft.setColours(0.0, 1.0, 0.0, 0);
	backMiddleLeft.setColours(0.0, 0.0, 1.0, 4);

	backMiddleMiddle = cube(-0.3, 0.3, -0.3, 0.3, -0.32, -0.9);
	backMiddleMiddle.setColours(0.0, 0.0, 1.0, 4);

	backMiddleRight = cube(0.32, 0.9, -0.3, 0.3, -0.32, -0.9);
	backMiddleRight.setColours(1.0, 1.0, 1.0, 2);
	backMiddleRight.setColours(0.0, 0.0, 1.0, 4);

	backBottomLeft = cube(-0.9, -0.32, -0.9, -0.32, -0.32, -0.9);
	backBottomLeft.setColours(0.0, 1.0, 0.0, 0);
	backBottomLeft.setColours(1.0, 0.0, 0.0, 3);
	backBottomLeft.setColours(0.0, 0.0, 1.0, 4);

	backBottomMiddle = cube(-0.3, 0.3, -0.9, -0.32, -0.32, -0.9);
	backBottomMiddle.setColours(1.0, 0.0, 0.0, 3);
	backBottomMiddle.setColours(0.0, 0.0, 1.0, 4);

	backBottomRight = cube(0.32, 0.9, -0.9, -0.32, -0.32, -0.9);
	backBottomRight.setColours(1.0, 1.0, 1.0, 2);
	backBottomRight.setColours(1.0, 0.0, 0.0, 3);
	backBottomRight.setColours(0.0, 0.0, 1.0, 4);

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


void rotationKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		frontTopLeft.rotate(CW, ZSIDE, NAT);
		frontTopMiddle.rotate(CW, ZSIDE, NAT);
		frontTopRight.rotate(CW, ZSIDE, NAT);
		frontMiddleLeft.rotate(CW, ZSIDE, NAT);
		frontMiddleMiddle.rotate(CW, ZSIDE, NAT);
		frontMiddleRight.rotate(CW, ZSIDE, NAT);
		frontBottomLeft.rotate(CW, ZSIDE, NAT);
		frontBottomMiddle.rotate(CW, ZSIDE, NAT);
		frontBottomRight.rotate(CW, ZSIDE, NAT);
	}
	else if (key == GLUT_KEY_LEFT) {
		frontTopLeft.rotate(CW, XSIDE, NAT);
		middleTopLeft.rotate(CW, XSIDE, NAT);
		backTopLeft.rotate(CW, XSIDE, NAT);
		frontMiddleLeft.rotate(CW, XSIDE, NAT);
		middleMiddleLeft.rotate(CW, XSIDE, NAT);
		backMiddleLeft.rotate(CW, XSIDE, NAT);
		frontBottomLeft.rotate(CW, XSIDE, NAT);
		middleBottomLeft.rotate(CW, XSIDE, NAT);
		backBottomLeft.rotate(CW, XSIDE, NAT);
	}
	else if (key == GLUT_KEY_UP) {
		frontTopLeft.rotate(CW, YSIDE, NAT);
		frontTopMiddle.rotate(CW, YSIDE, NAT);
		frontTopRight.rotate(CW, YSIDE, NAT);
		middleTopLeft.rotate(CW, YSIDE, NAT);
		middleTopMiddle.rotate(CW, YSIDE, NAT);
		middleTopRight.rotate(CW, YSIDE, NAT);
		backTopLeft.rotate(CW, YSIDE, NAT);
		backTopMiddle.rotate(CW, YSIDE, NAT);
		backTopRight.rotate(CW, YSIDE, NAT);
	}
	else if (key == GLUT_KEY_DOWN) {

	}
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
	init();
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}


