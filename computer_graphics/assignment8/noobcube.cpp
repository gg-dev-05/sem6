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

    float walls[6][4][3] = {
        {{-2, -1, 2}, {2, -1, 2}, {2, 1, 2}, {-2, 1, 2}},
        {{-2, 1, -2}, {2, 1, -2}, {2, -1, -2}, {-2, -1, -2}},
        {{2, -1, 2}, {2, -1, -2}, {2, 1, -2}, {2, 1, 2}},
        {{-2, -1, 2}, {-2, 1, 2}, {-2, 1, -2}, {-2, -1, -2}},
        {{-2, 1, 2}, {2, 1, 2}, {2, 1, -2}, {-2, 1, -2}},
        {{-2, -1, 2}, {-2, -1, -2}, {2, -1, -2}, {2, -1, 2}}};

    float roof[4][3][3] = {
        {{-2, 1, 2}, {2, 1, 2}, {0, 3, 0}},
        {{2, 1, 2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, -2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, 2}, {-2, 1, -2}, {0, 3, 0}},
    };
    // glBegin(GL_LINES);
    // glVertex3f(-1000, -1, 1);
    // glVertex3f(1000, -1, 1);
    // glVertex3f(-1000, -1, -1);
    // glVertex3f(1000, -1, -1);
    // glEnd();
    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            glVertex3fv(walls[i][j]);
        }
        glEnd();
    }

    for (int i = 0; i < 4; i++) {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++) {
            glVertex3fv(roof[i][j]);
        }
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
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            speed += 0.01;
            cout << "MOVEMENT SPEED INCREASED\n";
        }
        if (button == GLUT_RIGHT_BUTTON) {
            speed -= 0.01;
            cout << "MOVEMENT SPEED DECREASED\n";
        }
        if (speed <= 0) speed = 0.01;
        if (speed >= 1) speed = 0.99;
        if (button == 3 || button == 4) {
            int sign = (button == 3 ? 1 : -1);
            cameraX += sign * speed * sin(theta);
            cameraZ -= sign * speed * cos(theta);
            cameraLookAtX += sign * speed * sin(theta);
            cameraLookAtZ -= sign * speed * cos(theta);
            glutPostRedisplay();
        }
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
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePress);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
