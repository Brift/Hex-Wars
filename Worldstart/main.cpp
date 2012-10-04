/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>


static int slices = 16;
static int stacks = 16;
static const double DEPTH = sqrt(3)/2;
static GLdouble vertices[2002][2002][2] ;
static int camerax=0;
static int cameray=0;
static int cameraz=0;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void vertexPlace()
{
    for(int z = 0; z < 2002; z++)
    {
        for(int x=0; x < 2002; x++)
        {
            if(z%2 == 0)
            {
                float altz = -z * DEPTH;
                vertices[x][z][0]= x;
                vertices[x][z][1]= altz;

            }
            else
            {
                float altx = x+0.5;
                float altz = -z * DEPTH;
                vertices[x][z][0]= altx;
                vertices[x][z][1]= altz;
            }
        }
    }
}

//this is for triangle creation forgiven a point
static void triangles(int a, int b, int c)
{
    int aup = a+1;
    int adown = a-1;
    int cup = c+1;
    int cdown = c-1;

    if(c%2 == 0)
    {
        //for even row  pointing toward positive z facing up direction triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
        glEnd();

        //for even row pointing toward negative z facing up triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
            glVertex4d(vertices[adown][c][0],b,vertices[adown][c][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
            glVertex4d(vertices[adown][c][0],b,vertices[adown][c][1],1);
        glEnd();


    }
    else
    {
        //for odd row facing up pointing to positive z up triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[aup][cup][0],b,vertices[aup][cup][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[aup][cup][0],b,vertices[aup][cup][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
        glEnd();

        //for odd row pointing to negative z direction facing up triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][c][0],b,vertices[adown][c][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][c][0],b,vertices[adown][c][1],1);
        glEnd();

    }

}

//This is for drawing the first row triangle
static void triangle(int a, int b, int c)
{
    int aup = a+1;
    int adown = a - 1;
    int cup = c+1;
    int cdown = c-1;

    if(c%2 == 0)
    {
        //for even row  pointing toward positive z facing up direction triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
            glVertex4d(vertices[adown][cup][0],b,vertices[adown][cup][1],1);
        glEnd();
    }

    else
    {
         //for odd row facing up pointing to positive z up triangles
        glColor3ub(200,200,200);
        glBegin(GL_POLYGON);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[aup][cup][0],b,vertices[aup][cup][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
        glEnd();

        glColor3ub(255,255,255);
        glBegin(GL_LINE_LOOP);
            glVertex4d(vertices[a][c][0],b,vertices[a][c][1],1);
            glVertex4d(vertices[aup][cup][0],b,vertices[aup][cup][1],1);
            glVertex4d(vertices[a][cup][0],b,vertices[a][cup][1],1);
        glEnd();
    }


}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3ub(100, 100, 100);

    glPushMatrix();
        glTranslated(-20,0,20);
        for(int z = 1; z < 2000; z++)
        {
            for(int y = 1; y < 2; y++)
            {
                for(int x= 1; x < 2000; x++)
                {
                    if(x == 1)
                    {
                        triangle(x,y,z);
                    }
                    else
                    {
                        triangles(x,y,z);
                    }
                }
            }
        }

    glPopMatrix();


    glColor4ub(200,200,0,1);
    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glLoadIdentity() ;
    gluLookAt(camerax,cameray,cameraz,0,0,-20,0.0,1.0,0.0);
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'w':
            if (cameraz > -100)
            {
                cameraz--;
            }
            break;

        case 'a':
            if (camerax > -100)
            {
                camerax--;
            }
            break;

        case 'd':
            if (camerax < 100)
            {
                camerax++;
            }
            break;

        case 's':
            if (cameraz < 100)
            {
                cameraz++;
            }
            break;

        case 'r':
            if (cameray < 100)
            {
                cameray++;
            }
            break;

        case 'f':
            if (cameray > -100)
            {
                cameray--;
            }
            break;

    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    vertexPlace();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
