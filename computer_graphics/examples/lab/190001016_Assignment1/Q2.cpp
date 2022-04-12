// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include "helper.hpp"

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // top triangle
    glColor3f(0.8, 0.4, 0.2);
    drawEquilateralTriangle(100, 500, 800, true);

    // walls rectangle
    glColor3f(0.49, 0.9, 0.90);
    drawRectangle(200, 100, 600, 400, true);

    // left window
    glColor3f(0.49, 0.73, 0.90);
    drawRectangle(250, 300, 100, 100, true);

    // right window
    glColor3f(0.49, 0.73, 0.90);
    drawRectangle(650, 300, 100, 100, true);

    // door
    glColor3f(0.3, 0.2, 0.1);
    drawRectangle(425, 150, 150, 250, true);

    // knob
    glColor3f(1, 1, 1);
    drawCircle(440, 275, 5, true);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    char windowTitle[] = "Assignment 1: Q2.cpp";
    initializeWindow(1000, 900, windowTitle);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}