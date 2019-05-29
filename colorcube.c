#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

float theta[3]={0,0,0};
int axis=0;
float v[8][3]={{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1}};

void spin()
{
	theta[axis] += 0.1;
	if(theta[axis] > 360)
		theta[axis]=0;
	glutPostRedisplay();
}

void polygon(int a,int b,int c,int d)
{
	glBegin(GL_POLYGON);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();
}

void cube()
{
	glColor3f(1,0,0);
	polygon(0,1,2,3);

	glColor3f(1,0,1);
	polygon(0,1,5,4);

	glColor3f(1,1,0);
	polygon(4,5,6,7);

	glColor3f(0,1,1);
	polygon(2,3,7,6);

	glColor3f(0,0,1);
	polygon(1,2,6,5);

	glColor3f(0,1,0);
	polygon(0,4,7,3);
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
	cube();
	glFlush();
	glutSwapBuffers();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		axis=0;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		axis=1;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		axis=2;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("color cube");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	init();
	glutIdleFunc(spin);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
