#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define W 6                        /* 台の幅の２分の１　 */
#define D 6                        /* 台の長さの２分の１ */
#define CYCLE 600                  /* 一周分のフレーム数 */
#define GR (D * 0.1)               /* ゴンドラの半径　　 */
#define GD (D * 0.05)              /* ゴンドラの幅　　　 */
#define WR (W * 0.6)               /* 観覧車の半径　　　 */
#define SR (W * 0.01)              /* 支柱の半径　　　　 */
#define NG 8                       /* ゴンドラの数　　　 */

#define PI 3.1415926535897932      /* 円周率　　　　　　 */

/*
 *   床を描く
 */
static void myGround(double height)
{
  const static GLfloat ground[][4] = {   /* 台の色　　　 */
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  glBegin(GL_QUADS);

  glNormal3d(0.0, 1.0, 0.0);
  for (int j = -D; j < D; ++j) {
    for (int i = -W; i < W; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, height, (GLdouble)j);
      glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
    }
  }

  glEnd();
}

/*
 * 円柱を描く
 */
static void myCylinder(double radius, double height, int sides)
{
  double step = 6.2831853072 / (double)sides;
  int i = 0;

  /* 後面 */
  glNormal3d(0.0, 0.0, -1.0);
  glBegin(GL_TRIANGLE_FAN);
  while (i < sides) {
    double t = step * (double)i++;
    glVertex3d(radius * sin(t), radius * cos(t), 0.0);
  }
  glEnd();

  /* 前面 */
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_TRIANGLE_FAN);
  while (--i >= 0) {
    double t = step * (double)i;
    glVertex3d(radius * sin(t), radius * cos(t), height);
  }
  glEnd();

  /* 側面 */
  glBegin(GL_QUAD_STRIP);
  while (i <= sides) {
    double t = step * (double)i++;
    double x = sin(t);
    double y = cos(t);

    glNormal3d(x, y, 0.0);
    glVertex3f(radius * x, radius * y, 0.0);
    glVertex3f(radius * x, radius * y, height);
  }
  glEnd();
}

/*
 * 画面表示
 */
static void display(void)
{
  const static GLfloat lightpos[] = { -3.0, 4.0, 5.0, 1.0 }; /* 光源の位置　　　 */
  const static GLfloat orange[] = { 0.9, 0.4, 0.1, 1.0 };    /* ゴンドラの色　　 */
  const static GLfloat white[] = { 0.9, 0.9, 0.9, 1.0 };     /* 支柱の色　　　　 */
  static int frame = 0;                                      /* 現在のフレーム数 */
  int i;

  /* CYCLE フレームごとに 0 -> 1 に変化 */
  double t = (double)frame / (double)CYCLE;

  /* フレーム数（画面表示を行った回数）をカウントする */
  if (++frame >= CYCLE) frame = 0;

  /* 画面クリア */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* 視点の移動（物体の方を奥に移す）*/
  glTranslated(0.0, 0.0, -10.0);

  /* 地面の描画 */
  myGround(-(WR + GR + GR));

  for (i = 0; i < NG; ++i) {
    glRotated(360.0 / (double)NG, 0.0, 0.0, 1.0);

    /* ゴンドラの描画 */
    glPushMatrix();
    {
      glTranslated(WR, 0.0, 0.0);
      glTranslated(0.0, GR * (-0.8), -GD); /* ゴンドラの支点 */
      glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
      myCylinder(GR, GD * 2.0, 32);
    }
    glPopMatrix();

    /* 支柱の描画 */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glPushMatrix();
    {
      glRotated(90.0, 0.0, 1.0, 0.0);
      glPushMatrix();
      {
        glTranslated(GD + SR, 0.0, 0.0);
        myCylinder(SR, WR, 8);
        glTranslated(0.0, 0.0, WR);
        glRotated(90.0 + 180.0 / NG, -1.0, 0.0, 0.0);
        myCylinder(SR, WR * 2.0 * PI / NG, 8);
      }
      glPopMatrix();
      glPushMatrix();
      {
        glTranslated(-(GD + SR), 0.0, 0.0);
        myCylinder(SR, WR, 8);
        glTranslated(0.0, 0.0, WR);
        glRotated(90.0 + 180.0 / NG, -1.0, 0.0, 0.0);
        myCylinder(SR, WR * 2.0 * sin(PI / NG), 8);
      }
      glPopMatrix();
    }
    glPopMatrix();
  }

  glFlush();
}

static void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);

  /* 透視変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(60.0, (double)w / (double)h, 1.0, 100.0);

  /* モデルビュー変換行列の指定 */
  glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC か q をタイプしたら終了 */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

static void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
