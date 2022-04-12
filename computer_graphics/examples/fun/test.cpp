#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -1);
    glColor3f(1, 1, 1);
    // glutSolidCube(1);
    DisplayStroke(0, 0, 0, 0.001, 1, 0, "H");
    glutSwapBuffers();
}

void reshapeFunction(int widthOfWindow, int heightOfWindow) {
    glViewport(0, 0, (GLsizei)widthOfWindow, (GLsizei)heightOfWindow);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)widthOfWindow / (GLfloat)heightOfWindow, 0.0001, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("ss");

    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunction);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
