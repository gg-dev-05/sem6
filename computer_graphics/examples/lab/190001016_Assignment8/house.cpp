// 190001016
// Garvit Galgat
#include <bits/stdc++.h>
#include <GL/glut.h>
#include "imageio.h"
using namespace std;

GLuint textures[6];
int imageWidthText;
int imageHeightText;

#define WIDTH 500
#define HEIGHT 500

bool LINE_MODE = true;
double widthOfWalls = 0.2;
double doorAngle = 0;
double windowAngle = 0;
double cameraPositionInX = 0, cameraPositionInY = 0, cameraPositionInZ = 5;
double cameraLookAtCoordinateInX = 0, cameraLookAtCoordinateInY = 0, cameraLookAtCoordinateInZ = 0;
double theta = 0;
double movementSpeed = 0.1;
double cameraUpVector[] = {0, 1, 0};

bool isLeftMouseButtonPressed = false;
double rotationInY = 0;
double changeInX = 0.0f;

void DisplayStroke(GLfloat x, GLfloat y, GLfloat z, GLfloat fontSize, GLfloat pointSize, GLfloat rotate, string text) {
    string buffer = text;
    glPushMatrix();
    glTranslatef(x, y, z);
    glPointSize(pointSize);
    glLineWidth(pointSize);
    glRotatef(rotate, 0.0, 1.0, 0.0);
    glScalef(fontSize, fontSize, fontSize);
    for (auto ch : buffer)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ch);
    glPopMatrix();
}

void drawCuboidAt(float centerOfCuboidX, float centerOfCuboidY, float centerOfCuboidZ, float lengthOfCubiod, float breadthOfCuboid, float heightOfCuboid, bool debug = false) {
    float walls[6][4][3] = {
        {{centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}},
        {{centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}},
        {{centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}},
        {{centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}},
        {{centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY + heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}},
        {{centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}, {centerOfCuboidX - lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ - breadthOfCuboid / (float)2.0}, {centerOfCuboidX + lengthOfCubiod / (float)2.0, centerOfCuboidY - heightOfCuboid / (float)2.0, centerOfCuboidZ + breadthOfCuboid / (float)2.0}}};

    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            if (debug) {
                cout << "[";
                for (auto k : walls[i][j]) {
                    cout << k << " ";
                }
                cout << "],";
            }
            glVertex3fv(walls[i][j]);
        }
        if (debug) {
            cout << endl;
        }
        glEnd();
    }
}

void drawDoorWithDoorKnob() {
    glColor3f(0.6, 0.3, 0.09);
    drawCuboidAt(0, -0.35, 2, 1.36, widthOfWalls, 1.7);
    glColor3f(1, 1, 1);

    glPushMatrix();
    glTranslatef(-0.5, -0.3, 2.1);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.3, 1.9);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();
}

void drawTableAt(double x, double y, double z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // base of table
    glColor3f(0, 0.7, 0.8);
    drawCuboidAt(0, -0.5, 0, 2, 2, 0.1);

    double corner = 0.9;

    // legs of table
    glPushMatrix();
    glTranslatef(-corner, 0, -corner);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(corner, 0, -corner);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-corner, 0, corner);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(corner, 0, corner);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPopMatrix();
}

void drawChairAt(double x, double y, double z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(1, 0, 0);
    // base of chair
    drawCuboidAt(0, -0.5, 0, 0.6, 0.8, 0.1);

    // back of chair
    glPushMatrix();
    glTranslatef(0, -0.1, -0.4);
    glRotatef(90, 1, 0, 0);
    drawCuboidAt(0, 0, 0, 0.6, 0.8, 0.1);
    glPopMatrix();

    // legs of chair
    glPushMatrix();
    glTranslatef(-0.26, 0, -0.32);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.26, 0, 0.32);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.26, 0, 0.32);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.26, 0, -0.32);
    drawCuboidAt(0, -0.75, 0, 0.1, 0.1, 0.5);
    glPopMatrix();

    glPopMatrix();
}

void drawFrontWallWithDoor() {
    glColor3f(0.72, 0.76, 0.87);
    drawCuboidAt(1.428, 0, 2, 1.428, widthOfWalls, 2);
    drawCuboidAt(-1.428, 0, 2, 1.428, widthOfWalls, 2);
    drawCuboidAt(0, 0.75, 2, 3, widthOfWalls, 0.5);

    // door
    glPushMatrix();
    glColor3f(0.8, 0.7, 0.8);
    glTranslatef(0.68, -1.2, 2.0);
    glRotatef(doorAngle, 0, 1, 0);
    glTranslatef(-0.68, 1.2, -2.0);
    drawDoorWithDoorKnob();
    glPopMatrix();
}

