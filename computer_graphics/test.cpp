#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

// Camera properties
float angle = 0.0;
float cameraDirX = 1.0, cameraDirZ = 1.0, cameraDirY = 1.0;
float cameraPosX = -3.0, cameraPosY = -3.0, cameraPosZ = -3.0;
float deltaAngle = 0.0;
float deltaMove = 0;
int prevX = -1;
int prevY = -1;

const float PI = 3.14159;
float cameraTheta = PI * 1.15;
float cameraPhi = -PI * 0.25;
float cameraRadius = 8;
float gateAngle = 0;
int open = 0;

bool pressed = false;
GLfloat aspect;

// new var
int wave_count = 0, on = 1, off = 1, p = 0;
double points[45][45][3], r = 0.5, s = 0.00681817;
double pi = acos(-1);

GLfloat hold;

// init
void init(void) {
    for (int x = 0; x < 45; x++) {
        for (int y = 0; y < 45; y++) {
            points[x][y][0] = double(((x / 3.0f) - 7.25f) / 10);
            points[x][y][1] = double(((y / 5.0f) - 4.5f) / 10);
            points[x][y][2] = double(sin((((x / 5.0f) * 40.0f) / 360.0f) * pi * 2.0f)) / 10;
        }
    }
}
// flag open
void rectangle(void) {
    int x, y;
    double double_x, double_y, double_xb, double_yb;

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0f, 0.0f, -10.0f);

    glBegin(GL_QUADS);
    // glVertex3f(points[0][0][0] + 3, points[0][0][1], points[0][0][2]);
    // glVertex3f(points[0][0][0] + 3, points[0][0][1], points[0][0][2]);
    // glVertex3f(points[43][1][0] + 3, points[43][1][1], points[43][1][2]);
    // glVertex3f(points[43][1][0] + 3, points[43][1][1], points[43][1][2]);
    for (x = 0; x < 44; x++) {
        for (y = 0; y < 44; y++) {
            double_x = double(x) / 44.0f;
            double_y = double(y) / 44.0f;
            double_xb = double(x + 1) / 44.0f;
            double_yb = double(y + 1) / 44.0f;

            int t = -3;
            glTexCoord2f(double_x, double_y);
            glVertex3f(points[0][y][0] - t, points[x][y][1], points[x][y][2]);

            glTexCoord2f(double_x, double_yb);
            glVertex3f(points[x][y + 1][0] - t, points[x][y + 1][1], points[x][y + 1][2]);

            glTexCoord2f(double_xb, double_yb);
            glVertex3f(points[x + 1][y + 1][0] - t, points[x + 1][y + 1][1], points[x + 1][y + 1][2]);

            glTexCoord2f(double_xb, double_y);
            glVertex3f(points[x + 1][y][0] - t, points[x + 1][y][1], points[x + 1][y][2]);
        }
    }
    glEnd();

    if (wave_count == 2) {
        for (y = 0; y < 45; y++) {
            hold = points[0][y][2];

            for (x = 0; x < 44; x++) {
                points[x][y][2] = points[x + 1][y][2];
            }

            points[44][y][2] = hold;
        }

        wave_count = 0;
    }

    wave_count++;
}

// flag closed

