#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

float posx = 0;
float posy = 0;
#define PI 3.14159
void drawLines(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_pos[] = {0.0, 0.0, 0.0, 0.0};
    //THIS ROTATES THE WHOLE SCENCE
    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(posx, 0.0f, 1.0f, 0.0f);*/

    //THIS ROTATES ONLY THE OBJECTS INSIDE THE GLPUSHMATRIX AND GLPOPMATRIX FUNCTIONS
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glRotatef(posx, 0.0f, 1.0f, 0.0f);

    //TETAEDRON BY HAND
   GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles
    GLfloat radius = 6.0f;
    int gradation = 20;
    float d = 2.0f;
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    for (float alpha = 0.0; alpha < 20*PI; alpha += PI/gradation)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (beta = 0.0; beta < 20*2.01*PI; beta += PI/gradation)
        {
            x = radius*cos(beta) + d;
            y = radius*sin(beta) + d;
            z = beta;
            glVertex3f(x, y, z);
        }
        glEnd();
    }

    //glutSolidTeapot(5.0);
    glPopMatrix();
    glFlush();
}

void init()
{
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);//range of x,y,z axis
    //gluOrtho2D(0.0f, 500.0f, 500.0f, 0.0f);//setup the camera in 2d mode

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'd':posx+=10;
            printf("right %f\n",posx);
            break;
        case 'a':posx-=10;
            printf("left\n");
            break;
        case 'w':posy-=10;
            printf("up\n");
            break;
        case 's':posy+=10;
            printf("down\n");
            break;
     }

 //glMatrixMode(GL_MODELVIEW);
 //glLoadIdentity();
 //glViewport(100.0f, 100.0f, 500.0f, 500.0f);
 //glTranslatef(posx, posy, 0.0);
 if(posx>=360)
     posx = 0;
 //glRotatef(posx, 0.0f, 1.0f, 0.0f);
}

int main(int argc, const char * argv[])
{

    // insert code here...

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowPosition(400, 200);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("OpenGLTest");

    init();

    glutDisplayFunc(drawLines);
    glutIdleFunc(drawLines);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 1;
}
