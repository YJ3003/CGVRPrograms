#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

int xc1, yc1, xc2, yc2;
bool ready = false;

void drawLine()
{
    int dx = abs(xc2 - xc1);
    int dy = abs(yc2 - yc1);

    int sx = (xc1 < xc2) ? 1 : -1;
    int sy = (yc1 < yc2) ? 1 : -1;

    int x = xc1, y = yc1;

    glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);

    if (dx > dy)
    {
        int p = 2 * dy - dx;

        for (int i = 0; i <= dx; i++)
        {
            glVertex2i(x, y);

            if (p > 0)
            {
                y += sy;
                p += 2 * (dy - dx);
            }
            else
                p += 2 * dy;

            x += sx;
        }
    }
    else
    {
        int p = 2 * dx - dy;

        for (int i = 0; i <= dy; i++)
        {
            glVertex2i(x, y);

            if (p > 0)
            {
                x += sx;
                p += 2 * (dx - dy);
            }
            else
                p += 2 * dx;

            y += sy;
        }
    }

    glEnd();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (ready)
        drawLine();
}

void mouse(int button, int state, int x, int y)
{
    static int count = 0;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (count == 0)
        {
            xc1 = x - 250;
            yc1 = 250 - y;
            ready = false;
        }
        else
        {
            xc2 = x - 250;
            yc2 = 250 - y;
            ready = true;
        }

        count = 1 - count;
        glutPostRedisplay();
    }
}

void myInit()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    int choice;

    cout << "1. Keyboard  2. Mouse: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter x1 y1: ";
        cin >> xc1 >> yc1;

        cout << "Enter x2 y2: ";
        cin >> xc2 >> yc2;

        ready = true;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line");

    myInit();
    glutDisplayFunc(display);

    if (choice == 2)
        glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}