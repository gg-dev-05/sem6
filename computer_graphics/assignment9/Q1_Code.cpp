// KULDEEP SINGH
// 190001030

#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

float intensity = 0;
GLfloat lightposition[] = {2.0, 2.0, 2.0, 1.0};
typedef GLfloat point[3];
point f[] = {{0.0, 0.25, 0.0}, {0.0, 1.0, 0.0}, {0.025, 0.25, -0.025}, {-0.025, 0.25, -0.025}, {-0.025, 0.25, 0.025}, {0.025, 0.25, 0.025}};
point fb[] = {{0.025, 0.25, -0.025}, {0.025, 0.25, 0.025}, {0.2, 0.25, 0.05}, {0.2, 0.25, -0.05}, {-0.025, 0.25, -0.025}, {-0.025, 0.25, 0.025}, {-0.2, 0.25, 0.05}, {-0.2, 0.25, -0.05}, {0.025, 0.25, -0.025}, {-0.025, 0.25, -0.025}, {-0.05, 0.25, -0.2}, {0.05, 0.25, -0.2}, {-0.025, 0.25, 0.025}, {0.025, 0.25, 0.025}, {0.05, 0.25, 0.2}, {-0.05, 0.25, 0.2}};
point t[] = {{1.1, -0.3, -0.5}, {1.1, 0.3, -0.5}, {1.1, 0.3, 0.5}, {1.1, -0.3, 0.5}};
point ts[] = {{1.1, 0.05, -0.05}, {1.1, 0.0, -0.05}, {1.1, 0.0, 0.05}, {1.1, 0.05, 0.05}, {1.49, 0.0, -0.05}, {1.49, -0.05, -0.05}, {1.49, -0.05, 0.05}, {1.49, 0.0, 0.05}};
;

float i[] = {1, 0, 0};
float i_neg[] = {-1, 0, 0};
float j[] = {0, 1, 0};
float j_neg[] = {0, -1, 0};
float k[] = {0, 0, 1};
float k_neg[] = {0, 0, -1};

/*
To run the program:

1. To create imageio.o file: g++ -c imageio.cpp -ltiff -lpng
2. TO RUN: g++ Q1_Code.cpp -o Q1 -lglut -lGLU -lGL imageio.o -ltiff -lpng

Using keyboard:

r/R 		Reset the house to initial position
a/s 		Zoom-in/out
f/F         fan on-off  ---> n/m will increase/decrease speed
l/L			lights on-off
g/G			open/close gate
w/W			open/close windows

Using Mouse:
drag + Rotate the house + change the direction of rotation
Scrollwheel -> Zoom-in/out

*/

double rotate_x = 0, rotate_y = 0, zoom = 1, mwo = 1;
float fanspeed = 2.0, angle = 0.0;
int fanflag = 0, lightflag = 0;
int sofa_s = 0, sofa_d = 0;
double doorAngle = 0;

int width, height;

void Tree(float x, float y, float z) {
    glPushMatrix();
    GLUquadricObj *qobj = gluNewQuadric();
    glTranslated(x, y, z);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glColor3f(0, 0.8, 0);
    // leaves
    gluCylinder(qobj, 0.1, 0.5, 1, 16, 16);
    gluCylinder(qobj, 0, 0.8, 2.5, 16, 16);
    glColor3f(0.5, 0.3, 0);
    gluCylinder(qobj, 0.05, 0.05, 4, 16, 16);
    gluDeleteQuadric(qobj);
    glPopMatrix();
}

void spin() {
    angle = angle + fanspeed;
    if (angle >= 360) {
        angle = 0;
    }
    glutPostRedisplay();
}

void grass() {
    glColor3f(0.13, 0.55, 0.13);
    glBegin(GL_QUADS);
    glVertex3f(-2.2, -1.02, -2.2);
    glVertex3f(-2.2, -1.02, 2.2);
    glVertex3f(2.2, -1.02, 2.2);
    glVertex3f(2.2, -1.02, -2.2);
    glEnd();
}

