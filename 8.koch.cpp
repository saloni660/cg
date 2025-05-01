#include <GL/glut.h>
#include <cmath>
#include <iostream>

int iterations;

void koch(int it, float x1, float y1, float x5, float y5) {
    if (it == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x5, y5);
        glEnd();
        return;
    }

    float dx = (x5 - x1) / 3, dy = (y5 - y1) / 3;
    float x2 = x1 + dx, y2 = y1 + dy;
    float x3 = 0.5 * (x1 + x5) + sqrt(3) * (y1 - y5) / 6;
    float y3 = 0.5 * (y1 + y5) + sqrt(3) * (x5 - x1) / 6;
    float x4 = x1 + 2 * dx, y4 = y1 + 2 * dy;

    koch(it - 1, x1, y1, x2, y2);
    koch(it - 1, x2, y2, x3, y3);
    koch(it - 1, x3, y3, x4, y4);
    koch(it - 1, x4, y4, x5, y5);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glLineWidth(2);
    koch(iterations, 100, 300, 700, 300);
    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Enter iterations: ";
    std::cin >> iterations;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve");

    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
