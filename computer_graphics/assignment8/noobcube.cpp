#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500
double cameraX = 0, cameraY = 0, cameraZ = 5;
double cameraLookAtX = 0, cameraLookAtY = 0, cameraLookAtZ = 0;
double theta = 0;
double speed = 0.1;
void display(void) {
    // cout << "Camera: " << cameraX << " " << cameraZ << endl;
    // cout << "LookAt: " << cameraLookAtX << " " << cameraLookAtZ << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);

    float face[6][4][3] = {
        {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}},
        {{-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}},
        {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
        {{-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, -1}},
        {{-1, 1, 1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, -1}},
        {{-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}}};

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex3f(-1000, -1, 1);
    glVertex3f(1000, -1, 1);
    glVertex3f(-1000, -1, -1);
    glVertex3f(1000, -1, -1);
    glEnd();
    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex3fv(face[i][0]);
        glColor3f(0, 1, 0);
        glVertex3fv(face[i][1]);
        glColor3f(0, 0, 1);
        glVertex3fv(face[i][2]);
        glColor3f(1, 0, 1);
        glVertex3fv(face[i][3]);
        glEnd();
    }
    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.0001, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);
}

double modValue(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

void mousePress(int button, int state, int x, int y) {
    if ((button == 3 || button == 4) && state == GLUT_DOWN) {
        speed += (button == 3 ? 0.01 : -0.01);
        if (speed <= 0) speed = 0.01;
        if (speed >= 1) speed = 0.99;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            cameraX += speed * sin(theta);
            cameraZ -= speed * cos(theta);
            cameraLookAtX += speed * sin(theta);
            cameraLookAtZ -= speed * cos(theta);
            break;
        case 's':
            cameraX -= speed * sin(theta);
            cameraZ += speed * cos(theta);
            cameraLookAtX += speed * sin(theta);
            cameraLookAtZ -= speed * cos(theta);
            break;
        case 'a':
            theta -= speed;
            cameraLookAtX = cameraX + sin(theta);
            cameraLookAtZ = cameraZ - cos(theta);
            break;
        case 'd':
            theta += speed;
            cameraLookAtX = cameraX + sin(theta);
            cameraLookAtZ = cameraZ - cos(theta);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("BOX");
    glutDisplayFunc(display);
    // glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePress);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
