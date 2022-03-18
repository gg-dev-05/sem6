#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500

bool LINE_MODE = true;
float wallWidth = 0.2;
float gateAngle = 0;
double cameraX = 0, cameraY = 0, cameraZ = 5;
double cameraLookAtX = 0, cameraLookAtY = 0, cameraLookAtZ = 0;
double theta = 0;
double speed = 0.1;

bool isLMBPressed = false;
double rotateY = 0;
double xDiff = 0.0f;

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
            cout << "[";
            for (auto k : walls[i][j]) {
                cout << k << ",";
            }
            cout << "] ";
            glVertex3fv(walls[i][j]);
        }
        cout << endl;
        glEnd();
    }
    cout << endl;
}

void drawDoor() {
    drawCuboid(0, -0.35, 2, 1.36, wallWidth, 1.7);
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(-0.5, -0.3, 2);
    glutSolidSphere(0.12, 10, 10);
    glTranslatef(0.5, 0.3, -2);
    glPopMatrix();
}

void display(void) {
    // cout << "Camera: " << cameraX << " " << cameraZ << endl;
    // cout << "LookAt: " << cameraLookAtX << " " << cameraLookAtZ << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (LINE_MODE == 0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);

    glRotatef(rotateY, 0, 1, 0);
    double x = -4.0 / 2.8;
    glColor3f(0.2, 0.7, 0.1);
    drawCuboid(x, 0, 2, x, wallWidth, 2);
    drawCuboid(-x, 0, 2, x, wallWidth, 2);
    drawCuboid(0, 0.75, 2, 3, wallWidth, 0.5);

    // door
    glPushMatrix();
    glColor3f(0.8, 0.7, 0.8);
    glTranslatef(0.68, -1.2, 2.0);
    glRotatef(gateAngle, 0, 1, 0);
    glTranslatef(-0.68, 1.2, -2.0);
    drawDoor();
    glPopMatrix();

    glColor3f(0.2, 0.7, 0.1);
    drawCuboid(0, 0, -2, 4, wallWidth, 2);  // back
    drawCuboid(-2, 0, 0, wallWidth, 4, 2);  // left
    drawCuboid(2, 0, 0, wallWidth, 4, 2);   // right
    glColor3f(0.3, 0.1, 0.5);
    drawCuboid(0, -1.1, 0, 8, 8, wallWidth);  // bottom

    cout << "FURNITURE\n";
    glPushMatrix();
    // glTranslatef(-1, 0, -1);
    glColor3f(0.6, 0.1, 0.6);
    drawCuboid(0, -0.5, 0, 2, 2, 0.1);

    glPushMatrix();
    glTranslatef(-1, 0, -1);
    drawCuboid(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, -1);
    drawCuboid(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 0, 1);
    drawCuboid(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, 1);
    drawCuboid(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPopMatrix();

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
            gateAngle += 10;
            if (gateAngle >= 90) gateAngle = 90;
            break;
        case 'R':
            gateAngle -= 10;
            if (gateAngle <= 0) gateAngle = 0;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseMotion(int currX, int currY) {
    if (isLMBPressed) {
        rotateY = currX - xDiff;
        glutPostRedisplay();
    }
}

void handleMouse(int button, int state, int currX, int currY) {
    if (state == GLUT_DOWN) {
        if (button == 3 || button == 4) {
            int sign = (button == 3 ? 1 : -1);
            cameraX += sign * speed * sin(theta);
            cameraZ -= sign * speed * cos(theta);
            cameraLookAtX += sign * speed * sin(theta);
            cameraLookAtZ -= sign * speed * cos(theta);
            glutPostRedisplay();
        }
        if (button == GLUT_LEFT_BUTTON) {
            isLMBPressed = true;
            xDiff = currX - rotateY;
        }
        if (button == GLUT_RIGHT_BUTTON) {
            LINE_MODE = !LINE_MODE;
            glutPostRedisplay();
        }
    } else {
        isLMBPressed = false;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("BOX");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(handleMouse);
    glutMotionFunc(mouseMotion);
    // glutPassiveMotionFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
