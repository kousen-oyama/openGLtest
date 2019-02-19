#include<iostream>
#include <GL/glut.h>

#define MAXPOINT 100

GLint point[MAXPOINT][2];
int pointnum=0;

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	if(pointnum>1){
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for(int i=0;i<pointnum;++i){
			glVertex2iv(point[i]);
		}
		glEnd();
	}
}

void init(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
  static int x0, y0;
  switch (button) {
  case GLUT_LEFT_BUTTON:
		point[pointnum][0]=x;
		point[pointnum][1]=y;
    if (state == GLUT_UP) {
      glColor3d(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
			glVertex2iv(point[pointnum-1]);
			glVertex2iv(point[pointnum]);
      glEnd();
      glFlush();
    }
		if(pointnum<MAXPOINT-1)
			++pointnum;
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;
  default:
    break;
  }
}

int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 240);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("DrowLine");
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  init();
  glutMainLoop();
  return 0;
}
