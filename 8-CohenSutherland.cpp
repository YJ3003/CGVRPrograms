#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

const int LEFT=8, RIGHT=4, BOTTOM=2, TOP=1;

float xmin, ymin, xmax, ymax;
int n;
float lines[100][4];

int compute(float x, float y)
{
    int c=0;

    if(y>ymax) c|=TOP;
    else if(y<ymin) c|=BOTTOM;

    if(x>xmax) c|=RIGHT;
    else if(x<xmin) c|=LEFT;

    return c;
}

bool clip(float &x0, float &y0, float &x1, float &y1)
{
    int c0=compute(x0,y0), c1=compute(x1,y1);

    while(true)
    {
        if(!(c0|c1)) return true;
        if(c0&c1) return false;

        float x,y,dx=x1-x0,dy=y1-y0;
        int c=c0?c0:c1;

        if(c&TOP) {
            y=ymax;
            x=x0+dx*(ymax-y0)/dy;
        }
        else if(c&BOTTOM) {
            y=ymin;
            x=x0+dx*(ymin-y0)/dy;
        }
        else if(c&RIGHT) {
            x=xmax;
            y=y0+dy*(xmax-x0)/dx;
        }
        else {
            x=xmin;
            y=y0+dy*(xmin-x0)/dx;
        }

        if(c==c0) {
            x0=x; y0=y;
            c0=compute(x0,y0);
        }
        else {
            x1=x; y1=y;
            c1=compute(x1,y1);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw original lines in red
    glColor3f(1,0,0);
    glLineWidth(1);
    glBegin(GL_LINES);

    for(int i=0;i<n;i++) {
        glVertex2f(lines[i][0],lines[i][1]);
        glVertex2f(lines[i][2],lines[i][3]);
    }

    glEnd();

    // Draw clipping window in green
    glColor3f(0,1,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);

    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);

    glEnd();

    // Draw clipped lines in blue
    glColor3f(0,0,1);
    glLineWidth(3);
    glBegin(GL_LINES);

    for(int i=0;i<n;i++) {
        float x0=lines[i][0], y0=lines[i][1];
        float x1=lines[i][2], y1=lines[i][3];

        if(clip(x0,y0,x1,y1)) {
            glVertex2f(x0,y0);
            glVertex2f(x1,y1);
        }
    }

    glEnd();
    glFlush();
}

void myInit()
{
    glClearColor(1,1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc,char** argv)
{
    cout<<"Enter clipping window (xmin ymin xmax ymax): ";
    cin>>xmin>>ymin>>xmax>>ymax;

    cout<<"Enter number of lines: ";
    cin>>n;

    if(xmin>=xmax || ymin>=ymax || n<1 || n>100) {
        cout<<"Invalid input!";
        return 1;
    }

    cout<<"Enter line coordinates (x0 y0 x1 y1):\n";

    for(int i=0;i<n;i++)
        cin>>lines[i][0]>>lines[i][1]
           >>lines[i][2]>>lines[i][3];

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cohen Sutherland Line Clipping");

    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