// Function to draw the house
GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat position[] = {3.0f, 3.0f, -1.0f, 1.0f};
void drawHouse() {
    glTranslatef(-1.5, -0.5, -0.5);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    // sun
    glTranslatef(3, 3, -1);
    GLUquadric *quad = gluNewQuadric();
    glColor3f(1.0, 1.0, 0.0);
    gluSphere(quad, 0.25, 100, 20);
    glTranslatef(-3, -3, 1);

    // tree
    glColor3f(0.5, 0.44, 0.33);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(4, -1, 0.4);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quadratic, 0.1, 0.1, 3, 20, 20);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-4, 1, -0.4);

    glColor3f(0.18, 0.35, 0.15);
    glTranslatef(0.0, 0.2, 0);
    glRotatef(-90, 1, 0, 0);
    //   glutSolidCone(0.3, 0.3, 20, 20);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.0, -0.2, 0);
    glRotatef(-90, 1, 0, 0);
    //   glutSolidCone(0.3, 0.3, 20, 20);
    glRotatef(90, 1, 0, 0);
    glTranslatef(1.5, 0.5, 0.5);

    // road

    glColor3f(0.28, 0.28, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(-10.0, -0.905, 1.2);
    glVertex3f(-10.0, -0.905, 1.7);
    glVertex3f(10.0, -0.905, 1.7);
    glVertex3f(10.0, -0.905, 1.2);

    glColor3f(0.72, 0.7, 0.68);
    glVertex3f(-0.1875, -0.905, 0.20);
    glVertex3f(0.1875, -0.905, 0.20);
    glVertex3f(0.1875, -0.905, 1.2);
    glVertex3f(-0.1875, -0.905, 1.2);
    glEnd();

    glColor3f(0.49, 0.99, 0);
    glTranslatef(0.0, -0.91, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);

    // ground
    quad = gluNewQuadric();
    gluDisk(quad, 0.0, 20, 50, 50);
    glRotatef(-90, 1., 0.0, 0.0);
    glTranslatef(0.0, 0.91, 0.0);

    // Walls
    glColor3f(170.0 / 255.0, 170.0 / 255.0, 44.0 / 255.0);

    glBegin(GL_POLYGON);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    glColor3f(145.0 / 255.0, 117.0 / 255.0, 103.0 / 255.0);
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();

    // pool
    glTranslatef(0.0, -0.5, 3);
    glColor3f(1, 0, 0);

    glBegin(GL_POLYGON);
    glVertex3f(1, -1.0, -1.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1, -1.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(1.0, -0.1, 1.0);
    glVertex3f(1.0, -0.1, -1.0);
    glVertex3f(-1.0, -0.1, -1.0);
    glVertex3f(-1.0, -0.1, 1.0);
    glEnd();

    // Door
    glTranslatef(0.0, 0.5, -3);
    glColor3f(170.0 / 255.0, 170.0 / 255.0, 44.0 / 255.0);
    glBegin(GL_QUADS);
    glVertex3f(-1, 1, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(-1, 0, 1);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(1, 1, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(0.2, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(0.2, -1, 1);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-0.2, 0, 1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-0.2, -1, 1);
    glEnd();

    if (gateAngle > 0) {
        glTranslatef(0.2, 0, 1);
        glRotatef(-1 * gateAngle, 0.0, 1.0, 0);
        glTranslatef(-0.2, 0, -1);
    }
    glColor3f(0.80, 0.72, 0.24);  // Colorfor door
    glBegin(GL_QUADS);            // drawing for door
    glVertex3f(-0.2, -1, 1);
    glVertex3f(0.2, -1, 1);
    glVertex3f(0.2, 0, 1);
    glVertex3f(-0.2, 0, 1);
    glEnd();
    if (gateAngle > 0) {
        glTranslatef(0.2, 0, 1);
        glRotatef(gateAngle, 0.0, 1.0, 0);
        glTranslatef(-0.2, 0, -1);
    }

    // Windows
    glColor3f(112.0 / 255.0, 48.0 / 255.0, 22.0 / 255.0);
    glBegin(GL_POLYGON);
    glVertex3f(1.01, -0.2, 0.2);
    glVertex3f(1.01, 0.2, 0.2);
    glVertex3f(1.01, 0.2, -0.2);
    glVertex3f(1.01, -0.2, -0.2);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-1.01, -0.2, 0.2);
    glVertex3f(-1.01, 0.2, 0.2);
    glVertex3f(-1.01, 0.2, -0.2);
    glVertex3f(-1.01, -0.2, -0.2);
    glEnd();

    // Roof
    glColor3f(112.0 / 255.0, 48.0 / 255.0, 22.0 / 255.0);
    glBegin(GL_POLYGON);
    glVertex3f(1.5, 1.0, 1.5);
    glVertex3f(1.5, 1.0, -1.5);
    glVertex3f(-1.5, 1.0, -1.5);
    glVertex3f(-1.5, 1.0, 1.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.5, 1.0, 1.5);
    glVertex3f(1.5, 1.0, -1.5);
    glVertex3f(0, 2, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.5, 1.0, -1.5);
    glVertex3f(-1.5, 1.0, -1.5);
    glVertex3f(0, 2, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0, 2, 0);
    glVertex3f(-1.5, 1.0, -1.5);
    glVertex3f(-1.5, 1.0, 1.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(1.5, 1.0, 1.5);
    glVertex3f(0, 2, 0);
    glVertex3f(-1.5, 1.0, 1.5);
    glEnd();

    glBegin(GL_QUADS);  // for the table drawn
    glVertex3f(0.05, -0.1, -0.05);
    glVertex3f(0.05, -0.1, 0.05);
    glVertex3f(0.05, -1, 0.05);
    glVertex3f(0.05, -1, -0.05);

    glVertex3f(0.05, -0.1, -0.05);
    glVertex3f(-0.05, -0.1, -0.05);
    glVertex3f(-0.05, -1, -0.05);
    glVertex3f(0.05, -1, -0.05);

    glVertex3f(-0.05, -0.1, 0.05);
    glVertex3f(-0.05, -0.1, -0.05);
    glVertex3f(-0.05, -1, -0.05);
    glVertex3f(-0.05, -1, 0.05);

    glVertex3f(-0.05, -0.1, 0.05);
    glVertex3f(0.05, -0.1, 0.05);
    glVertex3f(0.05, -1, 0.05);
    glVertex3f(-0.05, -1, 0.05);

    glVertex3f(0.3, -0.1, 0.3);
    glVertex3f(0.3, -0.1, -0.3);
    glVertex3f(-0.3, -0.1, -0.3);
    glVertex3f(-0.3, -0.1, 0.3);

    glEnd();
}

// Function to compute position of camera
void computeCameraPosition(float deltaMove) {
    cameraPosX += deltaMove * cameraDirX * 0.1;
    cameraPosY += deltaMove * cameraDirY * 0.1;
    cameraPosZ += deltaMove * cameraDirZ * 0.1;
}

// Function to render house on screen
void renderHouse() {
    if (deltaMove) computeCameraPosition(deltaMove);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -1.0 * cameraRadius);
    glRotatef((cameraTheta - PI) * (180.0 / PI), 1, 0, 0);
    glRotatef(-1.0 * cameraPhi * (180.0 / PI), 0, 1, 0);

    glPushMatrix();
    glTranslatef(0.25, 1, 0);
    rectangle();
    glTranslatef(-0.25, -1, 0);

    drawHouse();

    glPopMatrix();
    glutSwapBuffers();
}

// Update camera position when mouse is pressed
void mouseMove(int x, int y) {
    if (prevX == -1) prevX = x;
    if (prevY == -1) prevY = y;
    if (pressed) {
        float temp;
        temp = 800 / (2 * PI * cameraRadius);
        cameraTheta += (y - prevY) / temp * 0.1;

        temp = 800 / (2 * PI * cameraRadius);
        if (cameraTheta >= (3 * PI / 2) || cameraTheta <= (PI / 2))
            cameraPhi += (x - prevX) / temp * 0.1;
        else
            cameraPhi -= (x - prevX) / temp * 0.1;
    }
    if (cameraTheta > 2 * PI) cameraTheta -= 2 * PI;
    if (cameraTheta < 0) cameraTheta += 2 * PI;
    if (cameraPhi > 2 * PI) cameraPhi -= 2 * PI;
    if (cameraPhi < 0) cameraPhi += 2 * PI;
    prevX = x;
    prevY = y;
}

// Start motion if the left button is pressed
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            pressed = true;
            prevX = -1;
            prevY = -1;
        } else {
            pressed = true;
        }
    }
}

