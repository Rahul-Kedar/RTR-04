// header Files
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <math.h>
#include <GL/freeglut.h>

#define PI 3.14159265359

// global Variables
bool bFullScreen = false;


// entry-point function
int main(int argc, char *argv[])
{
    // local function declarations
    void initialize(void);
    void resize(int, int);
    void display(void);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);
    void uninitialize(void);

    // code
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Clock : Rahul Kedar");

    initialize();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);

    glutMainLoop();

    return 0;
}

void initialize(void)
{
    // code
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
    // code
    glViewport(0, 0, width, height);
}

void display(void)
{
    // code
    glClear(GL_COLOR_BUFFER_BIT); 

    float x1 = 0.5f;
    float y1 = 0.5f;
    float r1 = 0.5f;
    
    float x2 = 0.52f;
    float y2 = 0.52f;
    float r2 = 0.52f;
    
    float x3 = 0.54f;
    float y3 = 0.54f;
    float r3 = 0.54f;

    // //glPointSize(2.0f);
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i = 0; i < 360; i++)
    {
        x3 = r3 * cos(i*PI/180);
        y3 = r3 * sin(i*PI/180);

        glVertex3f((float)x3, (float)y3, 0.0f);
    }
    glEnd();

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(int i = 0; i < 360; i++)
    {
        x1 = r1 * cos(i*PI/180);
        y1 = r1 * sin(i*PI/180);
        x2 = r2 * cos(i*PI/180);
        y2 = r2 * sin(i*PI/180);
        x3 = r3 * cos(i*PI/180);
        y3 = r3 * sin(i*PI/180);

        glVertex3f(x1, y1,0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x3, y3, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    glEnd();
    
    glLineWidth(4.0f);

    glBegin(GL_LINES);   
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.38f, 0.0f, 0.0f);
    glEnd();
    
    glLineWidth(3.0f);
    
    glBegin(GL_LINES);   
    glColor3f(1.0f, 0.64f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.46f, 0.0f);
    glEnd();
    
    glLineWidth(2.0f);
    
    x1 = 0.46f * cos(45 * PI / 180);
    y1 = 0.46f * sin(45 * PI / 180);;
    glBegin(GL_LINES);   
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x1, y1, 0.0f);
    glEnd();

    glPointSize(7.0f);

    glBegin(GL_POINTS);   
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.48f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.48f, 0.0f);
    glVertex3f(-0.48f, 0.0f, 0.0f);
    glVertex3f(0.0f, -0.48f, 0.0f);
    glEnd();

    glPointSize(4.0f);

    x1 = 0.48f;
    y1 = 0.0f;
    r1 = 0.48f;

    glBegin(GL_POINTS);   
    x1 = r1 * cos(30*PI/180);
    y1 = r1 * sin(30*PI/180);

    glVertex3f(x1, y1, 0.0f);
    glVertex3f(-x1, y1, 0.0f);
    glVertex3f(x1, -y1, 0.0f);
    glVertex3f(-x1, -y1, 0.0f);
    
    x1 = r1 * cos(60*PI/180);
    y1 = r1 * sin(60*PI/180);
    
    glVertex3f(x1, y1, 0.0f);
    glVertex3f(-x1, y1, 0.0f);
    glVertex3f(x1, -y1, 0.0f);
    glVertex3f(-x1, -y1, 0.0f);
    
    glEnd();
    


    // float x = 0.5f;
    // float y = 0.0f;
    // float r = 0.5f;
    
    // float prev_x;
    // float prev_y;

    // //glPointSize(2.0f);

    // glBegin(GL_LINES);
    // glColor3f(1.0f, 0.0f, 0.0f);
    // for(int i = 0; i <= 360; i++)
    // {
    //     prev_x = x;
    //     prev_y = y;

    //     x = r * cos(i*PI/180);
    //     y = r * sin(i*PI/180);

    //     glVertex3f((float)prev_x, (float)prev_y, 0.0f);
    //     glVertex3f((float)x, (float)y, 0.0f);
    // }
    // glEnd();

    SYSTEMTIME systime;

    GetSystemTime(&systime);

    

    glutSwapBuffers();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    // code
    switch(key)
    {
    case 27:
        glutLeaveMainLoop();
        break;

    case 'F':
    case 'f':
        if(bFullScreen == false)
        {
            glutFullScreen();
            bFullScreen = true;
        }
        else
        {
            glutLeaveFullScreen();
            bFullScreen = false;
        }
        break;

    default:
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    // code
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        glutLeaveMainLoop();
        break;

    default:
        break;
    }
}

void uninitialize(void)
{
    // code
}
