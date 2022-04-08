// header Files
#include <GL/freeglut.h>

void draw(int, float);

// global Variables
bool bFullScreen = false;
float fBranch = 20;
float fLength = 0.5f;
float fAngle = 30;

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

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rahul Kedar");

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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
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
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, -1.0f, 0.0f);

    glColor3f(0.64f, 0.16f, 0.16f);


    draw(fBranch, fLength);

    glutSwapBuffers();
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

    case 'w':
        fAngle += 1.0f;
        glutPostRedisplay();
        break;
        
    case 's':
        fAngle -= 1.0f;
        glutPostRedisplay();
        break;
        
    case 'a':
        fBranch += 1.0f;
        glutPostRedisplay();
        break;
        
    case 'd':
        fBranch -= 1.0f;
        glutPostRedisplay();
        break;

    case 'q':
        fLength += 0.01f;
        glutPostRedisplay();
        break;

    case 'e':
        fLength -= 0.01f;
        glutPostRedisplay();
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

void draw(int branch, float len)
{
    if(branch <= 0)
        return;

    if(branch <= 2)   
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(0.64f, 0.16f, 0.16f);

    glBegin(GL_LINES);
    
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( 0.0f,  len,  0.0f);
    
    glEnd();

    glTranslatef(0.0f, len, 0.0f);

    glPushMatrix();
    glRotatef(fAngle, 0.0f, 0.0f, 1.0f);
    draw(--branch, len*0.67);    
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-fAngle, 0.0f, 0.0f, 1.0f);
    draw(--branch, len*0.67);
    glPopMatrix();
}