/*
 *
 * File: planets.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GLUT/glut.h>

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512

void init_gfx(void)
{
    glClearColor(0,0,0,0);

    /*
     * Projektionsmatrix mit der Einheitsmatrix initialisieren
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*
     * Weltkoordinatensystem auf [0,1]x[0,1]x[0,1] festlegen
     * (Parallelprojektion)
     * letzter Parameter negativ wegen: (siehe man-page von glOrtho())
     */
    glOrtho( 0.0,1.0, 0.0,1.0, 0.0,-1.0 );

    glMatrixMode(GL_MODELVIEW);
}

void drawscene(void)
{
    static double    rot_sphere1=0.0;

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslated(0.5,0.5,0.5);

    glPushMatrix();

    /* Sonne */
    glRotated(rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(0.1,12,12);

    glPopMatrix();

    glPushMatrix();

    /* Planet 1 */
    glRotated(2.0*rot_sphere1, 0.0, 0.0, 1.0);
    glTranslated(0.2,0.0,0.0);
    glRotated(3.0*rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 1.0);
    glutWireSphere(0.03,12,12);

    /* Mond 1.1 */
    glRotated(5.0*rot_sphere1, 0.0, 0.0, 1.0);
    glTranslated(0.05,0.0,0.0);
    glRotated(-15.0*rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(0.5, 0.5, 0.5);
    glutWireSphere(0.01,6,6);

    glPopMatrix();

    /* Planet 2 */
    glRotated(7.0*rot_sphere1, 0.0, 0.0, 1.0);
    glTranslated(0.0,0.35,0.0);
    glRotated(2.0*rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(0.03,12,12);

    glPushMatrix();

    /* Mond 2.1 */
    glRotated(18.0*rot_sphere1, 0.0, 0.0, 1.0);
    glTranslated(0.05,0.0,0.0);
    glRotated(17.0*rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(0.01,6,6);

    glPopMatrix();

    /* Mond 2.2 */
    glRotated(-14.0*rot_sphere1, 0.0, 0.0, 1.0);
    glTranslated(0.0,0.08,0.0);
    glRotated(-20.0*rot_sphere1, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(0.015,8,8);

    glFlush();
    glFinish();
    glutSwapBuffers();

    rot_sphere1+=0.1;
    while(rot_sphere1>=360.0) rot_sphere1-=360.0;
}

void reshape_gfx(int w, int h)
{
    glViewport(0, 0, w, h);
}

void keyboard_input(unsigned char key, int x, int y)
{
    switch(key) {
        case  27: exit(0); break;
        default: printf(" Key pressed: >%c< (%d) at position x=%d y=%d\n",key,key,x,y); break;
        }
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape_gfx);
    glutDisplayFunc(drawscene);
    glutIdleFunc(drawscene);
    glutKeyboardFunc(keyboard_input);

    init_gfx();

    glutMainLoop();
}
