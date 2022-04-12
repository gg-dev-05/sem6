// 190001016
// Garvit Galgat

#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

float intensity = 1;
GLfloat lightposition[] = {2.0, 2.0, 2.0, 1.0};
bool window = true;
typedef GLfloat point[3];
int flag_time = 0;
double rotate_x = 0, rotate_y = 0, zoom = 1, mwo = 1;
int lightflag = 0;
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

void table() {
    glPushMatrix();
    glTranslatef(-1, 1, 0);
    glScalef(2, 2, 2);
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
    glPopMatrix();
}

void lights() {
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
    else {
        glClearColor(0.3, 0.3, 0.3, 0.3);
        glDisable(GL_LIGHTING);
    }

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

void banner() {
    GLUquadricObj *qobj = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glColor3f(0.45, 0.25, 0.13);
    glRotatef(270, 1.0, 0, 0);
    glPushMatrix();
    glRotatef(-270, 1.0, 0, 0);

    float num_elements = 1000;
    float dx = 1 / num_elements;
    for (int i = 0; i < num_elements; i++) {
        float phase1 = i * dx;
        int j = i + 1;
        float phase2 = j * dx;

        glColor3f(0.7, 0.7, 0.3);
        glBegin(GL_POLYGON);

        glVertex3f(dx * i, 2, (sinf((2 * 3.14159 / 500 * flag_time) + phase1)) * i / num_elements);
        glVertex3f(dx * i, 3, (sinf((2 * 3.14159 / 500 * flag_time) + phase1)) * i / num_elements);
        glVertex3f(dx * j, 3, (sinf((2 * 3.14159 / 500 * flag_time) + phase2)) * j / num_elements);
        glVertex3f(dx * j, 2, (sinf((2 * 3.14159 / 500 * flag_time) + phase2)) * j / num_elements);

        glEnd();
    }
    glPopMatrix();
    glPopMatrix();
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(3 * 1.0 / 255 * intensity, 211 * 1.0 / 255 * intensity, 252 * 1.0 / 255 * intensity, 1);

    lights();
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
    glVertex3f(1.5, -1.0, -1.5);
    glVertex3f(1.5, 1.0, -1.5);
    glVertex3f(1.5, 1.0, 1.5);
    glVertex3f(1.5, -1.0, 1.5);
    glEnd();

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
    glVertex3f(-x, -1.0, x);
    glVertex3f(-x, -1.0, -x);
    glVertex3f(x, -1.0, -x);
    glVertex3f(x, -1.0, x);
    glEnd();

    //******** POOL ********
    glPushMatrix();
    glTranslatef(3.5, 0.1, 0);
    glColor3f(0, 0.5, 0.8);
    glBegin(GL_QUADS);
    x = 1.5;
    glVertex3f(-x, -1, x);
    glVertex3f(-x, -1, -x);
    glVertex3f(x, -1, -x);
    glVertex3f(x, -1, x);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(3.5, -0.9, 1.5);
    glScalef(2 * x, 0.2, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(3.5, -0.9, -1.5);
    glScalef(2 * x, 0.2, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(2, -0.9, 0);
    glScalef(0.1, 0.2, 2 * x);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(5, -0.9, 0);
    glScalef(0.1, 0.2, 2 * x);
    glutSolidCube(1);
    glPopMatrix();

    //******** TREE ********

    for (int i = -3; i < 3; i++) {
        glPushMatrix();
        Tree(-3.5, 3, i);
        glPopMatrix();
    }

    for (int i = -3; i < 3; i++) {
        glPushMatrix();
        Tree(-5, 3, i);
        glPopMatrix();
    }

    //******** ROAD ********
    glPushMatrix();
    glTranslatef(0, 0.1, 5);
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    x = 10;
    double y = 2;
    glVertex3f(-x, -1, y);
    glVertex3f(-x, -1, -y);
    glVertex3f(x, -1, -y);
    glVertex3f(x, -1, y);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    x = 10;
    y = 0.1;
    glVertex3f(-x, -0.9, y);
    glVertex3f(-x, -0.9, -y);
    glVertex3f(x, -0.9, -y);
    glVertex3f(x, -0.9, y);
    glEnd();
    glPopMatrix();

    //******** SUN ********
    glPushMatrix();
    glColor3f(0.8, 0.7, 0);
    float sca = 2;
    glTranslatef(lightposition[0] * sca, lightposition[1] * sca, lightposition[2] * sca);
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

    // Table
    table();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

// Direction of rotation
int axis_x = 0, axis_y = 0;

// Takes action on pressing keyboard key
void SpecialKeys(unsigned char key, int x, int y) {
    if (key == '.') {
        window = !window;
    }
    if (key == ']') {
        intensity += 0.1;
        if (intensity > 1.5) intensity = 1.5;
    }
    if (key == '[') {
        intensity -= 0.1;
        if (intensity < 0.1) intensity = 0.1;
    }
    if (key == ' ') {
        rotate_x = 0;
        rotate_y = 0;
    }

    // Zoom in/out
    if (key == 'w') {
        zoom *= 1.1;
    }
    if (key == 's') {
        zoom /= 1.1;
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

    if (key == 'l') {
        if (lightflag == 0)
            lightflag = 1;
        else
            lightflag = 0;
    }
    if (key == 'x') {
        lightposition[0] += 0.1;
    }
    if (key == 'X') {
        lightposition[0] -= 0.1;
    }
    if (key == 'y') {
        lightposition[1] += 0.1;
    }
    if (key == 'Y') {
        lightposition[1] -= 0.1;
    }
    if (key == 'z') {
        lightposition[2] += 0.1;
    }
    if (key == 'Z') {
        lightposition[2] -= 0.1;
    }

    glutPostRedisplay();
}

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

void reshape(int w, int h) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.0001, 200);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spin() {
    flag_time += 1;
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    cout << ". TO WINDOW\n";
    cout << "[ / ] TO CHANGE INTENSITY\n";
    cout << "SPACE TO RESET ROTATIONS\n";
    cout << "W / S TO MOVE FORWARDS AND BACKWARDS\n";
    cout << "g / G TO SWITCH DOOR\n";
    cout << "l TO SWITCH LIGHT\n";
    cout << "x / X TO MOVE SUN ALONG X-AXIS\n";
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D - HOUSE");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // To set funtionalities like zoom-in/out, intensity and reset.
    glutKeyboardFunc(SpecialKeys);
    glutSpecialFunc(keyboardRotate);

    glutMouseFunc(mouseZoom);
    glutMotionFunc(mouseRotate);
    glutIdleFunc(spin);

    glutMainLoop();
    return 0;
}
