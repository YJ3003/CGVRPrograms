#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

int xc, yc, r;
bool ready = false;

void draw8Pixel(int x, int y)
{
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);

    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

void drawCircle()
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glColor3f(0, 1, 0);
    glPointSize(3);
    glBegin(GL_POINTS);

    while (x <= y)
    {
        draw8Pixel(x, y);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }

        x++;
    }

    glEnd();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (ready)
        drawCircle();
}

void mouse(int button, int state, int x, int y)
{
    static int count = 0;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (count == 0)
        {
            xc = x - 250;
            yc = 250 - y;
            ready = false;
        }
        else
        {
            int xb = x - 250;
            int yb = 250 - y;
            r = hypot(xb - xc, yb - yc);
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
        cout << "Enter xc, yc and radius: ";
        cin >> xc >> yc >> r;
        ready = true;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Drawing");

    myInit();
    glutDisplayFunc(display);

    if (choice == 2)
        glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