void windows() {
    if (mwo == 1) {
        glColor3f(0.5, 0.55, 0.5);
        glBegin(GL_POLYGON);
        glVertex3f(-1.1f, -0.5f, 1.51f);
        glVertex3f(-1.1f, 0.0f, 1.51f);
        glVertex3f(-0.6f, 0.0f, 1.51f);
        glVertex3f(-0.6f, -0.5f, 1.51f);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f(1.1f, -0.5f, 1.51f);
        glVertex3f(1.1f, 0.0f, 1.51f);
        glVertex3f(0.6f, 0.0f, 1.51f);
        glVertex3f(0.6f, -0.5f, 1.51f);
        glEnd();
    } else {
        glColor3f(0.5, 0.55, 0.5);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-1.1f, -0.5f, 1.51f);
        glVertex3f(-1.1f, 0.0f, 1.51f);
        glVertex3f(-0.6f, 0.0f, 1.51f);
        glVertex3f(-0.6f, -0.5f, 1.51f);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(1.1f, -0.5f, 1.51f);
        glVertex3f(1.1f, 0.0f, 1.51f);
        glVertex3f(0.6f, 0.0f, 1.51f);
        glVertex3f(0.6f, -0.5f, 1.51f);
        glEnd();
    }
}

void tv(point a, point b, point c, point d) {
    glColor3f(0.19, 0.31, 0.31);
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glVertex3fv(d);
    glEnd();
}

