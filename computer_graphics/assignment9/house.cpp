#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#define WIDTH 500
#define HEIGHT 500

bool LINE_MODE = false;
double widthOfWalls = 0.2;
double doorAngle = 0;
double window1Angle = 0;
double window2Angle = 0;
double cameraPositionInX = 0, cameraPositionInY = 0, cameraPositionInZ = 5;
double aspectRatio = 1.0;
double fieldOfView = 60;
double cameraLookAtCoordinateInX = 0, cameraLookAtCoordinateInY = 0, cameraLookAtCoordinateInZ = 0;
double movementSpeed = 0.1;
double cameraUpVector[] = {0, 1, 0};

bool isLeftMouseButtonPressed = false;
double rotationInY = 0;
double rotationInX = 0;
double changeInX = 0.0f;
double changeInY = 0.0f;
bool allowRotationAlongX = false;

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

void wallWithWindow(double windowAngle) {
    // walls
    double temp = -4.0 / 2.8;
    glColor3f(0.9, 0.7, 0.1);
    drawCuboidAt(2, 0, temp, widthOfWalls, temp, 2);
    drawCuboidAt(2, 0, -temp - 0.25, widthOfWalls, temp, 2);
    drawCuboidAt(2, 0.75, 0, widthOfWalls, 3, 0.5);
    drawCuboidAt(2, -0.75, 0, widthOfWalls, 3, 0.5);

    // left pane of window
    glPushMatrix();
    glColor4f(0.60, 0.33, 0.08, 0.9);
    glTranslatef(2.1, -0.5, 0.445);
    glRotatef(-windowAngle, 0, 1, 0);
    glTranslatef(-2.1, 0.5, -0.445);
    drawCuboidAt(2, 0, 0.2, widthOfWalls, 0.6, 1);
    glPopMatrix();

    // right pane of window
    glPushMatrix();
    glColor4f(0.60, 0.33, 0.08, 0.9);
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
    gluPerspective(fieldOfView, aspectRatio, 0.0001, 200);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.58, 0.67, 1);

    // select between line modes
    if (LINE_MODE)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();
    gluLookAt(cameraPositionInX, cameraPositionInY, cameraPositionInZ, cameraLookAtCoordinateInX, cameraLookAtCoordinateInY, cameraLookAtCoordinateInZ, cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);
    glRotatef(rotationInY, 0, 1, 0);
    if (allowRotationAlongX)
        glRotatef(rotationInX, 1, 0, 0);

    float ROOF_TOP = 2;
    float roof[4][3][3] = {
        {{-2, 1, 2}, {2, 1, 2}, {0, ROOF_TOP, 0}},
        {{2, 1, 2}, {2, 1, -2}, {0, ROOF_TOP, 0}},
        {{-2, 1, -2}, {2, 1, -2}, {0, ROOF_TOP, 0}},
        {{-2, 1, 2}, {-2, 1, -2}, {0, ROOF_TOP, 0}},
    };

    drawFrontWallWithDoor();  // front

    // back wall with window
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    wallWithWindow(window2Angle);
    glPopMatrix();

    glColor3f(0.9, 0.7, 0.1);
    leftWallWithTV();
    wallWithWindow(window1Angle);  // right

    // TOP
    glColor3f(0.92, 0.71, 0.36);
    for (int i = 0; i < 4; i++) {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++) {
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
    gluPerspective(fieldOfView, aspectRatio, 0.0001, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPositionInX, cameraPositionInY, cameraPositionInZ, cameraLookAtCoordinateInX, cameraLookAtCoordinateInY, cameraLookAtCoordinateInZ, cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);
}

void keyboardFunction(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
        case 'w':  // move forwards
            cameraPositionInZ -= movementSpeed;
            cameraLookAtCoordinateInZ -= movementSpeed;
            break;
        case 's':  // move backwards
            cameraPositionInZ += movementSpeed;
            cameraLookAtCoordinateInZ -= movementSpeed;
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
        case '[':
            window1Angle += 10;
            if (window1Angle >= 90) window1Angle = 90;
            break;
        case ']':
            window1Angle -= 10;
            if (window1Angle <= 0) window1Angle = 0;
            break;
        case ';':
            window2Angle += 10;
            if (window2Angle >= 90) window2Angle = 90;
            break;
        case '\'':
            window2Angle -= 10;
            if (window2Angle <= 0) window2Angle = 0;
            break;
        case ',':
            allowRotationAlongX = !allowRotationAlongX;
            rotationInX = 0;
            break;
        case ' ':
            window1Angle = 0;
            window2Angle - 0;
            cameraPositionInX = 0;
            cameraPositionInY = 0;
            cameraPositionInZ = 5;
            cameraLookAtCoordinateInX = 0;
            cameraLookAtCoordinateInY = 0;
            cameraLookAtCoordinateInZ = 0;
            rotationInY = 0;
            rotationInX = 0;
            changeInX = 0;
            changeInY = 0;
            glLoadIdentity();
            gluLookAt(cameraPositionInX, cameraPositionInY, cameraPositionInZ, cameraLookAtCoordinateInX, cameraLookAtCoordinateInY, cameraLookAtCoordinateInZ, cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseMotionFunction(int currentPositionX, int currentPositionY) {
    // update rotation and run display again
    if (isLeftMouseButtonPressed) {
        rotationInY = currentPositionX - changeInX;
        rotationInX = currentPositionY - changeInY;
        glutPostRedisplay();
    }
}

void handleMouseFunction(int button, int state, int currentPositionX, int currentPositionY) {
    if (state == GLUT_DOWN) {
        if (button == 3) {  // zoom in
            cameraPositionInZ -= movementSpeed;
            cameraLookAtCoordinateInZ -= movementSpeed;
            glutPostRedisplay();
        }
        if (button == 4) {  // zoom out
            cameraPositionInZ -= -1 * movementSpeed;
            cameraLookAtCoordinateInZ -= -1 * movementSpeed;
            glutPostRedisplay();
        }
        if (button == GLUT_LEFT_BUTTON) {  // left button to rotate world
            isLeftMouseButtonPressed = true;
            changeInX = currentPositionX - rotationInY;
            changeInY = currentPositionY - rotationInX;
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

int main(int argc, char *argv[]) {
    cout << "W / SCROLL UP -> MOVE IN FORWARD DIRECTION\n";
    cout << "S / SCROLL DOWN -> MOVE IN BACKWARD DIRECTION\n";
    cout << "E -> MOVE IN UPWARDS DIRECTION\n";
    cout << "Q -> MOVE IN DOWNWARDS DIRECTION\n";
    cout << "RIGHT CLICK -> SWITCH BETWEEN LINE MODE AND FILL MODE\n";
    cout << "LEFT CLICK + MOVE -> ROTATION ABOUT ORIGIN\n";
    cout << "r / R -> INTERACT WITH DOOR\n";
    cout << "[ / ] -> INTERACT WITH RIGHT WINDOW\n";
    cout << "; / \'-> INTERACT WITH BACK WINDOW\n";
    cout << ", to SWITCH ROTATION ALONG X-AXIS\n";
    cout << "[ ESC ] TO EXIT\n";
    cout << "[ SPACE ] TO RESET\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Assignment 8");

    glEnable(GL_DEPTH_TEST);
    // Enable Transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glutDisplayFunc(displayFunction);
    glutReshapeFunc(reshapeFunction);

    glutMouseFunc(handleMouseFunction);
    glutMotionFunc(mouseMotionFunction);
    glutKeyboardFunc(keyboardFunction);

    glutMainLoop();
    return 0;
}
