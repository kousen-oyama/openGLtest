#include <iostream>
#include <GL/glut.h>

#define BOARD_SIZE 8
#define NONE 0
#define BLACK 1
#define WHITE 2

using namespace std;
int screenWidth = 800, screenHeight = 800;
char board[BOARD_SIZE][BOARD_SIZE];


void showStone(){
    //���̤����֤��줿�Ф�����
    glPointSize(60);
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] == BLACK){
                //���Ф�����
                glColor3d(0, 0, 0);
                glBegin(GL_POINTS);
                glVertex2i(120 + 80 * i, 120 + 80 * j);
                glEnd();
            }else if(board[i][j] == WHITE){
                //���Ф�����
                glColor3d(1, 1, 1);
                glBegin(GL_POINTS);
                glVertex2i(120 + 80 * i, 120 + 80 * j);
                glEnd();
            }
        }
    }
}

void display(){
	glClearColor(0, 0.5, 0, 1); //�طʿ�����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //���̤Υޥ��ܺ���
    glColor3d(0.0, 0.0, 0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    
    for(int i = 0; i <= BOARD_SIZE; i++){
        glVertex2i(80 + 80 * i, 720);
        glVertex2i(80 + 80 * i, 80);
        
        glVertex2i(80, 80 + 80 * i);
        glVertex2i(720, 80 + 80 * i);
    }
    glEnd();
    
    //���̾��4��������
    glColor3d(0.0, 0.0, 0.0);
    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex2i(240, 240);
        glVertex2i(240, 560);
        glVertex2i(560, 240);
        glVertex2i(560, 560);
    glEnd();
    
    showStone();
    glFlush();  //����¹�
}

void initialize(){
    //�����������
    
    //�ʲ��Фν������
    for(int i; i < BOARD_SIZE * BOARD_SIZE; i++)
        board[i / BOARD_SIZE][i % BOARD_SIZE] = NONE;
    
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = BLACK;
    board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = BLACK;
    
    board[BOARD_SIZE / 2][BOARD_SIZE / 2] = WHITE;
    board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = WHITE;
}

void inits(){
	static const int WindowPositionWight=100;
	static const int WindowPositionHeight=100;
	
	static const int WindowSizeWidth=800;
	static const int WindowSizeHeight=800;
	
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(WindowPositionWight, WindowPositionHeight);
	glutInitWindowSize(WindowSizeWidth, WindowSizeHeight);
	glClearColor(0, 0.5, 0, 1);
}


int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);

		inits();
    
    glutCreateWindow("Othello");
    gluOrtho2D(0, 800, 800, 0); //��ɸ�ϻ���
    initialize();
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

