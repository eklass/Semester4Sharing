/*
*
* File: planets.c
*
*/

#include <GLUT/GLUT.h>

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

#if !defined(BUFSIZE)
#define BUFSIZE 512
#endif

float size = 1;			//Kreisgröße
float rotate_x = 0;		//WEfelausrichtung
float rotate_y = 0;
float rotate_z = 0;
float sphereXPOS = 0.0f;
float sphereYPOS = 0.0f;
float sphereZPOS = 0.0f;
float color = 1;
float jahrtag = 60;
float mondtag = 15;
float grad = 45;
float zahl = 0;
float faktor=1;


float ORG[3] = { 0, 0, 0 };
float XP[3] = { 5, 0, 0 }, XN[3] = { -5, 0, 0 },
YP[3] = { 0, 5, 0 }, YN[3] = { 0, -5, 0 },
ZP[3] = { 0, 0, 5 }, ZN[3] = { 0, 0, -5 };


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

	glColor3f(0.0f, 1.0f, 0.0f); // GrE
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

void drawSphere(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();


	static float rotateTmp = 0;
	static float rotateTmp2 = 0;
	static float rotateTmp3 = 0;

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

    static float rtmp=1;
    static int toggle=1;
	//draw sun
    if(toggle){
        rtmp-=0.01f;
    } else {
        rtmp+=0.01f;
    }
    if(rtmp<=0.0f){
        toggle = 0;
    } else if(rtmp >=1.0f){
        toggle = 1;
    }
	glPushMatrix();
	if (color == 1)
	{
		glColor3f(rtmp, 0.0f, 1.0f);
		glPushMatrix();
		glutWireSphere(0.75, 35, 35);
		glPopMatrix();
	}
	else
	{
		glColor3f(1.0, 1.0, 0.0);
		glPushMatrix();
		glutWireSphere(0.75, 35, 35);
		glPopMatrix();
	}
	glPopMatrix();
	

    /*//andere Version
     //draw planet1
     glColor3f(0, 1, 1);
     glPushMatrix();
     glRotatef(rotateTmp*10, 0, 1, 0);
     glTranslatef(2.0f, 0, 0); // Verschiebung
     glRotatef(rotateTmp * 10, 0, -1, 0);
     glRotatef(grad, 1, 0, 0); // 45‹ Neigung
     glPushMatrix();
     glRotatef(rotateTmp * 10, 0, 1, 0);
     glutWireSphere(0.25f, 15, 15); // planet 1*/
     
     
    

	//draw planet1
	glColor3f(0, 1, 1);
	glPushMatrix();
	glRotatef(rotateTmp*10, 0, 1, 0);
	glTranslatef(2.0f, 0, 0); // Verschiebung
	glRotatef(grad, 1, 0, 0); // 45‹ Neigung
	glRotatef(-rotateTmp * 3, 0, 0, 1);
	glutWireSphere(0.25f, 15, 15); // planet 1

	//planet1 axis
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0.5f);
	glVertex3f(0, 0, -0.5f);
	glEnd();

	drawcircle(0.3);
	drawcircle(0.31);
	drawcircle(0.32);
	drawcircle(0.33);
	drawcircle(0.34);
	drawcircle(0.35);
