#include<stdio.h>
#include<GL/glut.h>
#include<math.h>


float theta=0;
float rot_mat[3][3]={{0},{0},{0}};
float result[3][3]={{0},{0},{0}};
float triangle[3][3]={{100,150,200},{100,200,100},{1,1,1}};
float h=100,k=100;
float m=0,n=0;

void draw_triangle(float a[3][3])
{
	glBegin(GL_TRIANGLES);
	glVertex2f(a[0][0],a[1][0]);
	glVertex2f(a[0][1],a[1][1]);
	glVertex2f(a[0][2],a[1][2]);
	glEnd();
}
void multiply()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			result[i][j]=0;
			for(int p=0;p<3;p++)
				result[i][j] += rot_mat[i][p]*triangle[p][j];
		}
}
void rotate(float m,float n)
{
	rot_mat[0][0]=cos(theta);
	rot_mat[0][1]=-sin(theta);
	rot_mat[0][2]=m;
	rot_mat[1][0]=sin(theta);
	rot_mat[1][1]=cos(theta);
	rot_mat[1][2]=n;
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;

	multiply();


}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,0,0);
	draw_triangle(triangle);

	glColor3f(0,1,0);
	rotate(0,0);
	draw_triangle(result);

	glColor3f(0,0,1);
	m=-h*(cos(theta)-1) + k*(sin(theta));
	n=-k*(cos(theta)-1) - h*(sin(theta));
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			result[i][j]=0;
	rotate(m,n);
	draw_triangle(result);

	glFlush();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,300,0,300);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc,char **argv)
{
	printf("Enter theta : ");
	scanf("%f",&theta);
	theta=(theta*3.14)/180.0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("rotate triangle");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
