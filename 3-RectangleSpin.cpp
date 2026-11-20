#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
float angle = 0;
int spinWin;

void drawRect()
{
    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0);
    glVertex2f(-150, -150);

    glColor3f(0, 1, 0);
    glVertex2f(-150, 150);

    glColor3f(0, 0, 1);
    glVertex2f(150, 150);

    glColor3f(1, 1, 0);
    glVertex2f(150, -150);

    glEnd();
}

void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawRect();
    glutSwapBuffers();
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle, 0, 0, 1);
    drawRect();

    glutSwapBuffers();
}

void idle()
{
    angle += 0.1;

    if (angle >= 360)
        angle -= 360;

    glutSetWindow(spinWin);
    glutPostRedisplay();
}

void myInit()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);

    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rect 1");
    myInit();
    glutDisplayFunc(display1);

    glutInitWindowPosition(600, 100);
    spinWin = glutCreateWindow("Rect 2");
    myInit();
    glutDisplayFunc(display2);

    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