void wallWithWindow() {
    // walls
    double temp = -4.0 / 2.8;
    glColor3f(0.9, 0.7, 0.1);
    drawCuboidAt(2, 0, temp, widthOfWalls, temp, 2);
    drawCuboidAt(2, 0, -temp - 0.25, widthOfWalls, temp, 2);
    drawCuboidAt(2, 0.75, 0, widthOfWalls, 3, 0.5);
    drawCuboidAt(2, -0.75, 0, widthOfWalls, 3, 0.5);

    // left pane of window
    glColor3f(0.67, 0.85, 0.83);
    glPushMatrix();
    glTranslatef(2.1, -0.5, 0.445);
    glRotatef(-windowAngle, 0, 1, 0);
    glTranslatef(-2.1, 0.5, -0.445);
    drawCuboidAt(2, 0, 0.2, widthOfWalls, 0.6, 1);
    glPopMatrix();

    // right pane of window
    glColor3f(0.67, 0.87, 0.83);
    glPushMatrix();
    glTranslatef(2.1, 0, -0.7);
    glRotatef(windowAngle, 0, 1, 0);
    glTranslatef(-2.1, 0, 0.7);
    drawCuboidAt(2, 0, -0.4, widthOfWalls, 0.6, 1);
    glPopMatrix();
}

void leftWallWithTV() {
    drawCuboidAt(-2, 0, 0, widthOfWalls, 4, 2);  // left
    glColor3f(0, 0, 0);
    drawCuboidAt(-1.8, 0, 0, widthOfWalls, 2, 1);  // tv
    glColor3f(1, 1, 1);
    DisplayStroke(-1.65, 0, 0.7, 0.001, 1, 90, "Garvit Galgat");
}

void displayFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glClearColor(0.1, 0.58, 0.67, 1);

    // select between line modes
    if (LINE_MODE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();
    gluLookAt(cameraPositionInX, cameraPositionInY, cameraPositionInZ, cameraLookAtCoordinateInX, cameraLookAtCoordinateInY, cameraLookAtCoordinateInZ, cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);
    glRotatef(rotationInY, 0, 1, 0);

    float roof[4][3][3] = {
        {{-2, 1, 2}, {2, 1, 2}, {0, 3, 0}},
        {{2, 1, 2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, -2}, {2, 1, -2}, {0, 3, 0}},
        {{-2, 1, 2}, {-2, 1, -2}, {0, 3, 0}},
    };

    drawFrontWallWithDoor();  // front
    glColor3f(0.9, 0.7, 0.1);
    // drawCuboidAt(0, 0, -2, 4, widthOfWalls, 2, true);  // back

    glBegin(GL_QUADS);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -1, -1.9);
    glTexCoord2f(1, 0);
    glVertex3f(2, -1, -1.9);
    glTexCoord2f(1, 1);
    glVertex3f(2, 1, -1.9);
    glTexCoord2f(0, 1);
    glVertex3f(-2, 1, -1.9);
    glEnd();

    leftWallWithTV();
    wallWithWindow();  // right
    glColor3f(0.92, 0.71, 0.36);
    for (int i = 0; i < 4; i++) {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++) {
            if (j == 3) {
            }
            glVertex3fv(roof[i][j]);
        }
        glEnd();
    }

    glColor3f(0.32, 0.87, 0.24);
    drawCuboidAt(0, -1.1, 0, 100, 100, widthOfWalls);  // bottom

    // furniture
    drawTableAt(0, 0, 0);

    drawChairAt(0, -0.2, -0.8);

    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    drawChairAt(0, -0.2, -0.8);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    drawChairAt(0, -0.2, -0.8);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshapeFunction(int widthOfWindow, int heightOfWindow) {
    glViewport(0, 0, (GLsizei)widthOfWindow, (GLsizei)heightOfWindow);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)widthOfWindow / (GLfloat)heightOfWindow, 0.0001, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPositionInX, cameraPositionInY, cameraPositionInZ, cameraLookAtCoordinateInX, cameraLookAtCoordinateInY, cameraLookAtCoordinateInZ, cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);
}

