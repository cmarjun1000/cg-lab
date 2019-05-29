#include<stdio.h>
#include<GL/glut.h>

int x0,y0,x1,y1,x2,y2,x3,y3;
int flag=0;

void edge_detect(int x0,int y0,int x1,int y1,int *le,int *re)
{
	if(y0>y1)
	{
		int temp1=x0;
		x0=x1;
		x1=temp1;
		int temp2=y0;
		y0=y1;
		y1=temp2;
	}
	float m=(float)(x1-x0)/(y1-y0);
	int x=x0;
	
	for(int i=y0;i<y1;i++)
	{
		if(x<le[i])
			le[i]=x;
		if(x>re[i])
			re[i]=x;
		x=x+m;
	}	
}

void scanfill(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3)
{
	int le[500],re[500];
	for(int i=0;i<500;i++)
	{
		le[i]=500;re[i]=0;
	}
	edge_detect(x0,y0,x1,y1,le,re);
	edge_detect(x1,y1,x2,y2,le,re);
	edge_detect(x2,y2,x3,y3,le,re);
	edge_detect(x3,y3,x0,y0,le,re);
	
	for(int y=0;y<500;y++)
	{
		if(le[y]<re[y])
		{
			for(int i=le[y];i<re[y];i++)
			{
				glColor3f(0,0,1);
				glBegin(GL_POINTS);
				glVertex2f(i,y);
				glEnd();
			}
		}
	}
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1,0,0);
	//glPointSize(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
	
	if(flag==1)
		scanfill(x0,y0,x1,y1,x2,y2,x3,y3);

	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void menu(int id)
{
	if(id==1)
		flag=1;
	else if(id==2)
		flag=0;
	else
		exit(0);
	glutPostRedisplay();
}

void main(int argc, char **argv)
{
	printf("Enter x0,y0,x1,y1,x2,y2,x3,y3 : ");
    	scanf("%d%d%d%d%d%d%d%d", &x0, &y0, &x1, &y1, &x2, &y2, &x3, &y3);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Scanline");
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	init();
	glutDisplayFunc(display);

	glutCreateMenu(menu);
	glutAddMenuEntry("fill",1);
	glutAddMenuEntry("clear",2);
	glutAddMenuEntry("quit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