void tvs(point a, point b, point c, point d, point a1, point b1, point c1, point d1) {
    glColor3f(0.75, 0.75, 0.75);
    glBegin(GL_LINES);
    glVertex3fv(a);
    glVertex3fv(a1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(b);
    glVertex3fv(b1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(c);
    glVertex3fv(c1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(d);
    glVertex3fv(d1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(a1);
    glVertex3fv(b1);
    glVertex3fv(b);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(a1);
    glVertex3fv(d1);
    glVertex3fv(d);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(b);
    glVertex3fv(b1);
    glVertex3fv(c1);
    glVertex3fv(c);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(c);
    glVertex3fv(c1);
    glVertex3fv(d1);
    glVertex3fv(d);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a1);
    glVertex3fv(b1);
    glVertex3fv(c1);
    glVertex3fv(d1);
    glEnd();
}

void fan(point a, point b, point c, point d, point e, point f) {
    glColor3f(0.72, 0.53, 0.04);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3fv(a);
    glVertex3fv(b);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(c);
    glVertex3fv(d);
    glVertex3fv(e);
    glVertex3fv(f);
    glEnd();
}

void fblade(point a, point b, point c, point d, point a1, point b1, point c1, point d1, point a2, point b2, point c2, point d2, point a3, point b3, point c3, point d3) {
    glColor3f(0.72, 0.53, 0.04);
    if (fanflag == 1)
        glRotatef(angle, 0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glVertex3fv(d);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a1);
    glVertex3fv(b1);
    glVertex3fv(c1);
    glVertex3fv(d1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a2);
    glVertex3fv(b2);
    glVertex3fv(c2);
    glVertex3fv(d2);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3fv(a3);
    glVertex3fv(b3);
    glVertex3fv(c3);
    glVertex3fv(d3);
    glEnd();
}

void table() {
    glColor3f(0.80, 0.72, 0.62);
    glPushMatrix();
    glTranslated(0.375, -1.325 + 0.55, 0.0);
    glScaled(5.0, 0.75, 11.0);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.475, -1.425 + 0.525, -0.50);
    glScaled(0.5, 2.25, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.475, -1.425 + 0.525, 0.50);
    glScaled(0.5, 2.25, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.275, -1.425 + 0.525, 0.50);
    glScaled(0.5, 2.25, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.275, -1.425 + 0.525, -0.50);
    glScaled(0.5, 2.25, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}

void sofa1() {
    glColor3f(0.96, 0.64, 0.38);
    glPushMatrix();
    glTranslated(-0.4 + sofa_s, -1.425 + 0.55, 0 + sofa_d);  // bottom
    glScaled(4, 2.5, 12);
    glutSolidCube(0.1);
    glPopMatrix();

    glColor3f(0.93, 0.84, 0.72);
    glPushMatrix();
    glTranslated(-0.4 + sofa_s, -1.3125 + 0.55, -0.501 + sofa_d);  // back
    glScaled(4.01, 1.5, 2);
    glutSolidCube(0.1);
    glPopMatrix();

    glColor3f(0.93, 0.84, 0.72);
    glPushMatrix();
    glTranslated(-0.4 + sofa_s, -1.3125 + 0.55, 0.501 + sofa_d);  // front
    glScaled(4.01, 1.5, 2);
    glutSolidCube(0.1);
    glPopMatrix();

    glColor3f(0.87, 0.72, 0.53);
    glPushMatrix();
    glTranslated(-0.550 + sofa_s, -1.275 + 0.55, 0 + sofa_d);  // rest
    glScaled(1.0, 4.0, 10);
    glutSolidCube(0.1);
    glPopMatrix();
}

void banner() {
    glPushMatrix();
    glRotatef(45, 0, 0, 1);
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(1.6, -0.4, -0.5);
    glVertex3f(1.6, 0.4, -0.5);
    glVertex3f(1.6, 0.4, 0.5);
    glVertex3f(1.6, -0.4, 0.5);
    glEnd();
    glPopMatrix();
}

// Display house
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(3 * 1.0 / 255 * intensity, 211 * 1.0 / 255 * intensity, 252 * 1.0 / 255 * intensity, 1);
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat lightintensity[] = {1 * intensity, 1 * intensity, 1 * intensity, intensity};
    GLfloat lightposition2[] = {-2.0, -2.0, -2.0, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightintensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightintensity);
    glLightfv(GL_LIGHT1, GL_SPECULAR, mat_specular);

    if (lightflag)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    // house transformations
    glLoadIdentity();

    // Translate the house
    glTranslatef(0.0f, 0.0f, -1.0f);

    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glScalef(zoom, zoom, zoom);

    //******** FRONT ********
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1.5, 0.20, 1.5);
    glVertex3f(-1.5, 1.0, 1.5);
    glVertex3f(1.5, 1.0, 1.5);
    glVertex3f(1.5, 0.20, 1.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1.5, -1.0, 1.5);
    glVertex3f(-1.5, 0.20, 1.5);
    glVertex3f(-0.30, 0.20, 1.5);
    glVertex3f(-0.30, -1.0, 1.5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(1.5, -1.0, 1.5);
    glVertex3f(1.5, 0.20, 1.5);
    glVertex3f(0.30, 0.20, 1.5);
    glVertex3f(0.30, -1.0, 1.5);
    glEnd();

    //******** GATE ********
    glPushMatrix();
    glTranslatef(0.3, 0, 1.5);
    glRotatef(doorAngle, 0, 1, 0);
    glTranslatef(-0.3, 0, -1.5);
    glBegin(GL_QUADS);
    glColor3f(0.65f, 0.41f, 0.16f);
    glVertex3f(0.30, -1.0, 1.501);
    glVertex3f(0.30, 0.20, 1.501);
    glVertex3f(0.003, 0.20, 1.501);
    glVertex3f(0.003, -1.0, 1.501);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0, 1.5);
    glRotatef(-doorAngle, 0, 1, 0);
    glTranslatef(0.3, 0, -1.5);
    glBegin(GL_QUADS);
    glVertex3f(-0.30, -1.0, 1.501);
    glVertex3f(-0.30, 0.20, 1.501);
    glVertex3f(-0.003, 0.20, 1.501);
    glVertex3f(-0.003, -1.0, 1.501);
    glEnd();
    glPopMatrix();

    //******** BACK ********
    glColor3f(0.8f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.5, -1.0, -1.5);
    glVertex3f(-1.5, 1.0, -1.5);
    glVertex3f(1.5, 1.0, -1.5);
    glVertex3f(1.5, -1.0, -1.5);
    glEnd();

    //******** RIGHT ********
    glBegin(GL_QUADS);
    glColor3f(0.8f, 1.0f, 0.9f);
    // glTexCoord2f(0.0, 0.0);
    glVertex3f(1.5, -1.0, -1.5);
    // glTexCoord2f(1.0, 0.0);
    glVertex3f(1.5, 1.0, -1.5);
    // glTexCoord2f(1.0, 1.0);
    glVertex3f(1.5, 1.0, 1.5);
    // glTexCoord2f(0.0, 1.0);
    glVertex3f(1.5, -1.0, 1.5);

    glEnd();

    //******** BANNER ********
    banner();

    //******** LEFT ********
    glBegin(GL_QUADS);
    glColor3f(0.8f, 1.0f, 0.7f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.5, -1.0, -1.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.5, 1.0, -1.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.5, 1.0, 1.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.5, -1.0, 1.5);
    glEnd();

    //******** TOP ********
    glBegin(GL_QUADS);
    // glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.75, 1.0, 1.5);
    // glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.75, 1.0, -1.5);
    // glTexCoord2f(1.0, 1.0);
    glVertex3f(1.75, 1.0, -1.5);
    // glTexCoord2f(0.0, 1.0);
    glVertex3f(1.75, 1.0, 1.5);
    glEnd();

    //******** BOTTOM ********
    glBegin(GL_QUADS);
    double x = 10;
    glColor3f(0.1f, 1.0f, 0.2f);
    // glTexCoord2f(0.0, 0.0);
    glVertex3f(-x, -1.0, x);
    // glTexCoord2f(1.0, 0.0);
    glVertex3f(-x, -1.0, -x);
    // glTexCoord2f(1.0, 1.0);
    glVertex3f(x, -1.0, -x);
    // glTexCoord2f(0.0, 1.0);
    glVertex3f(x, -1.0, x);
    glEnd();

    //******** POOL ********
    glPushMatrix();
    glTranslatef(3.5, 0.01, 0);
    glColor3f(0, 0.5, 0.8);
    glBegin(GL_QUADS);
    x = 1.5;
    // glTexCoord2f(0.0, 0.0);
    glVertex3f(-x, -1, x);
    // glTexCoord2f(1.0, 0.0);
    glVertex3f(-x, -1, -x);
    // glTexCoord2f(1.0, 1.0);
    glVertex3f(x, -1, -x);
    // glTexCoord2f(0.0, 1.0);
    glVertex3f(x, -1, x);
    glEnd();
    glPopMatrix();

    //******** TREE ********
    glPushMatrix();
    Tree(-3.5, 3, 0);
    glPopMatrix();

    //******** ROAD ********
    glPushMatrix();
    glTranslatef(0, 0.01, 5);
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    x = 10;
    double y = 2;
    // glTexCoord2f(0.0, 0.0);
    glVertex3f(-x, -1, y);
    // glTexCoord2f(1.0, 0.0);
    glVertex3f(-x, -1, -y);
    // glTexCoord2f(1.0, 1.0);
    glVertex3f(x, -1, -y);
    // glTexCoord2f(0.0, 1.0);
    glVertex3f(x, -1, y);
    glEnd();
    glPopMatrix();

    //******** SUN ********
    glPushMatrix();
    glColor3f(0.8, 0.7, 0);
    float sca = 2;
    glTranslatef(lightposition[0] * sca, lightposition[1] * sca, -lightposition[2] * sca);
    // glTranslatef();
    glutSolidSphere(0.3, 12, 12);
    glPopMatrix();

    //******** ROOF ********
    // left tri
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.75f, 1.0f, 1.5f);
    glVertex3f(-1.75f, 1.0f, -1.5f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glEnd();

    // right tri
    glColor3f(0.5f, 0.2f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex3f(1.75f, 1.0f, 1.5f);
    glVertex3f(1.75f, 1.0f, -1.5f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glEnd();

    // back tri
    glColor3f(0.65f, 0.41f, 0.16f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.75f, 1.0f, -1.5f);
    glVertex3f(1.75f, 1.0f, -1.5f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glEnd();

    // front tri
    glColor3f(0.5f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.75f, 1.0f, 1.5f);
    glVertex3f(1.75f, 1.0f, 1.5f);
    glVertex3f(0.0f, 2.5f, 0.0f);
    glEnd();

    // TV
    tv(t[0], t[1], t[2], t[3]);
    tvs(ts[0], ts[1], ts[2], ts[3], ts[4], ts[5], ts[6], ts[7]);

    // Sofa
    sofa1();

    // Table
    table();

    // Windows
    windows();

    // Grass
    grass();

    // FAN
    fan(f[0], f[1], f[2], f[3], f[4], f[5]);
    fblade(fb[0], fb[1], fb[2], fb[3], fb[4], fb[5], fb[6], fb[7], fb[8], fb[9], fb[10], fb[11], fb[12], fb[13], fb[14], fb[15]);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

// Direction of rotation
int axis_x = 0, axis_y = 0;

// Takes action on pressing keyboard key
void SpecialKeys(unsigned char key, int x, int y) {
    if (key == 'x' || key == 'X') {
        lightposition[0] += 1 * (key == 'x' ? 1 : -1);
    }
    if (key == 'y' || key == 'Y') {
        lightposition[1] += 1 * (key == 'y' ? 1 : -1);
    }
    if (key == 'z' || key == 'Z') {
        lightposition[2] += 1 * (key == 'z' ? 1 : -1);
    }
    if (key == 'I') {
        intensity += 0.1;
    }
    if (key == 'i') {
        intensity -= 0.1;
    }
    // Reset
    if (key == 'r' or key == 'R') {
        rotate_x = 0;
        rotate_y = 0;
    }

    // Zoom in/out
    if (key == 'a' or key == 'A') {
        zoom *= 1.021897148;
    }
    if (key == 's' or key == 'S') {
        zoom /= 1.021897148;
    }

    // To open and close main gate
    if (key == 'g') {
        doorAngle += 10;
        if (doorAngle >= 120) doorAngle = 120;
    }

    if (key == 'G') {
        doorAngle -= 10;
        if (doorAngle <= 0) doorAngle = 0;
    }

    // To open and close windows
    if (key == 'w' or key == 'W') {
        if (mwo == 0)
            mwo = 1;
        else
            mwo = 0;
    }

    // To rotate fan
    if (key == 'f' or key == 'F') {
        if (fanflag == 0)
            fanflag = 1;
        else
            fanflag = 0;
    }

    // To rotate fan
    if (key == 'n' or key == 'N') {
        fanspeed += 4.0f;
    }
    if (key == 'm' or key == 'M') {
        fanspeed -= 4.0f;
    }

    // To rotate fan
    if (key == 'l' or key == 'L') {
        if (lightflag == 0)
            lightflag = 1;
        else
            lightflag = 0;
    }

    glutPostRedisplay();
}

// when a special keyboard key is pressed, it executes action.
// Rotate the house (Also change the direction of rotation)       --- Using Keyboard
void keyboardRotate(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        rotate_y += 5;
        axis_y = 0;
    }
    if (key == GLUT_KEY_RIGHT) {
        rotate_y -= 5;
        axis_y = 1;
    }
    if (key == GLUT_KEY_DOWN) {
        rotate_x -= 5;
        axis_x = 1;
    }
    if (key == GLUT_KEY_UP) {
        rotate_x += 5;
        axis_x = 0;
    }
    glutPostRedisplay();
}

int last_x = 0, last_y = 0;

// Rotate the house (Also change the direction of rotation) --- Using Mouse
void mouseRotate(int x, int y) {
    if (x > 500 or y > 500 or x < 0 or y < 0)
        return;
    if (abs(x - last_x) > 25 or abs(y - last_y) > 25) {
        last_x = x;
        last_y = y;
        return;
    }
    rotate_x += (last_y - y + 0.0) * 0.5;
    rotate_y += (last_x - x + 0.0) * 0.5;
    if ((last_y - y) > 0)
        axis_x = 0;
    if ((last_y - y) < 0)
        axis_x = 1;
    if ((last_x - x) > 0)
        axis_y = 0;
    if ((last_x - x) < 0)
        axis_y = 1;
    last_x = x;
    last_y = y;

    glutPostRedisplay();
}

// To show Zoom-in/out functionality (Also changed using Scrollwheel)
void mouseZoom(int btn, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (btn == 3) {
            zoom *= 1.021897148;
        }
        if (btn == 4) {
            zoom /= 1.021897148;
        }
    }
    glutPostRedisplay();
}

// To add Spin motion to the house
void idleSpinFunc() {
    if (axis_x == 0)
        rotate_x += 0.2;
    if (axis_x == 1)
        rotate_x -= 0.2;
    if (axis_y == 0)
        rotate_y += 0.2;
    if (axis_y == 1)
        rotate_y -= 0.2;
    glutPostRedisplay();
}

void setupCamera(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

    /* eye is at (0,0,5) */
    /* center is at (0, 0.2, 0) */
    /* Up vector is in positive Y direction */
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialize
void myInit() {
    glClearColor(0.0, 0.1, 0.12, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Camera view
    setupCamera(width, height);
}

// When any option in the menu is selected, this method is called.
void choose_Menu(int value) {
    if (value == 999)
        exit(0);
    glutPostRedisplay();
}

// Create Menu
void create_menu() {
    glutCreateMenu(choose_Menu);
    glutAddMenuEntry("Quit", 999);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(700, 0);  // set window position
    glutInitWindowSize(700, 700);    // set window size
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D - HOUSE | 190001030");  // set window title

    myInit();
    create_menu();
    glutDisplayFunc(display);
    glutReshapeFunc(setupCamera);

    // To set funtionalities like zoom-in/out, intensity and reset.
    glutKeyboardFunc(SpecialKeys);
    glutSpecialFunc(keyboardRotate);

    // To drag the house using mouse
    glutMouseFunc(mouseZoom);
    glutMotionFunc(mouseRotate);

    // To spin the house
    // glutIdleFunc(idleSpinFunc);
    glutIdleFunc(spin);

    glutMainLoop();
    return 0;
}
