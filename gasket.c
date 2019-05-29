#include<stdio.h>
#include<GL/glut.h>

float v[4][3]={{0,0,1},{0,1,-1},{-1,-1,-1},{1,-1,-1}};
int n;

void triangle(float *a,float *b,float *c)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void divide_triangle(float *a,float *b,float *c,int m)
{
	float v1[3],v2[3],v3[3];
	if(m>0)
	{
		for(int i=0;i<3;i++)
		{
			v1[i] = (a[i]+b[i])/2;
			v2[i] = (a[i]+c[i])/2;
			v3[i] = (b[i]+c[i])/2;
		}
		divide_triangle(v1,v2,a,m-1);
		divide_triangle(v1,v3,b,m-1);
		divide_triangle(v2,v3,c,m-1);
	}
	else
		triangle(a,b,c);
}

void display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glColor3f(1,0,0);
	divide_triangle(v[0],v[1],v[2],n);

	glColor3f(0,1,0);
	divide_triangle(v[0],v[1],v[3],n);

	glColor3f(0,0,1);
	divide_triangle(v[0],v[2],v[3],n);

	glColor3f(1,0,1);
	divide_triangle(v[1],v[2],v[3],n);
	
	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc,char **argv)
{
	printf("Enter n : ");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("gasket");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
