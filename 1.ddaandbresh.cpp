#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int method = 0;
float X1, Y1, X2, Y2;

void drawDDA() {
	float dx = X2 - X1;
	float dy = Y2 - Y1;
	float x_inc = dx / max(dx,dy);
	float y_inc = dy / max(dx,dy);
	float  x=X1 , y=Y1;
	glBegin(GL_POINTS);
	while(x!=X2 && y!=Y2){
		glVertex2f((int)x, (int)y);
		x += x_inc;
		y += y_inc;
	}					
	glEnd();	
}

void drawBresenham() {
	int dx = X2 - X1;
	int dy = Y2 - Y1;	
	int D = 2*dy - dx;
	int x=X1,y=Y1;
	int sx = (X2>X1)? 1:-1;
	int sy = (Y2>Y1)? 1: -1;
	glBegin(GL_POINTS);
	while(x!=X2){
		glVertex2f(x,y);
		x+=sx;
		if(D<0)D += 2*dy;
		if(D>0){
			D += 2*dy - 2*dx;
			y+=sy;
		}	
	}	
	glEnd();	
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    if (method == 1) drawDDA();
    else if (method == 2) drawBresenham();
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == '1') method = 1;
    else if (key == '2') method = 2;
    else if (key == 'q' || key == 'Q') exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    cout << "Enter (x1 y1): "; cin >> X1 >> Y1;
    cout << "Enter (x2 y2): "; cin >> X2 >> Y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Line Drawing (1-DDA, 2-Bresenham)");
    gluOrtho2D(0, 800, 0, 800);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    cout << "\n[1] DDA\n[2] Bresenham\n[q] Quit\n";
    glutMainLoop();
    return 0;
}
