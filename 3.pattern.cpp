#include <GL/glut.h>
#include <cmath>

void plot(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawCircle(float cx, float cy, float r) {
    float x = 0, y = r, d = 3 - 2 * r;
    while (x <= y) {
        plot(cx + x, cy + y); plot(cx - x, cy + y);
        plot(cx + x, cy - y); plot(cx - x, cy - y);
        plot(cx + y, cy + x); plot(cx - y, cy + x);
        plot(cx + y, cy - x); plot(cx - y, cy - x);
        d = (d < 0) ? (d + 4 * x + 6) : (d + 4 * (x - y) + 10), x++;
        if (d >= 0) y--;
    }
}

void drawTriangle(float cx, float cy, float s) {
    float h = (sqrt(3) / 2) * s;
    float x1 = cx - s / 2, y1 = cy - h / 3;
    float x2 = cx + s / 2, y2 = cy - h / 3;
    float x3 = cx,         y3 = cy + 2 * h / 3;
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1); glVertex2f(x2, y2); glVertex2f(x3, y3);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float cx = 400, cy = 400, outerR = 150, side = 260;
    float innerR = side / (2 * sqrt(3));
    glColor3f(0, 1, 1);
    drawCircle(cx, cy, outerR);
    drawTriangle(cx, cy, side);
    drawCircle(cx, cy, innerR);
    glFlush();
}

void setup() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 800, 0, 800);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Pattern");
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
