#include <iostream>
#include <GL/glut.h>
using namespace std;

int x1, y1, x2, y2;
bool firstClick = true, drawLine = false;
const int xmin = 100, yminC = 100, xmax = 700, ymaxC = 500;
enum { LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8 };

int getCode(int x, int y) {
    int code = 0;
    if (x < xmin) code |= LEFT; if (x > xmax) code |= RIGHT;
    if (y < yminC) code |= BOTTOM; if (y > ymaxC) code |= TOP;
    return code;
}

void cohenSutherland() {
    int c1 = getCode(x1, y1), c2 = getCode(x2, y2);
    while (true) {
        if (!(c1 | c2)) break;
        else if (c1 & c2) { drawLine = false; return; }
        int cx = c1 ? c1 : c2, x, y;
        if (cx & TOP)    { x = x1 + (x2 - x1) * (ymaxC - y1) / (y2 - y1); y = ymaxC; }
        else if (cx & BOTTOM){ x = x1 + (x2 - x1) * (yminC - y1) / (y2 - y1); y = yminC; }
        else if (cx & RIGHT) { y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1); x = xmax; }
        else              { y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1); x = xmin; }

        if (cx == c1) { x1 = x; y1 = y; c1 = getCode(x1, y1); }
        else          { x2 = x; y2 = y; c2 = getCode(x2, y2); }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0); // Clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, yminC); glVertex2i(xmax, yminC);
    glVertex2i(xmax, ymaxC); glVertex2i(xmin, ymaxC);
    glEnd();

    if (drawLine) {
        glColor3f(1, 1, 0);
        glBegin(GL_LINES); glVertex2i(x1, y1); glVertex2i(x2, y2); glEnd();
    }
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    y = 600 - y;
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick) { x1 = x; y1 = y; firstClick = false; }
        else { x2 = x; y2 = y; drawLine = true; firstClick = true; glutPostRedisplay(); }
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && drawLine) {
        cohenSutherland(); glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); glutCreateWindow("Cohen-Sutherland - C++");
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display); glutMouseFunc(mouse);
    glClearColor(0, 0, 0, 1);
    glutMainLoop(); return 0;
}
