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
	//ラインを描く
	glColor3f(0,0,0);
	glLineWidth(3);//線幅の指定。省略可。指定しなければ1。
	glBegin(GL_LINES);
	for(int i=0;i<9;i++){
		glVertex2i(80+80*i,720);//縦線上端
		glVertex2i(80+80*i,80);//縦線下端
		glVertex2i(80,80+80*i);//横線左端
		glVertex2i(720,80+80*i);//横線右端
	}
	glEnd();

	//点を4箇所描く
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
	glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("Othello");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	gluOrtho2D(0, 800, 800,0);//座標系の設定
	glutDisplayFunc(display);//描画関数を指定
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}
