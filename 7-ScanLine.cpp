#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <algorithm>
using namespace std;

int n;
float x[100], y[100];

void drawLine(float x1, float y1, float x2, float y2)
{
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void edgeDetect(float xa, float ya, float xb, float yb,
                int scan, float ix[], int &count)
{
    if (ya > yb) {
        swap(xa, xb);
        swap(ya, yb);
    }

    if (ya != yb && scan >= ya && scan < yb) {
        float xi = xa + (scan - ya) * (xb - xa) / (yb - ya);
        ix[count++] = xi;
    }
}

void scanFill()
{
    for (int s = 0; s <= 500; s++) {
        float ix[100];
        int count = 0;

        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            edgeDetect(x[i], y[i], x[j], y[j], s, ix, count);
        }

        sort(ix, ix + count);

        for (int i = 0; i + 1 < count; i += 2)
            drawLine(ix[i], s, ix[i+1], s);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    scanFill();

    glColor3f(1, 0, 0);
    glLineWidth(2);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2f(x[i], y[i]);
    glEnd();

    glFlush();
}

void myInit()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    cout << "Enter number of sides (3-100): ";
    cin >> n;

    if (n < 3 || n > 100) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "Enter coordinates of vertices (x y):\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan-Line Area Filling");

    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
