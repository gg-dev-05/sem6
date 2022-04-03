#include <GL/glut.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500

using namespace std;

float x = 3, y = 0, z = 0;
double r = 2;
double theta = 0;

void lights() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    // double r = 2.0;
    gluLookAt(r * cos(theta), 0, r * sin(theta), 0, 0, 0, 0, 1, 0);

    glEnable(GL_LIGHT0);
    GLfloat directional_light_position[] = {0, 0, 0, 0.0};
    GLfloat positional_light_position[] = {0, 0, 0, 1.0};
    // // set up light
    // float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuse[] = {1.0f, 0.3f, 0.4f, 1.0f};
    // float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // float position[] = {200.0f, 300.0f, 100.0f, 0.0f};

    // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_POSITION, directional_light_position);
    GLfloat emission[] = {0, 0, 0, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glutSolidSphere(1, 100, 100);
    glLightfv(GL_LIGHT0, GL_POSITION, positional_light_position);

    glPushMatrix();

    // Emerald
    float mat_ambient[] = {0.0215f, 0.1745f, 0.0215f, 0.55f};
    float mat_diffuse[] = {0.07568f, 0.61424f, 0.07568f, 0.55f};
    float mat_specular[] = {0.633f, 0.727811f, 0.633f, 0.55f};
    float shine[] = {76.8f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glTranslatef(3, 0, 0);
    glColor3f(1, 1, 0);
    glutSolidSphere(1, 100, 10);
    glPopMatrix();

    // /****** LIGHTS ******/
    // GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    // GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    // // 1.0 => Positional
    // // 0.0 => Directional
    // glEnable(GL_LIGHT0);
    // GLfloat light_position[] = {0, 0, 0, 0.0};
    // // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    // // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    // // glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // // GLfloat light_position[] = {x, y, z, 1.0};
    // // glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // /***************************/

    // /***** CAMERA ******/
    // // double r = 2.0;
    // gluLookAt(r * cos(theta), 0, r * sin(theta), 0, 0, 0, 0, 1, 0);
    // /******************/

    // /****** OBJECTS *****/
    // // GLfloat mat_specular[] = {1.0, 1.0, 1.0};
    // // GLfloat mat_shininess[] = {50.0};
    // // glDisable(GL_COLOR_MATERIAL);
    // glPushMatrix();
    // GLfloat emission[] = {0.88, 0.53, 0.16, 1.0};
    // GLfloat emission1[] = {1, 0, 0, 0.0};
    // glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    // glutSolidSphere(1, 100, 10);
    // GLfloat light_position1[] = {0, 0, 0, 1.0};
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    // glEnable(GL_LIGHT1);
    // glDisable(GL_LIGHT0);
    // glPopMatrix();
    // // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    // glPushMatrix();
    // glDisable(GL_COLOR_MATERIAL);
    // glMaterialfv(GL_FRONT, GL_EMISSION, emission1);
    // glTranslatef(3, 0, 0);
    // glutSolidSphere(1, 100, 10);
    // glEnable(GL_COLOR_MATERIAL);
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(1.5, 0, 0);
    // glutSolidSphere(0.3, 100, 10);
    // glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.001, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x_, int y_) {
    float val = 0.1;
    switch (key) {
        case 'd':
            theta += val;
            break;
        case 'a':
            theta -= val;
            break;
        case 's':
            r += val;
            break;
        case 'w':
            r -= val;
            break;
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

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Assignment 9");
    glEnable(GL_DEPTH_TEST);
    lights();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
