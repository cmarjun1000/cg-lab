#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int x0,y_0,x1,y_1;
float m;

void draw_pixel(float x,float y)
{
	//glColor3f(1,0,0);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void linedrawing1(float x0,float y_0,float x1,float y_1,float m)
{
	float x,y,dx,dy,p,ppos,pneg;
	if(x0>x1)
	{
		float temp1=x0;
		x0=x1;
		x1=temp1;
		float temp2=y_0;
		y_0=y_1;
		y_1=temp2;
	}
	dx=abs(x1-x0);
	dy=abs(y_1-y_0);
	p=2*dy-dx;
	ppos=2*dy;
	pneg=2*dy-2*dx;
	x=x0;
	y=y_0;
	
	draw_pixel(x,y);
	
	while(x<x1)
	{
		x++;
		if(p<0)
			p+=pneg;
		else
		{
			if(m<0)
				y--;
			else
				y++;
			p+=ppos;
		}
		draw_pixel(x,y);
	}
}

void linedrawing2(float x0,float y_0,float x1,float y_1,float m)
{
	float x,y,dx,dy,p,ppos,pneg;
	if(x0>x1)
	{
		float temp1=x0;
		x0=x1;
		x1=temp1;
		float temp2=y_0;
		y_0=y_1;
		y_1=temp2;
	}
	dx=abs(x1-x0);
	dy=abs(y_1-y_0);
	p=2*dx-dy;
	pneg=2*dx;
	ppos=2*dx-2*dy;
	x=x0;
	y=y_0;
	
	draw_pixel(x,y);

	while(y<y_1)
	{
		y++;
		if(p<0)
			p+=pneg;
		else
		{
			if(m<0)
				x--;
			else
				x++;
			p+=ppos;
		}
		draw_pixel(x,y);
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,0,0);
	float d1 =(x1-x0);
	float d2 =(y_1-y_0);
	m = d2 / (float)d1;
	if(m<1)
		linedrawing1(x0,y_0,x1,y_1,m);	
	else
	{
		linedrawing2(x0,y_0,x1,y_1,m);
	}	
	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,50,0,50);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc,char **argv)
{
	printf("Enter x0,y_0,x1,y_1 : ");
	scanf("%d%d%d%d",&x0,&y_0,&x1,&y_1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("bresenhams line drawing");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(100,100);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
