#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define W 6                        /* ������Σ�ʬ�Σ��� */
#define D 6                        /* ���Ĺ���Σ�ʬ�Σ� */
#define CYCLE 600                  /* ���ʬ�Υե졼��� */
#define GR (D * 0.1)               /* ����ɥ��Ⱦ�¡��� */
#define GD (D * 0.05)              /* ����ɥ���������� */
#define WR (W * 0.6)               /* �����֤�Ⱦ�¡����� */
#define SR (W * 0.01)              /* �����Ⱦ�¡������� */
#define NG 8                       /* ����ɥ�ο������� */

#define PI 3.1415926535897932      /* �߼�Ψ������������ */

/*
 *   ��������
 */
static void myGround(double height)
{
  const static GLfloat ground[][4] = {   /* ��ο������� */
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
 * ���������
 */
static void myCylinder(double radius, double height, int sides)
{
  double step = 6.2831853072 / (double)sides;
  int i = 0;

  /* ���� */
  glNormal3d(0.0, 0.0, -1.0);
  glBegin(GL_TRIANGLE_FAN);
  while (i < sides) {
    double t = step * (double)i++;
    glVertex3d(radius * sin(t), radius * cos(t), 0.0);
  }
  glEnd();

  /* ���� */
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_TRIANGLE_FAN);
  while (--i >= 0) {
    double t = step * (double)i;
    glVertex3d(radius * sin(t), radius * cos(t), height);
  }
  glEnd();

  /* ¦�� */
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
 * ����ɽ��
 */
static void display(void)
{
  const static GLfloat lightpos[] = { -3.0, 4.0, 5.0, 1.0 }; /* �����ΰ��֡����� */
  const static GLfloat orange[] = { 0.9, 0.4, 0.1, 1.0 };    /* ����ɥ�ο����� */
  const static GLfloat white[] = { 0.9, 0.9, 0.9, 1.0 };     /* ����ο��������� */
  static int frame = 0;                                      /* ���ߤΥե졼��� */
  int i;

  /* CYCLE �ե졼�ऴ�Ȥ� 0 -> 1 ���Ѳ� */
  double t = (double)frame / (double)CYCLE;

  /* �ե졼����ʲ���ɽ����Ԥä�����ˤ򥫥���Ȥ��� */
  if (++frame >= CYCLE) frame = 0;

  /* ���̥��ꥢ */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* ��ǥ�ӥ塼�Ѵ�����ν���� */
  glLoadIdentity();

  /* �����ΰ��֤����� */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* �����ΰ�ư��ʪ�Τ�������˰ܤ���*/
  glTranslated(0.0, 0.0, -10.0);

  /* ���̤����� */
  myGround(-(WR + GR + GR));

  for (i = 0; i < NG; ++i) {
    glRotated(360.0 / (double)NG, 0.0, 0.0, 1.0);

    /* ����ɥ������ */
    glPushMatrix();
    {
      glTranslated(WR, 0.0, 0.0);
      glTranslated(0.0, GR * (-0.8), -GD); /* ����ɥ�λ��� */
      glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
      myCylinder(GR, GD * 2.0, 32);
    }
    glPopMatrix();

    /* ��������� */
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
  /* ������ɥ����Τ�ӥ塼�ݡ��Ȥˤ��� */
  glViewport(0, 0, w, h);

  /* Ʃ���Ѵ�����λ��� */
  glMatrixMode(GL_PROJECTION);

  /* Ʃ���Ѵ�����ν���� */
  glLoadIdentity();
  gluPerspective(60.0, (double)w / (double)h, 1.0, 100.0);

  /* ��ǥ�ӥ塼�Ѵ�����λ��� */
  glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC �� q �򥿥��פ����齪λ */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

static void init(void)
{
  /* ������� */
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
