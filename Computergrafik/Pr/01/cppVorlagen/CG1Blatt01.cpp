#include <GLUT/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <stdio.h>
#include <math.h>


#if !defined(BUFSIZE)
#define BUFSIZE 512
#endif
static int PI=3.1415;



void drawcircle(unsigned int steps)
{
    // Dreiecksfächer zeichnen
    glBegin(GL_TRIANGLE_FAN);
    
    // Zentrum (ertsten Punkt) setzen
    glVertex2f(0.0f, 0.0f);
    
    for (unsigned int i = 0; i <= steps; i++)
    {
        // Umlaufenden Winkel berechnen (Von Radian zu Grad)
        float angle = float(i)/float(steps) * 2.1f * PI;
        
        // Kreisfunktionen Sinus und Cosinus verwenden
        float x = sinf(angle);
        float y = cosf(angle);
        
        // Punkt setzen
        glVertex2f(x, y);
    }
    glEnd();
    //glTranslatef(1,2,1);

}
void drawcube()
{
	
}

void drawRect()
{
	glBegin(GL_POLYGON);
	  glVertex3f(0.25,0.25,0.0);
	  glVertex3f(0.75,0.25,0.0);
	  glVertex3f(0.75,0.75,0.0);
	  glVertex3f(0.25,0.75,0.0);
	glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0, 0, 1);
    //drawRect();
    drawcircle(1000);
    glutSwapBuffers();
}

void init(void) 
{
    //Fensterfarbe
    glClearColor(1,1,0,0);
    glShadeModel(GL_FLAT);
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat) w / (GLfloat) h, 1.0,20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key) {

	case '+':   
            // do something
            glutPostRedisplay();
	    break;
	case '-':
	    // do something
            glutPostRedisplay();
	    break;
	case 'x':   
            // do something
            glutPostRedisplay();
	    break;
	case 'y':
	    // do something
            glutPostRedisplay();
	    break;
	case 'z':
	    // do something
            glutPostRedisplay();
	    break;

	}
	
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 600, 360 );
    glutCreateWindow( "Aufgabenblatt 1" );

    init();

    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
	
    glutMainLoop();
    return 0;		
}
