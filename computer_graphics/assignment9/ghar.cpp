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
bool l = false;

bool isLMBPressed = false;
double rotateY = 0;
double xDiff = 0.0f;

float intensity = 0.0;
float mat_alpha = 0.0;
void lights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat specular_material[] = {0, 0, 0, mat_alpha};
    GLfloat emission_material[] = {0, 0, 0, mat_alpha};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_material);

    GLfloat position0[] = {3, 3, 3, 0.0};
    GLfloat ambient0[] = {1, 1, 1, intensity};
    GLfloat specular0[] = {1, 1, 1, intensity};
    GLfloat diffuse0[] = {1, 1, 1, intensity};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    if (l) {
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, position0);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
    } else {
        glDisable(GL_LIGHT1);
    }
}

void drawCuboid(float centerX, float centerY, float centerZ, float l, float b, float h) {
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glScalef(l, h, b);
    glutSolidCube(1);
    glPopMatrix();
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

void drawTable() {
    glPushMatrix();
    glTranslatef(-0.8, 0, -0.8);

    // base of table
    glColor3f(0.6, 0.1, 0.6);
    drawCuboid(0, -0.5, 0, 2, 2, 0.1);

    // legs
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
}

void frontWallWithGate() {
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
}

void wallWithWindow() {
    // walls
    double x = -4.0 / 2.8;
    glColor3f(0.9, 0.7, 0.1);
    drawCuboid(2, 0, x, wallWidth, x, 2);
    drawCuboid(2, 0, -x - 0.25, wallWidth, x, 2);
    drawCuboid(2, 0.75, 0, wallWidth, 3, 0.5);
    drawCuboid(2, -0.75, 0, wallWidth, 3, 0.5);

    glPushMatrix();
    glTranslatef(2.1, -0.5, 0.445);
    glRotatef(-gateAngle, 0, 1, 0);
    glTranslatef(-2.1, 0.5, -0.445);
    drawCuboid(2, 0, -0.1, wallWidth, 1.2, 1);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.58, 0.67, 1);

    if (LINE_MODE == 0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraLookAtX, cameraLookAtY, cameraLookAtZ, 0, 1, 0);
    glRotatef(rotateY, 0, 1, 0);

    frontWallWithGate();

    wallWithWindow();

    glColor3f(0.3, 0.1, 0.5);
    drawCuboid(0, -1.1, 0, 8, 8, wallWidth);  // bottom

    drawTable();

    float roof[4][3][3] = {
        {{-2, 1, 2}, {2, 1, 2}, {0, 3, 0}},
        {{2, 1, 2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, -2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, 2}, {-2, 1, -2}, {0, 3, 0}},
    };

    for (int i = 0; i < 4; i++) {
        glBegin(GL_TRIANGLES);
        glColor3f(0.2, 0.5, 0.2);
        for (int j = 0; j < 3; j++) {
            glVertex3fv(roof[i][j]);
        }
        glEnd();
    }

    lights();
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
        case '[':
            cameraY += 0.1;
            cameraLookAtY += 0.1;
            break;
        case ']':
            cameraY -= 0.1;
            cameraLookAtY -= 0.1;
            break;
        case 'r':
            gateAngle += 10;
            if (gateAngle >= 90) gateAngle = 90;
            break;
        case 'R':
            gateAngle -= 10;
            if (gateAngle <= 0) gateAngle = 0;
            break;
        case 'i':
            intensity += 0.1;
            cout << "i:" << intensity << endl;
            break;
        case 'o':
            mat_alpha += 0.1;
            cout << "a: " << mat_alpha << endl;
            break;
        case 'k':
            l = !l;
            break;
        case 27:
            exit(0);
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
    cout << "W => FORWARD\nS => BACKWARD\n[ => UP\n] => DOWN\nr => OPEN GATE/WINDOW\nR => CLOSE GATE/WINDOW\nMOUSE => ROTATE VIEW\nESC => EXIT\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // init();
    glutMouseFunc(handleMouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
