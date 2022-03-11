#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageio.h"
#include <math.h>

int texImageWidth;
int texImageHeight;
int window;
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1};
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};
static GLuint handles[6];  // texture names
float anglex = 30;
int angley = 40, anglez = 0;  // rotation angles
int yOrigin = -1, xOrigin = -1;
float deltaAngle = 0.0f;
float deltaAnglez = 0.0f;
float lx = 0.0f, lz = 0.0f, ly = 0.0f;
int swapVal = 0, lightSwitch = 0;
// images for texture maps for 6 faces of cube
char maps[][12] = {"text.png", "text.png", "texture.png", "text.png",
                   "text.png", "texture.png"};
double deltaMovX = 0, deltaMovY = 0, deltaMovZ = 5;
// load texture image
GLubyte *makeTexImage(char *loadfile) {
    int i, j, c, width, height;
    GLubyte *texImage;

    /*
      Onlx works for .png or .tif images.  NULL is returned if errors occurred.
      loadImageRGA() is from imageio library downloaded from Internet.
    */
    texImage = loadImageRGBA((char *)loadfile, &width, &height);
    texImageWidth = width;
    texImageHeight = height;

    return texImage;
}

void init(void) {
    glClearColor(0, 0, 0, 1.0);
    glShadeModel(GL_FLAT);

    //  glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // handles is global
    glGenTextures(6, handles);
    for (int i = 0; i < 6; ++i) {
        GLubyte *texImage = makeTexImage(maps[i]);
        if (!texImage) {
            printf("\nError reading %s \n", maps[i]);
            continue;
        }
        glBindTexture(GL_TEXTURE_2D, handles[i]);  // now we work on handles
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImageWidth,
                     texImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

        delete texImage;  // free memory holding texture image
    }
    printf("\nUse mouse to rotate the cube and s or S to swap rotating axis and L to change light shades\n");
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //  gluLookAt ( deltaMovX , deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0 );
    float x0 = -1.0, y0 = -1, x1 = 1, y1 = 1, z0 = 1;
    float face[6][4][3] = {
        {{x0, y0, z0}, {x1, y0, z0}, {x1, y1, z0}, {x0, y1, z0}},      // front
        {{x0, y1, -z0}, {x1, y1, -z0}, {x1, y0, -z0}, {x0, y0, -z0}},  // back
        {{x1, y0, z0}, {x1, y0, -z0}, {x1, y1, -z0}, {x1, y1, z0}},    // right
        {{x0, y0, z0}, {x0, y1, z0}, {x0, y1, -z0}, {x0, y0, -z0}},    // left
        {{x0, y1, z0}, {x1, y1, z0}, {x1, y1, -z0}, {x0, y1, -z0}},    // top
        {{x0, y0, z0}, {x0, y0, -z0}, {x1, y0, -z0}, {x1, y0, z0}}     // bottom
    };
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //  printf("(%d, %d)",GLUT_SCREEN_WIDTH,GLUT_SCREEN_HEIGHT);
    //  gluLookAt ( deltaMovX , deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0 );
    glPushMatrix();
    glRotatef(anglex + lx, 1.0, 0.0, 0.0);  // rotate the cube along x-axis
    // Adding Lighting
    if (lightSwitch == 1) {
        //  printf("Light On\n");
        glEnable(GL_LIGHTING);
    } else if (lightSwitch == 2) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, light_diffuse);
    } else {
        //  printf("Light Off\n");
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHT0);
    }
    if (swapVal) {
        glRotatef(angley + ly, 0.0, 1.0, 0.0);  // rotate along y-axis
        glRotatef(anglez + lz, 0.0, 0.0, 1.0);  // rotate along z-axis
    } else {
        glRotatef(angley + lz, 0.0, 1.0, 0.0);  // rotate along y-axis
        glRotatef(anglez + ly, 0.0, 0.0, 1.0);  // rotate along z-axis
    }

    for (int i = 0; i < 6; ++i) {  // draw cube with texture images
        glBindTexture(GL_TEXTURE_2D, handles[i]);
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
// Pressing of key from keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            swapVal = (swapVal + 1) % 2;
            break;
        case 'l':
            lightSwitch = (lightSwitch + 1) % 3;
            break;
        case 27: /* escape */
            glutDestroyWindow(window);
            exit(0);
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.00001, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(deltaMovX, deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0);
}

void mouseMove(int x, int y) {
    // this will onlx be true when the left button is down
    if (yOrigin >= 0) {
        // update deltaAngle
        deltaAnglez = (x - xOrigin) * 0.3f;
        deltaAngle = (y - yOrigin) * 0.3f;
        // update camera's direction
        // lx = -sin(anglex + deltaAngle);
        // lz = cos(anglex + deltaAngle);
        lx = deltaAngle;
        lz = deltaAnglez;
        // printf("anglex+lx: %f\n",anglex+lx);
    }
}

double modVal(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}
void mouseButton(int button, int state, int x, int y) {
    // onlx start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is released
        if (state == GLUT_UP) {
            anglex = anglex + lx;
            if (swapVal)
                anglez = anglez + lz;
            else
                angley = angley + lz;

            lx = 0;
            lz = 0;
            // printf("angle: %f\n",anglex);
            yOrigin = -1;
            xOrigin = -1;
        } else {  // state = GLUT_DOWN
            yOrigin = y;
            xOrigin = x;
        }
    }
    if (button == 3) {
        double valC = (1 - (double)1 / (10 * modVal(deltaMovX, deltaMovY, deltaMovZ)));
        // printf("%f\n",valC);
        deltaMovX *= valC;
        deltaMovY *= valC;
        deltaMovZ *= valC;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(deltaMovX, deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0);
    } else if (button == 4) {
        double valC = (1 + (double)1 / (10 * modVal(deltaMovX, deltaMovY, deltaMovZ)));
        deltaMovX *= valC;
        deltaMovY *= valC;
        deltaMovZ *= valC;
        // glutPostRedisplay();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(deltaMovX, deltaMovY, deltaMovZ, 0, 0, 0, 0, 1, 0);
    }
}

int main(int argc, char **argv) {
    // GLUT INITIALIZATION
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutMainLoop();
    return 0;
}
