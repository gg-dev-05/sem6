#include <bits/stdc++.h>
#include <GL/glut.h>
#include "imageio.h"

#define PERSPECTIVE 60
#define NEARZ 0.0001
#define FARZ 50
int imageWidthText;
int imageHeightText;
int window;
GLfloat diffuseLight[] = {1.0, 1.0, 1.0, 1};
GLfloat ambientLight[] = {0.0, 0.0, 0.0, 1.0};
GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat positionLight[] = {1.0, 1.0, 0.0, 0.0};
static GLuint textures[6];
int yOrigin = -1, xOrigin = -1;
float angDelta = 0.0f;
float angDeltaZ = 0.0f;
float angleX = 0;
int angleY = 0, angleZ = 0;

float lx = 0.0f, lz = 0.0f, ly = 0.0f;
int lightSwitch = 0;

char maps[][40] = {"textF.png", "textBR.png", "texture.png", "texture.png", "texture.png", "texture.png"};
double deltaMovX = 0, deltaMovY = 0, deltaMovZ = 5;

GLubyte *generateTextImage(char *loadfile) {
    int i, j, c, width, height;
    GLubyte *texImage;
    texImage = loadImageRGBA((char *)loadfile, &width, &height);
    imageWidthText = width;
    imageHeightText = height;
    return texImage;
}

void initialize(void) {
    glClearColor(0, 0, 0, 1.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(6, textures);
    for (int i = 0; i < 6; ++i) {
        GLubyte *texImage = generateTextImage(maps[i]);
        if (!texImage) {
            printf("\nError reading %s \n", maps[i]);
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, textures[i]);  // now we work on handles
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidthText,
                     imageHeightText, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

        delete texImage;
    }
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    float face[6][4][3] = {
        {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}},
        {{-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}},
        {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
        {{-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, -1}},
        {{-1, 1, 1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, -1}},
        {{-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}}};

    // to enable texture on only one face (front one)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glPushMatrix();
    glRotatef(angleX + lx, 1.0, 0.0, 0.0);
    if (lightSwitch == 1) {
        glEnable(GL_LIGHTING);
    } else if (lightSwitch == 2) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, positionLight);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, diffuseLight);
    } else {
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHT0);
    }
    glRotatef(angleY + lz, 0.0, 1.0, 0.0);
    glRotatef(angleZ + ly, 0.0, 0.0, 1.0);

    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3fv(face[i][0]);
        glTexCoord2f(1.0, 0.0);
        glVertex3fv(face[i][1]);
        glTexCoord2f(1.0, 1.0);
        glVertex3fv(face[i][2]);
        glTexCoord2f(0.0, 1.0);
        glVertex3fv(face[i][3]);
        glEnd();
    }

    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            lx = fmod((lx + 5), 360);
            break;
        case 'w':
            lx = fmod((lx - 5), 360);
            break;
        case 'd':
            ly = fmod((ly + 5), 360);
            break;
        case 'a':
            ly = fmod((ly - 5), 360);
            break;
        case 'q':
            lz = fmod((lz + 5), 360);
            break;
        case 'e':
            lz = fmod((lz - 5), 360);
            break;
        case 'l':
            lightSwitch = (lightSwitch + 1) % 3;
            break;
        case ' ':
            lx = 0;
            ly = 0;
            lz = 0;
            break;
        case 27:
            glutDestroyWindow(window);
            exit(0);
    }
    glutPostRedisplay();
}

void handleResize(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PERSPECTIVE, (GLfloat)w / (GLfloat)h, NEARZ, FARZ);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(deltaMovX, deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0);
}

void mouseEvent(int x, int y) {
    if (yOrigin >= 0) {
        angDeltaZ = (x - xOrigin) * 0.3f;
        angDelta = (y - yOrigin) * 0.3f;
        lx = angDelta;
        lz = angDeltaZ;
    }
}

double modValue(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

void mousePress(int button, int state, int x, int y) {
    if (button == 3 || button == 4) {
        double valC = (1 + (button == 3 ? -1 : 1) * (double)1 / (10 * modValue(deltaMovX, deltaMovY, deltaMovZ)));
        deltaMovX *= valC;
        deltaMovY *= valC;
        deltaMovZ *= valC;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(deltaMovX, deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow(argv[0]);
    initialize();
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);
    glutIdleFunc(draw);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseEvent);
    glutMainLoop();
    return 0;
}