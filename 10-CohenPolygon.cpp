#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <algorithm>
using namespace std;

float xmin, ymin, xmax, ymax;

struct Point {
    float x, y;
};

Point original[100], inp[100], outp[100];
int n, clippedN;

enum Edge { LEFT, TOP, RIGHT, BOTTOM };

void drawPoly(Point p[], int n)
{
    if(n < 2) return;

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);

    for(int i=0; i<n; i++)
        glVertex2f(p[i].x, p[i].y);

    glEnd();
}

bool inside(Point p, int edge)
{
    switch(edge) {
        case LEFT:   return p.x >= xmin;
        case TOP:    return p.y <= ymax;
        case RIGHT:  return p.x <= xmax;
        case BOTTOM: return p.y >= ymin;
    }
    return false;
}

Point intersect(Point s, Point p, int edge)
{
    float t, x, y;

    if(edge == LEFT || edge == RIGHT) {
        x = (edge == LEFT) ? xmin : xmax;
        t = (x-s.x)/(p.x-s.x);
        y = s.y + t*(p.y-s.y);
    }
    else {
        y = (edge == BOTTOM) ? ymin : ymax;
        t = (y-s.y)/(p.y-s.y);
        x = s.x + t*(p.x-s.x);
    }

    return {x,y};
}

void sutherlandHodgman()
{
    copy(original, original+n, inp);
    clippedN = n;

    for(int edge=0; edge<4; edge++) {
        int k=0;
        if(clippedN == 0) break;

        Point s = inp[clippedN-1];

        for(int j=0; j<clippedN; j++) {
            Point p = inp[j];

            if(inside(p,edge)) {
                if(!inside(s,edge))
                    outp[k++] = intersect(s,p,edge);

                outp[k++] = p;
            }
            else if(inside(s,edge)) {
                outp[k++] = intersect(s,p,edge);
            }

            s=p;
        }

        clippedN=k;
        copy(outp, outp+clippedN, inp);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Original polygon - Red
    glColor3f(1,0,0);
    drawPoly(original,n);

    // Clipping window - Green
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();

    // Clipped polygon - Blue
    sutherlandHodgman();
    glColor3f(0,0,1);
    drawPoly(inp,clippedN);

    glFlush();
}

void myInit()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    cout << "Enter number of polygon vertices: ";
    cin >> n;

    if(n<3 || n>100) {
        cout << "Invalid number of vertices";
        return 0;
    }

    cout << "Enter polygon vertices (x y):\n";
    for(int i=0; i<n; i++)
        cin >> original[i].x >> original[i].y;

    cout << "Enter clipping window (xmin ymin xmax ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    if(xmin>=xmax || ymin>=ymax) {
        cout << "Invalid clipping window";
        return 0;
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sutherland Hodgman Polygon Clipping");

    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
