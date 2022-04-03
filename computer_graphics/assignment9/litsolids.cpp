// This program shows three cyan objects illuminated with a single yellow
// light source.  It illustrates several of the lighting parameters.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
float x = 1, y = 1, z = 1;
GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
GLfloat cyan[] = {0.0, 1.0, 1.0, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat none[] = {0.0, 0.0, 0.0, 0.0};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    GLfloat direction[] = {x, y, z, 0};
    GLfloat positional[] = {x, y, z, 1};

    glPushMatrix();
    glTranslatef(x, y, z);
    GLfloat emission[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glLightfv(GL_LIGHT0, GL_POSITION, positional);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
    // Rotate the scene so we can see the tops of the shapes.
    glRotatef(-20.0, 1.0, 0.0, 0.0);

    // Make a cone.  The standard cone "points" along z; we want it pointing
    // along y, hence the 270 degree rotation about x.
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glTranslatef(-0.75, -0.5, 0.0);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glutSolidCone(1.0, 2.0, 70, 12);
    glPopMatrix();

    // Add a sphere to the scene.
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    glTranslatef(0.75, 0.0, -1.0);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

// We don't want the scene to get distorted when the window size changes, so
// we need a reshape callback.  We'll always maintain a range of -2.5..2.5 in
// the smaller of the width and height for our viewbox, and a range of -10..10
// for the viewbox depth.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    GLfloat aspect = GLfloat(w) / GLfloat(h);
    glLoadIdentity();
    if (w <= h) {
        // width is smaller, so stretch out the height
        glOrtho(-2.5, 2.5, -2.5 / aspect, 2.5 / aspect, -10.0, 10.0);
    } else {
        // height is smaller, so stretch out the width
        glOrtho(-2.5 * aspect, 2.5 * aspect, -2.5, 2.5, -10.0, 10.0);
    }
}

// Performs application specific initialization.  It defines lighting
// parameters for light source GL_LIGHT0: black for ambient, yellow for
// diffuse, white for specular, and makes it a directional source
// shining along <-1, -1, -1>.  It also sets a couple material properties
// to make cyan colored objects with a fairly low shininess value.  Lighting
// and depth buffer hidden surface removal are enabled here.
void init() {
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);    // so the renderer considers light
    glEnable(GL_LIGHT0);      // turn LIGHT0 on
    glEnable(GL_DEPTH_TEST);  // so the renderer considers depth
}

void keyboard(unsigned char key, int x_, int y_) {
    float val = 1;
    switch (key) {
        case 'x':
            x += val;
            break;
        case 'X':
            x -= val;
            break;
        case 'y':
            y += val;
            break;
        case 'Y':
            y -= val;
            break;
        case 'z':
            z += val;
            break;
        case 'Z':
            z -= val;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
// The usual application statup code.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cyan Shapes in Yellow Light");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}