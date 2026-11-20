#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void drawCircle(int xc, int yc, int r)
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float t = 2 * 3.142 * i / 100;
        glVertex2f(xc + r*cos(t), yc + r*sin(t));
    }

    glEnd();
}

void drawCylinder()
{
    int xc = 200, r = 50;
    int yBottom = 150, yTop = 350;

    glColor3f(1, 0, 0);

    drawCircle(xc, yBottom, r);
    drawCircle(xc, yTop, r);

    glBegin(GL_LINES);

    glVertex2f(xc-r, yBottom);
    glVertex2f(xc-r, yTop);

    glVertex2f(xc+r, yBottom);
    glVertex2f(xc+r, yTop);

    glEnd();
}

void drawRectangle(int x1, int x2, int yBottom, int yTop)
{
    glBegin(GL_LINE_LOOP);

    glVertex2f(x1, yBottom);
    glVertex2f(x2, yBottom);
    glVertex2f(x2, yTop);
    glVertex2f(x1, yTop);

    glEnd();
}

void drawParallelepiped()
{
    int x1 = 100, x2 = 300;
    int yBottom = 100, yTop = 300;
    int offset = 60;

    glColor3f(0, 0, 1);

    drawRectangle(x1, x2, yBottom, yTop);

    drawRectangle(x1+offset, x2+offset,
                  yBottom+offset, yTop+offset);

    glBegin(GL_LINES);

    glVertex2f(x1, yBottom);
    glVertex2f(x1+offset, yBottom+offset);

    glVertex2f(x2, yBottom);
    glVertex2f(x2+offset, yBottom+offset);

    glVertex2f(x2, yTop);
    glVertex2f(x2+offset, yTop+offset);

    glVertex2f(x1, yTop);
    glVertex2f(x1+offset, yTop+offset);

    glEnd();
}

void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCylinder();
    glFlush();
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawParallelepiped();
    glFlush();
}

void myInit()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);

    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cylinder");
    myInit();
    glutDisplayFunc(display1);

    glutInitWindowPosition(650, 100);
    glutCreateWindow("Parallelepiped");
    myInit();
    glutDisplayFunc(display2);

    glutMainLoop();
    return 0;
}
