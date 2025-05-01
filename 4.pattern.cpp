#include <GL/glut.h>

int width = 800, height = 800, cx = 400, cy = 400;
float r = 142;

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1); glVertex2i(x2, y2);
    glEnd();
}

void plotCirclePoints(int x, int y) {
    int pts[][2] = {{x,y},{-x,y},{x,-y},{-x,-y},{y,x},{-y,x},{y,-x},{-y,-x}};
    glBegin(GL_POINTS);
    for (auto& p : pts) glVertex2i(cx + p[0], cy + p[1]);
    glEnd();
}

void drawCircle() {
    int x = 0, y = r;
    float d = 1 - r;
    while (y >= x) {
        plotCirclePoints(x, y);
        x++;
        d += (d < 0) ? 2 * x + 1 : 2 * (x - y--) + 1;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5, 0.75, 0.25); glLineWidth(5);
    drawLine(200,200,200,600); drawLine(600,200,600,600);
    drawLine(200,200,600,200); drawLine(200,600,600,600);

    glColor3f(0.0, 1.0, 1.0); glLineWidth(2);
    drawLine(200,400,400,200); drawLine(400,200,600,400);
    drawLine(600,400,400,600); drawLine(400,600,200,400);

    glColor3f(1,1,1); glPointSize(2);
    drawCircle();

    glFlush();
}

void init() {
    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Pattern");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
