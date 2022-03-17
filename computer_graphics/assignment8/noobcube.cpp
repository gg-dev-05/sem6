#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500
float wallWidth = 0.2;
float gateAngle = 0;
double cameraX = 0, cameraY = 0, cameraZ = 5;
double cameraLookAtX = 0, cameraLookAtY = 0, cameraLookAtZ = 0;
double theta = 0;
double speed = 0.1;

void drawCuboid(float centerX, float centerY, float centerZ, float l, float b, float h) {
    float walls[6][4][3] = {
        {{centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}, {centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}, {centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}},
        {{centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}, {centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}},
        {{centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}, {centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}},
        {{centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}, {centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}, {centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}, {centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}},
        {{centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ + b / (float)2.0}, {centerX + l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}, {centerX - l / (float)2.0, centerY + h / (float)2.0, centerZ - b / (float)2.0}},
        {{centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}, {centerX - l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ - b / (float)2.0}, {centerX + l / (float)2.0, centerY - h / (float)2.0, centerZ + b / (float)2.0}}};

    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            // cout << "[";
            // for (auto k : walls[i][j]) {
            //     cout << k << " ";
            // }
            // cout << "],";
            glVertex3fv(walls[i][j]);
        }
        // cout << endl;
        glEnd();
    }
    // cout << "\n";
}

void display(void) {
    // cout << "Camera: " << cameraX << " " << cameraZ << endl;
    // cout << "LookAt: " << cameraLookAtX << " " << cameraLookAtZ << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);

    // drawCuboid(0, 0, 2, 4, wallWidth, 2);     // front
    double x = -4.0 / 2.8;
    glColor3f(0.2, 0.7, 0.1);
    drawCuboid(x, 0, 2, x, wallWidth, 2);
    drawCuboid(-x, 0, 2, x, wallWidth, 2);
    drawCuboid(0, 0.75, 2, 3, wallWidth, 0.5);

    glPushMatrix();
    glColor3f(0.8, 0.7, 0.8);  // door
    glRotatef(gateAngle, 0, 1, 0);
    drawCuboid(0, -0.35, 2, 1.36, wallWidth, 1.7);
    glLoadIdentity();
    glPopMatrix();

    glColor3f(0.2, 0.7, 0.1);
    drawCuboid(0, 0, -2, 4, wallWidth, 2);  // back
    drawCuboid(-2, 0, 0, wallWidth, 4, 2);  // left
    drawCuboid(2, 0, 0, wallWidth, 4, 2);   // right
    glColor3f(0.3, 0.1, 0.5);
    drawCuboid(0, -1.1, 0, 8, 8, wallWidth);  // bottom

    float roof[4][3][3] = {
        {{-2, 1, 2}, {2, 1, 2}, {0, 3, 0}},
        {{2, 1, 2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, -2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, 2}, {-2, 1, -2}, {0, 3, 0}},
    };

    for (int i = 0; i < 4; i++) {
        glBegin(GL_TRIANGLES);
        glColor3f(0.2, 0.5 * i, 0.2);
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
        case '[':
            cameraY += 0.1;
            cameraLookAtY += 0.1;
            break;
        case ']':
            cameraY -= 0.1;
            cameraLookAtY -= 0.1;
            break;
        case 'z':
            cameraX = 0;
            cameraLookAtX = 0;
            break;
        case 'x':
            cameraY = 0;
            cameraLookAtY = 0;
            break;
        case 'c':
            cameraZ = 0;
            cameraLookAtZ = 0;
            break;
        case 'r':
            gateAngle += 1;
            break;
        case 'R':
            gateAngle -= 1;
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
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePress);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
