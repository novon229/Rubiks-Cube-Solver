
#include <windows.h> // use proper includes for your system
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/Gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

class cube{
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
	void rotate(int direction) {
		glRotatef(5, 1.0, 1.0, 1.0);
	}

private:
	
	GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
		{ -1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 1.0, 0.0, 0.0 },
		{ 0.0, -1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 0.0, 0.0, -1.0 } };
	GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
		{ 0, 1, 2, 3 },{ 3, 2, 6, 7 },{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },{ 5, 6, 2, 1 },{ 7, 4, 0, 3 } };
	GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
	GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };  /* Red diffuse light. */
	GLfloat light_position[4] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */
	float theta = 90;
	float xMatrix[4][4] = { { 1, 0, 0, 0 },
	{ 0, cos(theta), -sin(theta), 0 },
	{ 0, sin(theta), cos(theta), 0 },
	{ 0, 0, 0, 1 } };
	float yMatrix[4][4] = { { cos(theta), 0, sin(theta), 0 },
	{ 0, 1, 0, 0 },
	{ -sin(theta), 0, cos(theta), 0 },
	{ 0, 0, 0, 1 } };
	float zMatrix[4][4] = { { cos(theta), -sin(theta), 0, 0 },
	{ sin(theta), cos(theta), 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 } };
};



//========================================================================================================================================================================

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

	/*frontTopLeft.setColours(1.0, 1.0, 1.0, 2);	//extra colours for testing just the one cube
	frontTopLeft.setColours(1.0, 0.0, 0.0, 3);
	frontTopLeft.setColours(0.0, 0.0, 1.0, 4);*/

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
	//glTranslatef(0.0, 0.0, -1.0);
	//glRotatef(60, 1.0, 0.0, 0.0);
	//glRotatef(-20, 0.0, 0.0, 1.0);

}


void rotationKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		frontTopLeft.rotate(0);
	}
	else if (key == GLUT_KEY_LEFT) {

	}
	else if (key == GLUT_KEY_UP) {

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