void keyboardFunction(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
        case 'w':  // move forwards
            cameraPositionInX += movementSpeed * sin(theta);
            cameraPositionInZ -= movementSpeed * cos(theta);
            cameraLookAtCoordinateInX += movementSpeed * sin(theta);
            cameraLookAtCoordinateInZ -= movementSpeed * cos(theta);
            break;
        case 's':  // move backwards
            cameraPositionInX -= movementSpeed * sin(theta);
            cameraPositionInZ += movementSpeed * cos(theta);
            cameraLookAtCoordinateInX += movementSpeed * sin(theta);
            cameraLookAtCoordinateInZ -= movementSpeed * cos(theta);
            break;
        case 'e':  // move up
            cameraPositionInY += 0.1;
            cameraLookAtCoordinateInY += 0.1;
            if (cameraPositionInY >= 0.6) cameraPositionInY = 0.6;
            if (cameraLookAtCoordinateInY >= 0.6) cameraLookAtCoordinateInY = 0.6;
            break;
        case 'q':  // move down
            cameraPositionInY -= 0.1;
            cameraLookAtCoordinateInY -= 0.1;
            if (cameraPositionInY <= -0.8) cameraPositionInY = -0.8;
            if (cameraLookAtCoordinateInY <= -0.8) cameraLookAtCoordinateInY = -0.8;
            break;
        case 'r':  // open door
            doorAngle += 10;
            if (doorAngle >= 90) doorAngle = 90;
            break;
        case 'R':  // close door
            doorAngle -= 10;
            if (doorAngle <= 0) doorAngle = 0;
            break;
        case 't':
            windowAngle += 10;
            if (windowAngle >= 90) windowAngle = 90;
            break;
        case 'T':
            windowAngle -= 10;
            if (windowAngle <= 0) windowAngle = 0;
            break;
        case 27:
            exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseMotionFunction(int currentPositionX, int currentPositionY) {
    // update rotation and run display again
    if (isLeftMouseButtonPressed) {
        rotationInY = currentPositionX - changeInX;
        glutPostRedisplay();
    }
}

void handleMouseFunction(int button, int state, int currentPositionX, int currentPositionY) {
    if (state == GLUT_DOWN) {
        if (button == 3) {  // zoom in
            cameraPositionInX += movementSpeed * sin(theta);
            cameraPositionInZ -= movementSpeed * cos(theta);
            cameraLookAtCoordinateInX += movementSpeed * sin(theta);
            cameraLookAtCoordinateInZ -= movementSpeed * cos(theta);
            glutPostRedisplay();
        }
        if (button == 4) {  // zoom out
            cameraPositionInX += -1 * movementSpeed * sin(theta);
            cameraPositionInZ -= -1 * movementSpeed * cos(theta);
            cameraLookAtCoordinateInX += -1 * movementSpeed * sin(theta);
            cameraLookAtCoordinateInZ -= -1 * movementSpeed * cos(theta);
            glutPostRedisplay();
        }
        if (button == GLUT_LEFT_BUTTON) {  // left button to rotate world
            isLeftMouseButtonPressed = true;
            changeInX = currentPositionX - rotationInY;
        }
        if (button == GLUT_RIGHT_BUTTON) {
            LINE_MODE = !LINE_MODE;
            glutPostRedisplay();
        }
    } else {
        // set left mouse button as not pressed
        isLeftMouseButtonPressed = false;
    }
}

void initTextures() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, textures);
    GLubyte *texImage;
    int width, height;
    texImage = loadImageRGBA((char *)"texture.png", &width, &height);
    imageWidthText = width;
    imageHeightText = height;
    if (!texImage) {
        printf("\nError reading texture\n");
    }
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidthText,
                 imageHeightText, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

    delete texImage;
}

int main(int argc, char *argv[]) {
    cout << "W / SCROLL UP -> MOVE IN FORWARD DIRECTION\n";
    cout << "S / SCROLL DOWN -> MOVE IN BACKWARD DIRECTION\n";
    cout << "E -> MOVE IN UPWARDS DIRECTION\n";
    cout << "Q -> MOVE IN DOWNWARDS DIRECTION\n";
    cout << "RIGHT CLICK -> SWITCH BETWEEN LINE MODE AND FILL MODE\n";
    cout << "LEFT CLICK + MOVE -> ROTATION ABOUT ORIGIN\n";
    cout << "r / R -> INTERACT WITH DOOR\n";
    cout << "t / T -> INTERACT WITH WINDOW\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Assignment 8");

    glEnable(GL_DEPTH_TEST);
    initTextures();

    glutDisplayFunc(displayFunction);
    glutReshapeFunc(reshapeFunction);

    glutMouseFunc(handleMouseFunction);
    glutMotionFunc(mouseMotionFunction);
    glutKeyboardFunc(keyboardFunction);

    glutMainLoop();
    return 0;
}
