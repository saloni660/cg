#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

float X1 = 400,Y1 = 400,R = 300;

void plot(float x,float y){
	glBegin(GL_POINTS);
	glColor3f(1,1,0);
	glVertex2f(x,y);
	glEnd();
}

void circle(){
	float x = 0, y = R;
	float D = 5/4 - R;
	plot(x,y);
	while(x<y){
		if(D<0){
			D+=2*x - 1;
			x++;
		}else{
			D+=2*(x-y) -1;
			x++;
			y--;		
		}
		plot(X1+x,Y1+y);
		plot(X1-x,Y1+y);
		plot(X1+x,Y1-y);
		plot(X1-x,Y1-y);
		plot(X1+y,Y1+x);
		plot(X1-y,Y1+x);
		plot(X1+y,Y1-x);
		plot(X1-y,Y1-x);
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	circle();
	glFlush();
}

void setup(){
	glViewport(0,0,800,800);
	glOrtho(0,800,0,800,-1,1);
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800,800);
	glutCreateWindow("jai shree ram");
	setup();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
