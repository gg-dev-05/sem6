// 190001016
// Garvit Galgat

#include <bits/stdc++.h>
#include <GL/glut.h>
#include "imageio.h"
using namespace std;

#define WINDOW_WIDHT 500
#define WINDOW_HEIGHT 500
#define PERSPECTIVE 45.0
#define NEARZ 1.0  // nearest point for z-axis
#define FARZ 50.0  // farthest point for z-axis

int window;
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1};
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};

int anglex = 0, angley = 0, anglez = 0;  // rotation angles
// images for texture maps for 6 faces of cube
char maps[][8] = {"bat.png", "bat.png", "bat.png", "bat.png",
                  "bat.png", "bat.png"};
int texImageWidth;
int texImageHeight;
static GLuint texName[6];  // texture names
GLubyte *makeTexImage(char *loadfile) {
    int i, j, c, width, height;
    GLubyte *texImage;

    /*
      Only works for .png or .tif images.  NULL is returned if errors occurred.
      loadImageRGA() is from imageio library downloaded from Internet.
    */
    texImage = loadImageRGBA((char *)loadfile, &width, &height);
    texImageWidth = width;
    texImageHeight = height;
    if (!texImage) printf("Unable to get texImage");
    return texImage;
}

// handle window resize match the aspect ratio
void handleResize(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (double)width / (double)height;
    gluPerspective(PERSPECTIVE, aspectRatio, NEARZ, FARZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);
}

// draw the hut
void draw() {
    // glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPushMatrix();
    glRotatef(anglex, 1.0, 0.0, 0.0);  // rotate the cube along x-axis
    glRotatef(angley, 0.0, 1.0, 0.0);  // rotate along y-axis
    glRotatef(anglez, 0.0, 0.0, 1.0);  // rotate along y-axis

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, light_diffuse);

    int faces[][2][4][3] = {
        {{{-1, -1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, -1, -1}}, {0, -1, 0}},   // bottom
        {{{-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}}, {-1, 0, 0}},   // left
        {{{1, -1, -1}, {1, -1, 1}, {1, 1, 1}, {1, 1, -1}}, {1, 0, 0}},        // right
        {{{-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}}, {0, 1, 0}},        // top
        {{{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}}, {0, 0, 1}},        // back
        {{{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}}, {0, 0, -1}}};  // front

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -2.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[0]);
        glBegin(GL_QUADS);
        glNormal3i(*faces[i][1][0], *faces[i][1][1], *faces[i][1][2]);
        glTexCoord2f(0.0, 0.0);
        glVertex3iv(faces[i][0][0]);
        glTexCoord2f(0.0, 1.0);
        glVertex3iv(faces[i][0][1]);
        glTexCoord2f(1.0, 1.0);
        glVertex3iv(faces[i][0][2]);
        glTexCoord2f(1.0, 0.0);
        glVertex3iv(faces[i][0][3]);
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            anglex = (anglex + 5) % 360;
            break;
        case 'w':
            anglex = (anglex - 5) % 360;
            break;
        case 'd':
            angley = (angley + 5) % 360;
            break;
        case 'a':
            angley = (angley - 5) % 360;
            break;
        case 'q':
            anglez = (anglez + 5) % 360;
            break;
        case 'e':
            anglez = (anglez - 5) % 360;
            break;
        case ' ':
            anglex = 0;
            angley = 0;
            anglez = 0;
            break;
        case 27: /* escape */
            glutDestroyWindow(window);
            exit(0);
    }
    glutPostRedisplay();
}

void initTextures() {
    // glClearColor(0.2, 0.2, 0.8, 0.0);
    glShadeModel(GL_FLAT);
    glTranslatef(0.0, 0.0, -5.0);

    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // texName is global
    glGenTextures(6, texName);
    for (int i = 0; i < 6; ++i) {
        GLubyte *texImage = makeTexImage(maps[i]);
        if (!texImage) {
            printf("\nError reading %s \n", maps[i]);
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, texName[i]);  // now we work on texName
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth,
                     texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

        delete texImage;  // free memory holding texture image
    }
}

int main(int argc, char **argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // GLUT_DOUBLE for better frames while interacting  with mouse
    // GLUT_RGB for RGBA system
    // GLUT_DEPTH for depth buffer
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDHT, WINDOW_HEIGHT);
    // Create the window
    window = glutCreateWindow("HUT");
    initTextures();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Set handler functions
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard);

    glutMainLoop();  // start the main glut loop
    return 0;
}