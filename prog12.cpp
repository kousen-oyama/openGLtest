#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include"GL/glut.h"

const int BoardSize=8;
const int Black=0;
const int Whitw=1;
const int Wall=2;

void glutDispBoard();
void glutDispStone();
void glutDisp();

void inits();
void keyboard(unsigned char key, int x, int y);
void display();
void resize(int w, int h);

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutCreateWindow("Othero");
	inits();
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void inits(){
	static const int WindowPositionWight=100;
	static const int WindowPositionHeight=100;
	
	static const int WindowSizeWidth=800;
	static const int WindowSizeHeight=800;
	
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(WindowPositionWight, WindowPositionHeight);
	glutInitWindowSize(WindowSizeWidth, WindowSizeHeight);
	gluOrtho2D(0, 800, 800, 0);
	glClearColor(0, 0.5, 0, 1);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 'q':
	case 'Q':
	case '\033':
		std::exit(0);
		break;
	default:
		break;
	}
}

void resize(int w, int h){
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void glutDispBoard(){
 	glClear(GL_COLOR_BUFFER_BIT);
	
	static const int lineSize=4;
	static const int pointSize=12;
	
	//盤面のマス目作成
	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(lineSize);
	glBegin(GL_LINES);    
	for(int i = 0; i <= BoardSize; i++){
		glVertex2i(80 + 80 * i, 720);
		glVertex2i(80 + 80 * i, 80);
        
		glVertex2i(80, 80 + 80 * i);
		glVertex2i(720, 80 + 80 * i);
	}
	glEnd();
    
  //盤面上の4点の描画
	glColor3d(0.0, 0.0, 0.0);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex2i(240, 240);
	glVertex2i(240, 560);
	glVertex2i(560, 240);
	glVertex2i(560, 560);
	glEnd();

	glFlush();
}

void glutDispStone(){
	
}

void display(){
	//丸い点を打つための設定
	//点にアンチエリアシング処理を行う
	glEnable(GL_POINT_SMOOTH);
	//アンチエリアシング処理の品質を最高にする 
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//アルファブレンディングを有効にする 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutDispBoard();
	
};

void consoleDisp(){
	
}
