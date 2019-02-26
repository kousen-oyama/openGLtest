#include<iostream>
#include<string>
#include"GL/glut.h"

void render_string(float x, float y, const char* string)
{
	float z = -1.0f;
	glColor3f(1,0,0);
	glRasterPos3f(x, y, z);
	char* p = (char*) string;
	while (*p != '\0')
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
}

void display(){

	//数値データを文字列に変換
	int i=1;
	std::string str;
	str=std::to_string(i);
	const char* cs=str.data();

	
	glLoadIdentity();
	render_string(-0.6, 0.3, "OpenGLUT");
	render_string(-0.6, 0.25, cs);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-8.0f);
	glFlush();
}

int main(int argc, char* argv[]){
  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("Practice");
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFlush();
	glutMainLoop();
	return 0;
}
