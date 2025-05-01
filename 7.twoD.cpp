#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int m[20][3], n = 0;

void draw() {
    glColor3f(1, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) glVertex2i(m[i][0], m[i][1]);
    glEnd(); glFlush();
}

void transform(float t[3][3]) {
    for (int i = 0; i < n; i++) {
        int x = m[i][0], y = m[i][1];
        m[i][0] = t[0][0]*x + t[0][1]*y + t[0][2];
        m[i][1] = t[1][0]*x + t[1][1]*y + t[1][2];
    }
    draw();
}

void translate() {
    int tx, ty;
    cout << "Translate X Y: "; cin >> tx >> ty;
    float t[3][3] = { {1,0,tx}, {0,1,ty}, {0,0,1} };
    transform(t);
}

void scale() {
    float sx, sy, cx = 0, cy = 0;
    cout << "Scale X Y: "; cin >> sx >> sy;
    for (int i = 0; i < n; i++) cx += m[i][0], cy += m[i][1];
    cx /= n; cy /= n;
    for (int i = 0; i < n; i++) {
        m[i][0] = (m[i][0] - cx) * sx + cx;
        m[i][1] = (m[i][1] - cy) * sy + cy;
    }
    draw();
}

void rotate() {
    float deg;
    cout << "Rotate (deg): "; cin >> deg;
    float r = deg * 3.14159 / 180;
    float t[3][3] = { {cos(r), -sin(r), 0}, {sin(r), cos(r), 0}, {0, 0, 1} };
    transform(t);
}

void menu(int choice) {
    glColor3f(1, 1, 1);
    draw();
    if (choice == 1) translate();
    else if (choice == 2) rotate();
    else if (choice == 3) scale();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && n < 20) {
        m[n][0] = x - 250; m[n][1] = 250 - y; m[n][2] = 1; n++;
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS); glVertex2i(m[n-1][0], m[n-1][1]); glEnd(); glFlush();
    }
}

void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-250, 250, -250, 250);
    glClear(GL_COLOR_BUFFER_BIT); glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc([](){ glFlush(); });
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Rotate", 2);
    glutAddMenuEntry("Scale", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