//    glPopMatrix();

	//draw planet 1 moon 1
	glColor3f(1, 0, 1);
	glPushMatrix();
	glRotatef(-rotateTmp * 3, 0, 0, 1);
	glTranslatef(0.75f, 0, 0); // Verschiebung
	glutWireSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();

	//draw planet 1 moon 2
	glColor3f(1, 0, 1);
	glPushMatrix();
	glRotatef(-rotateTmp * 3, 0, 0, 1);
	glTranslatef(-0.75f, 0, 0); // Verschiebung
	glutWireSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();
	glPopMatrix();

	//draw planet2
	glColor3f(0, 1, 1);
	glPushMatrix();
	glRotatef(rotateTmp2/60, 0, 1, 0);
	glTranslatef(-3, 0, 0);
	glRotatef(-rotateTmp2/60, 0, 1, 0);
	glutWireSphere(0.5f, 15, 15);


	//draw planet 2 moon 1
	glColor3f(1, 0, 1);
	glPushMatrix();
    glRotatef(-rotateTmp3/10,0,1,0);
	glTranslatef(0.75f, 0, 0); // Verschiebung
	glRotatef(-rotateTmp3/10, 0, 0, 1);
	glutWireSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();


	//draw planet 2 moon 2
	/*glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(-0.75f, 0, 0); // Verschiebung
	glRotatef(-rotateTmp3 * 2, 0, 0, 1);
	glutWireSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();*/

	//draw planet 2 moon 3
	/*glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(0.75f, 0, 0.75f); // Verschiebung
	glRotatef(-rotateTmp3 * 2, 0, 0, 1);
	glutWireSphere(0.1f, 7, 7); // planet 1
	glPopMatrix();*/

	//draw planet 2 moon 4
	/*glColor3f(1, 0, 1);
	glPushMatrix();
	glTranslatef(-0.75f, 0, -0.75f); // Verschiebung
	glRotatef(-rotateTmp3 * 2, 0, 0, 1);
	glutWireSphere(0.1f, 7, 7); // planet 1

	glPopMatrix();*/
	glPopMatrix();

	rotateTmp += 0.02f;
    rotateTmp2 += 360/jahrtag;
    rotateTmp3 += jahrtag / mondtag/faktor;

    
	if (zahl==1200)
	{
		color = 0;
		glutPostRedisplay();
	}
	zahl = zahl + 1;
//	if (rotateTmp == 360){
//		rotateTmp = 0;
//	}
//	if (rotateTmp2 == 360){
//		rotateTmp2 = 0;
//	}
//	if (rotateTmp3 == jahrtag){
//		rotateTmp3 = 0;
//	}

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
		size = size * 2;		//Kreis vergrößern
		glutPostRedisplay();
		break;
	case 'w':
		if (grad <= 360 & grad >= 0)
		{
			grad = grad - 5;
		}
		else
		{
			grad = 360;
		}
		glutPostRedisplay();
		break;
	case 'W':
		if (grad <= 360 & grad >= 0)
		{
			grad = grad + 5;
		}
		else
		{
			grad = 0;
		}
		glutPostRedisplay();
		break;
	case 'j':
        if (jahrtag <= 360 & jahrtag >= 0)
        {
            jahrtag = jahrtag *2;
        }
        else
        {
            jahrtag = 360;
        }
            glutPostRedisplay();
		break;
	case 'J':
            if (jahrtag <= 360 & jahrtag >= 0)
            {
                jahrtag = jahrtag /2;
            }
            else
            {
                jahrtag = 360;
            }
		glutPostRedisplay();
		break;
	case 'm':
        if (mondtag <= 360 & mondtag >= 0)
            {
            mondtag = mondtag *2;
            faktor=faktor*2;
        }
        else
        {
            mondtag = 360;
            faktor=1;
        };
		glutPostRedisplay();
		break;
	case 'M':
            if (mondtag <= 360 & mondtag >= 0)
            {
                mondtag = mondtag / 2;
                faktor=faktor/2;
            }
            else
            {
                mondtag = 360;
                faktor=1;
            };
		glutPostRedisplay();
		break;
	case '-':
		size = size / 2;		//Kreis verkleinern
		glutPostRedisplay();
		break;
	case 'x':
		rotate_x = rotate_x + 1;	//WEfel um x drehen
		sphereXPOS += 0.01f;
		glutPostRedisplay();
		break;
	case 'y':
		rotate_y = rotate_y + 1;	//WEfel um y drehen
		sphereYPOS += 0.01f;
		glutPostRedisplay();
		break;
	case 'z':
		rotate_z = rotate_z + 1;	//WEfel um z drehen
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