// Change size of window
void changeWindowSize(int screenWidth, int screenHeight) {
    if (screenHeight == 0) screenHeight = 1;
    float ratio = (screenWidth * 1.0) / screenHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, screenWidth, screenHeight);
    gluPerspective(45.0, ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
            // forr zoomin and zoomout
        case 'a':
            cameraRadius += 0.1;
            break;
        case 'A':
            cameraRadius -= 0.1;
            break;
        case 'r':
            gateAngle += 10;
            if (gateAngle >= 90) gateAngle = 90;
            break;
        case 'R':
            gateAngle -= 10;
            if (gateAngle <= 0) gateAngle = 0;
            break;
        case '+':
            ambientLight[0] += 0.1;
            ambientLight[0] = min(ambientLight[0], 1.0f);
            diffuseLight[0] += 0.1;
            diffuseLight[0] = min(diffuseLight[0], 1.0f);
            specularLight[0] += 0.1;
            specularLight[0] = min(specularLight[0], 1.0f);
            break;
        case '-':
            ambientLight[0] -= 0.1;
            ambientLight[0] = max(ambientLight[0], 0.0f);
            diffuseLight[0] -= 0.1;
            diffuseLight[0] = max(diffuseLight[0], 0.0f);
            specularLight[0] -= 0.1;
            specularLight[0] = max(specularLight[0], 0.0f);
            break;

        default:
            break;
    }
}

void timer(int unused) {
    if (on == 1 && off == 1) {
        glutPostRedisplay();
        glutTimerFunc(30, timer, 0);
    }
}

int main(int C, char *V[]) {
    glutInit(&C, V);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(800, 800);
    glutCreateWindow("House with banner");

    init();

    glutDisplayFunc(renderHouse);
    glutReshapeFunc(changeWindowSize);
    glutIdleFunc(renderHouse);

    glClearColor(1.0, 1.0, 1.0, 0);
    // timer func
    glutTimerFunc(30, timer, 0);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(processKeys);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}