#include<stdio.h>
#include<GL/glut.h>

int x0,y0,x1,y1;
int xmin=50,xmax=100,ymin=50,ymax=100;
int code0,code1;
bool accept=false;
bool done=false;

const int bottom=1;
const int left=2;
const int top=4;
const int right=8;

int compute(int x,int y)
{
	int code=0;
	if(x<xmin)	code|=left;
	if(x>xmax)	code|=right;
	if(y<ymin)	code|=bottom;
	if(y>ymax)	code|=top;

	return code;
}

void cohen(int x0,int y0,int x1,int y1)
{
	int x,y;
	float m=float(y1-y0)/float(x1-x0);
	code0=compute(x0,y0);
	code1=compute(x1,y1);
	int out;

	do
	{
		out=code0?code0:code1;
		if(code0 & code1)
		{
			done=true;
		}
		else if(!(code0|code1))
		{
			done=true;
			accept=true;
		}
		else
		{
			if(out & left)
			{
				x=xmin;
				y=y0+(xmin-x0)*m;
			}
			if(out & right)
			{
				x=xmax;
				y=y0+(xmax-x0)*m;
			}
			if(out & bottom)
			{
				y=ymin;
				x=x0+(ymin-y0)/m;
			}
			if(out & top)
			{
				y=ymax;
				x=x0+(ymax-y0)/m;
			}
			if(out==code0)
			{
				x0=x;y0=y;
				code0=compute(x0,y0);
			}
			if(out==code1)
			{
				x1=x;y1=y;
				code1=compute(x1,y1);
			}
		}
	}while(!done);
	if(accept)
	{
		glTranslatef(100,100,0);
		glBegin(GL_LINE_LOOP);
		glColor3f(1,0,0);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);		
		glEnd();	

		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
		glEnd();
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_LOOP);
	glColor3f(1,0,0);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);	
	glEnd();	

	glBegin(GL_LINES);
	glColor3f(0,1,0);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
	
	cohen(x0,y0,x1,y1);

	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,250,0,250);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{
	printf("Enter x0,y0,x1,y1 : ");
	scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("rotate triangle");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
