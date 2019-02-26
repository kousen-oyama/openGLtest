#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"GL/glut.h"

//void display();
void mouse(int button, int state, int x, int y);
void DrugMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void resize(int w, int h);

int ButtonState=0;



class Calls{
private:
public:
	//staticなメンバ関数にするとメンバ関数のポインタが渡せる。
	static void display(){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
	void calls(){
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutMotionFunc(DrugMotion);
		glutKeyboardFunc(keyboard);
	}
};

Calls call;



void calls(){
	glutDisplayFunc(call.display);
	glutMouseFunc(mouse);
	glutMotionFunc(DrugMotion);
	glutKeyboardFunc(keyboard);
}

void inits(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(resize);
	glutInitWindowSize(800,800); 
	glutInitWindowPosition(0, 0);
	gluOrtho2D(0, 800, 800,0);
}

//void display(){
//	glClear(GL_COLOR_BUFFER_BIT);
//	glFlush();
//}

void mouse(int button, int state, int x, int y){
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		std::cout<<"("<<x<<","<<y<<")"<<std::endl;
		ButtonState=1;
	}
	else
		if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP){
			ButtonState=0;
		}
}

void DrugMotion(int x, int y){
		if(ButtonState==1){
		std::cout<<"DrugMotion("<<x<<","<<y<<")"<<std::endl;
	}
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'q':
	case 'Q':
		std::exit(0);
	}
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("mouse test");
		call.calls();
	//	calls();
	inits();
	glutMainLoop();
	return 0;
}
