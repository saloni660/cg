#include <GL/glut.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

vector<Point> vertices;
bool complete = false;

void drawPolygon() {
    glBegin(GL_LINE_LOOP);
    for (auto& p : vertices)
        glVertex2i(p.x, p.y);
    glEnd();
}

void scanlineFill() {
    if (vertices.size() < 3) return;

    int ymin = vertices[0].y, ymax = vertices[0].y;
    for (auto& p : vertices) {
        ymin = min(ymin, p.y);
        ymax = max(ymax, p.y);
    }

    for (int y = ymin; y <= ymax; y++) {
        vector<int> interX;

        for (int i = 0; i < vertices.size(); i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % vertices.size()];
            if (p1.y == p2.y) continue; // skip horizontal edges
            if ((y >= min(p1.y, p2.y)) && (y < max(p1.y, p2.y))) {
                float x = p1.x + (float)(y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                interX.push_back((int)x);
            }
        }

        sort(interX.begin(), interX.end());
        glBegin(GL_LINES);
        for (int i = 0; i < interX.size(); i += 2)
            glVertex2i(interX[i], y), glVertex2i(interX[i+1], y);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    drawPolygon();
    if (complete) {
        glColor3f(1, 1, 0);
        scanlineFill();
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    y = 480 - y; // invert y axis
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !complete) {
        vertices.push_back({x, y});
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        complete = true;
    }
    glutPostRedisplay();
}

void init() {
    gluOrtho2D(0, 640, 0, 480);
    glClearColor(0, 0, 0, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Scanline Polygon Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
