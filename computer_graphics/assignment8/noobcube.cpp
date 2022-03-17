#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500
double cameraX = 0, cameraY = 0, cameraZ = 5;
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glLoadIdentity();
    float face[6][4][3] = {
        {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}},
        {{-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}},
        {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
        {{-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, -1}},
        {{-1, 1, 1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, -1}},
        {{-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}}};

    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glVertex3fv(face[i][0]);
        glVertex3fv(face[i][1]);
        glVertex3fv(face[i][2]);
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
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
}

double modValue(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

void mousePress(int button, int state, int x, int y) {
    if (button == 3 || button == 4) {
        double valC = 1 + (button == 3 ? -1 : 1) * (double)1 / (10 * modValue(cameraX, cameraY, cameraZ));
        cameraX *= valC;
        cameraY *= valC;
        cameraZ *= valC;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    // switch (key) {
    //     case 'a':
    //         break;

    //     default:
    //         break;
    // }
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
