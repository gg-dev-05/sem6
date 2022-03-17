// 190001016
// Garvit Galgat

#include <bits/stdc++.h>
#include <GL/glut.h>

#define WINDOW_WIDHT 500
#define WINDOW_HEIGHT 500
#define PERSPECTIVE 45.0
#define NEARZ 1.0  // nearest point for z-axis
#define FARZ 50.0  // farthest point for z-axis

using namespace std;

// boolean for left mouse button keypress
bool isLMBPressed = false;

// rotation due to mouse movement
double rotateX = 0;
double rotateY = 0;

// difference between previous rotations and rotation after mouse movement
double XDiff = 0.0f;
double YDiff = 0.0f;

double cameraX = 0, cameraY = 0, cameraZ = 10;
double cameraLookAtX = 0, cameraLookAtY = 0, cameraLookAtZ = 0;
double theta = 0;
double speed = 0.1;
// handle window resize match the aspect ratio
void handleResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (double)width / (double)height;
    gluPerspective(PERSPECTIVE, aspectRatio, NEARZ, FARZ);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);
}

// draw the hut
void draw() {
    // Set background Color
    glClearColor(0.01, 0.5, 0.98, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);  // set the matrix mode
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);

    glRotatef(rotateX, 1.0, 0.0, 0.0);  // rotate about x-axis
    glRotatef(rotateY, 0.0, 1.0, 0.0);  // rotate about y-axis

    // // ground
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-4.0 + 2.5, -1.6, 2.0);
    glVertex3f(10 + 2.5, -1.6, 2.0);
    glVertex3f(10 + 2.5, -1.6, -2.0);
    glVertex3f(-4.0 + 2.5, -1.6, -2.0);

    // left wall
    glColor3f(0.8, 1.0, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(-3.5 + 2.5, -1.6, 1.0);
    glVertex3f(-2.0 + 2.5, -1.6, 1.0);
    glVertex3f(-2.0 + 2.5, -0.1, 1.0);
    glVertex3f(-3.5 + 2.5, -0.1, 1.0);

    // left wall window
    glColor3f(0.4, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-3.0 + 2.5, -1.0, 1.0001);
    glVertex3f(-2.5 + 2.5, -1.0, 1.0001);
    glVertex3f(-2.5 + 2.5, -0.5, 1.0001);
    glVertex3f(-3.0 + 2.5, -0.5, 1.0001);

    // house front
    glColor3f(0.8, 1.0, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-2.0 + 2.5, -1.6, -1.0);
    glVertex3f(-2.0 + 2.5, -0.1, -1.0);
    glVertex3f(-2.0 + 2.5, -0.1, 1.0);
    glVertex3f(-2.0 + 2.5, -1.6, 1.0);

    // door for front
    glColor3f(0.4, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.999 + 2.5, -1.5, -0.5);
    glVertex3f(-1.999 + 2.5, -0.3, -0.5);
    glVertex3f(-1.999 + 2.5, -0.3, 0.0);
    glVertex3f(-1.999 + 2.5, -1.5, 0.0);

    // window for front
    glColor3f(0.4, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.999 + 2.5, -1.0, 0.3);
    glVertex3f(-1.999 + 2.5, -0.5, 0.3);
    glVertex3f(-1.999 + 2.5, -0.5, 0.7);
    glVertex3f(-1.999 + 2.5, -1.0, 0.7);

    // right wall
    glColor3f(0.8, 1.0, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-3.5 + 2.5, -1.6, -1.0);
    glVertex3f(-2.0 + 2.5, -1.6, -1.0);
    glVertex3f(-2.0 + 2.5, -0.1, -1.0);
    glVertex3f(-3.5 + 2.5, -0.1, -1.0);

    // right wall window
    glColor3f(0.4, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-3.0 + 2.5, -1.0, -1.0001);
    glVertex3f(-2.5 + 2.5, -1.0, -1.0001);
    glVertex3f(-2.5 + 2.5, -0.5, -1.0001);
    glVertex3f(-3.0 + 2.5, -0.5, -1.0001);

    // backside
    glColor3f(0.8, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-3.5 + 2.5, -1.6, -1.0);
    glVertex3f(-3.5 + 2.5, -1.6, 1.0);
    glVertex3f(-3.5 + 2.5, -0.1, 1.0);
    glVertex3f(-3.5 + 2.5, -0.1, -1.0);

    // roof
    glColor3f(0.5, 0.2, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-3.5 + 2.5, -0.1, 1.1);
    glVertex3f(-2.0 + 2.5, -0.1, 1.1);
    glVertex3f(-2.75 + 2.5, 0.9, 0.0);

    glColor3f(0.5, 0.2, 0.3);
    glBegin(GL_TRIANGLES);
    glVertex3f(-3.5 + 2.5, -0.1, -1.1);
    glVertex3f(-2.0 + 2.5, -0.1, -1.1);
    glVertex3f(-2.75 + 2.5, 0.9, 0.0);

    glColor3f(0.5, 0.2, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex3f(-3.5 + 2.5, -0.1, 1.1);
    glVertex3f(-3.5 + 2.5, -0.1, -1.1);
    glVertex3f(-2.75 + 2.5, 0.9, 0.0);

    glColor3f(0.5, 0.2, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0 + 2.5, -0.1, -1.1);
    glVertex3f(-2.0 + 2.5, -0.1, 1.1);
    glVertex3f(-2.75 + 2.5, 0.9, 0.0);

    glEnd();

    glutSwapBuffers();
}

// change rotatation according to mouse movement
// based on current position of the cursor
void mouseMotion(int currX, int currY) {
    if (isLMBPressed) {
        rotateX = currY - YDiff;
        rotateY = currX - XDiff;
        glutPostRedisplay();  // re-display
    }
}

// handle mouse keypresses
void handleMouse(int button, int state, int currentX, int currentY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isLMBPressed = true;  // set LMB pressed as true
        XDiff = currentX - rotateY;
        YDiff = currentY - rotateX;
    } else
        isLMBPressed = false;  // mouse button released or not pressed
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // GLUT_DOUBLE for better frames while interacting  with mouse
    // GLUT_RGB for RGBA system
    // GLUT_DEPTH for depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDHT, WINDOW_HEIGHT);

    // Create the window
    glutCreateWindow("HUT");
    glEnable(GL_DEPTH_TEST);

    // Set handler functions
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);

    glutMouseFunc(handleMouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();  // start the main glut loop
    return 0;
}