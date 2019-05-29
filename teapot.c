#include<stdio.h>
#include<GL/glut.h>

void wall(double thickness)
{
	glPushMatrix();
	glTranslated(0.5,0.5*thickness,0.5);
	glScaled(1,thickness,1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void tableleg(double legthick,double leglen)
{
	glPushMatrix();
	glTranslated(0,leglen/2,0);
	glScaled(legthick,leglen,legthick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void table(double topwid,double topthick,double legthick,double leglen)
{
	glPushMatrix();
	glTranslated(0,leglen,0);
	glScaled(topwid,topthick,topwid);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95*topwid/2.0 - legthick/2.0;
	glPushMatrix();
	glTranslated(dist,0,dist);
	tableleg(legthick,leglen);
	glTranslated(0,0,-2*dist);
	tableleg(legthick,leglen);
	glTranslated(-2*dist,0,2*dist);
	tableleg(legthick,leglen);
	glTranslated(0,0,-2*dist);
	tableleg(legthick,leglen);
	glPopMatrix();
}

void display()
{
	GLfloat mat_amb[]={1.111,0.1,0.7,1.0};
	GLfloat mat_diff[]={0.7,0.7,0.7,1.0};
	GLfloat mat_spec[]={0.7,0.7,0.7,1.0};
	GLfloat mat_shine[]={50.0};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diff);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shine);

	GLfloat lightPosition[]={2.0,6.0,3.0,0.0};
	GLfloat lightIntensity[]={0.7,0.7,0.7,1.0};

	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1,1,-1,1,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);

	glPushMatrix();
	glTranslated(0.4,0.4,0.37);
	glutSolidTeapot(0.089);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4,0,0.4);
	table(0.6,0.07,0.06,0.3);
	glPopMatrix();

	glPushMatrix();
	glRotated(90,0,0,1);
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90,1,0,0);
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	wall(0.02);
	glPopMatrix();

	glFlush();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Teapot on table");
	glutInitWindowSize(640,480);
	glutDisplayFunc(display);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0,0,640,480);
	glutMainLoop();
}
