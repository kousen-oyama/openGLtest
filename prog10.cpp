#include<GL/glut.h>
#include<iostream>
class Test{
private:
public:
	static void board(){
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
  void disp(){
		glutDisplayFunc(this->board);
	}
};

class Test2{
private:
	
public:
	Test test;
	
};

Test2 test2;

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("test");
	test2.test.disp();
	glutMainLoop();
}	
