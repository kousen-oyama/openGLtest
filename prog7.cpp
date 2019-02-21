#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	#include <GL/glut.h> 
	//#include <GL/glut.h> 
#endif
#include<cstdlib>

void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�饤�������
	glColor3f(0,0,0);
	glLineWidth(3);//�����λ��ꡣ��ά�ġ����ꤷ�ʤ����1��
	glBegin(GL_LINES);
	for(int i=0;i<9;i++){
		glVertex2i(80+80*i,720);//������ü
		glVertex2i(80+80*i,80);//������ü
		glVertex2i(80,80+80*i);//������ü
		glVertex2i(720,80+80*i);//������ü
	}
	glEnd();

	//����4�ս�����
	glColor3f(0,0,0);
	glPointSize(10);
	glBegin(GL_POINTS);
	  glVertex2i(240,240);
		glVertex2i(240,560);
		glVertex2i(560,240);
		glVertex2i(560,560);
	glEnd();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
	case 'q':
	case 'Q':
	case '\033':
		std::exit(0);
	default:
		break;
	}	
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(800,800);//������ɥ��β��̤����ȹ⤵�����
	glutInitWindowPosition(0, 0);//������ɥ��ξ������
	glutCreateWindow("Othello");//������ɥ���̾��
	glClearColor( 0 , 0.7, 0, 1);//�������פο�
	gluOrtho2D(0, 800, 800,0);//��ɸ�Ϥ�����
	glutDisplayFunc(display);//����ؿ������
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}
