#include<iostream>
#include<cstdlib>
#include"GL/glut.h"

void display();
void keyboard(unsigned char key, int x, int y);
void keyboardup(unsigned char key, int x, int y);
void specialkeydown(int key, int x, int y);

void glutCallFunc(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(specialkeydown);
}

void init(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutIgnoreKeyRepeat(GL_TRUE);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	std::cout<<"("<<x<<","<<y<<")"<<key<<std::endl;
	switch(key){
	case 'q':
	case 'Q':
		std::exit(0);
		break;
	default:
		break;
	}
}


void keyboardup(unsigned char key, int x, int y){
	std::cout<<"("<<x<<","<<y<<")"<<key<<std::endl;
}

void specialkeydown(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		std::cout<<"up"<<std::endl;
		break;
		
	case GLUT_KEY_DOWN:
		std::cout<<"down"<<std::endl;
		break;

	case GLUT_KEY_RIGHT:
		std::cout<<"right"<<std::endl;
		break;

	case GLUT_KEY_LEFT:
		std::cout<<"left"<<std::endl;
		break;
	}
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutCreateWindow("keyboard test");
	gluOrtho2D(0, 800, 800,0);  //座標系の設
	glutCallFunc();
	init();
	glutMainLoop();
	return 0;
}
