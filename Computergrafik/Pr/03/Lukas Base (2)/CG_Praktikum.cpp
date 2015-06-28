//#include <glut.h>
//#include <GL/gl.h>
#include <GLUT/glut.h>

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <curses.h>
#include <string.h>


#if !defined(BUFSIZE)
#define BUFSIZE 512
#endif

float size = 1;			//Kreisgre
float rotate_x = 0;		//W・felausrichtung
float rotate_y = 0;
float rotate_z = 0;
float sphereXPOS = 0.0f;
float sphereYPOS = 0.0f;
float sphereZPOS = 0.0f;

float ORG[3] = { 0, 0, 0 };
float XP[3] = { 5, 0, 0 }, XN[3] = { -5, 0, 0 },
YP[3] = { 0, 5, 0 }, YN[3] = { 0, -5, 0 },
ZP[3] = { 0, 0, 5 }, ZN[3] = { 0, 0, -5 };

int sunRed=0;
int sunGreen=0;
int sunBlue=0;

int DESIRED_FPS=60;


void drawcircle(float size)
{
	glBegin(GL_LINE_STRIP);
	
	for (float i = 0; i <= 360; i++)
	{
		float angle = i / 360 * 2.0f * M_PI;

		float x = sinf(angle);
		float y = cosf(angle);

		glVertex2f(x*size, y*size);
	}
	glEnd();
}

void draw3DCircle(float x, float y, float z){
	glBegin(GL_LINES);
	for (float i = 0; i < 360; i++){
		float angle = i / 360 * 2.0f * M_PI;

		float x = sinf(angle);
		float y = cosf(angle);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
	}
	glEnd();
}
void drawcube()
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);

	glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotate_y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 1.0f); // Blau
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f); // Gr・
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f); // Rot
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 1.0f, 0.0f); // Gelb
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glColor3f(0.5f, 0.5f, 0.5f); // Grau
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 1.0f); // Violet
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
}

void drawRect()
{
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/DESIRED_FPS, timer, 0);
}

void changeSunColor() {
    if (sunRed>255|sunGreen>255){
        sunRed=255;
        sunGreen=255;
    }
        sunRed+=1;
        sunGreen-=1;
}

void drawSphere(){
    timer(100000000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float rotateTmp = 0;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	//draw coord system:
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);  glVertex3fv(ORG);  glVertex3fv(XP);    // X axis is red.
	glColor3f(0, 1, 0);  glVertex3fv(ORG);  glVertex3fv(YP);    // Y axis is green.
	glColor3f(0, 0, 1);  glVertex3fv(ORG);  glVertex3fv(ZP);    // z axis is blue.
	glEnd();
	

	//<--
	glPopMatrix();


    changeSunColor();
    //draw sun
	glColor3ub(sunRed, sunGreen, sunBlue);
    glPushMatrix();
	glutSolidSphere(0.75, 35, 35);
	glPopMatrix();

	
	//draw planet1
	glColor3f(0, 1, 1);
	glPushMatrix();
	glRotatef(rotateTmp, 0, 1, 0);
	glTranslatef(2.0f,0,0); // Verschiebung
	glRotatef(45, 1, 0, 0); // 45° Neigung
	glRotatef(-rotateTmp*3, 0, 0, 1);
	glutSolidSphere(0.25f,15,15); // planet 1
	
	//planet1 axis
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0.5f);
	glVertex3f(0,0,-0.5f);
	glEnd();

	drawcircle(0.3);
	drawcircle(0.31);
	drawcircle(0.32);
	drawcircle(0.33);
	drawcircle(0.34);
	drawcircle(0.35);

	//draw planet 1 moon 1
	glColor3f(1, 0, 1);
	glPushMatrix();
	glRotatef(-rotateTmp * 3, 0, 0, 1);
	glTranslatef(0.75f, 0, 0); // Verschiebung
	glutSolidSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();

	//draw planet 1 moon 2
	glColor3f(1, 0, 1);
	glPushMatrix();
	glRotatef(-rotateTmp * 3, 0, 0, 1);
	glTranslatef(-0.75f, 0, 0); // Verschiebung
	glutSolidSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();
	glPopMatrix();

	//draw planet2
	glColor3f(0, 1, 1);
    glPushMatrix();
	glRotatef(rotateTmp, 0, 1, 0);
	glTranslatef(-3, 0, 0);
	glRotatef(-rotateTmp, 0, 1, 0);
	glutSolidSphere(0.5f, 15, 15);


	//draw planet 2 moon 1
	glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(0.75f, 0, 0); // Verschiebung
	glRotatef(-rotateTmp * 2, 0, 0, 1);
	glutSolidSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();

	
	//draw planet 2 moon 2
	glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(-0.75f, 0, 0); // Verschiebung
	glRotatef(-rotateTmp * 2, 0, 0, 1);
	glutSolidSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();

	//draw planet 2 moon 3
	glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(0.75f, 0, 0.75f); // Verschiebung
	glRotatef(-rotateTmp * 2, 0, 0, 1);
	glutSolidSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();

	//draw planet 2 moon 4
	glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(-0.75f, 0, -0.75f); // Verschiebung
	glRotatef(-rotateTmp * 2, 0, 0, 1);
	glutSolidSphere(0.1f, 7, 7); // planet 1

	glPopMatrix();
	glPopMatrix();
	
	rotateTmp += 0.2f;
	if (rotateTmp == 360){
		rotateTmp = 0;
	}

}



void display(void)
{
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//drawRect();
	//drawcircle();
	//drawcube();
	
	drawSphere();
	glutSwapBuffers();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Hintergrundfarbe  (gelb: 1 1 0 0)
	glShadeModel(GL_FLAT);
    //Test......
    glEnable(GL_DEPTH_TEST);
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case '+':
		size = size * 2;		//Kreis vergrern
		glutPostRedisplay();
		break;
	case '-':
		size = size / 2;		//Kreis verkleinern
		glutPostRedisplay();
		break;
	case 'x':
		rotate_x = rotate_x + 1;	//W・fel um x drehen
		sphereXPOS += 0.01f;
		glutPostRedisplay();
		break;
	case 'y':
		rotate_y = rotate_y + 1;	//W・fel um y drehen
		sphereYPOS += 0.01f;
		glutPostRedisplay();
		break;
	case 'z':
		rotate_z = rotate_z + 1;	//W・fel um z drehen
		glutPostRedisplay();
		sphereZPOS += 0.01f;
		break;

	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Aufgabenblatt 1");

	init();

	glEnable(GL_DEPTH_TEST);

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
