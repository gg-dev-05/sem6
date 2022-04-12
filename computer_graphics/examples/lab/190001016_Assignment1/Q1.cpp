// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include "helper.hpp"

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Brown Rectangle
    glColor3f(0.6, 0.3, 0.1);
    drawRectangle(475, 100, 50, 250, true);

    // bottom triangle
    glColor3f(0.4, 0.9, 0);
    drawEquilateralTriangle(250, 300, 500, true);

    // mid triangle
    glColor3f(0.4, 0.9, 0);
    drawEquilateralTriangle(250, 430, 500, true);

    // top triangle
    glColor3f(0.4, 0.9, 0);
    drawEquilateralTriangle(250, 560, 500, true);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    char windowTitle[] = "Assignment 1: Q1.cpp";
    initializeWindow(1000, 900, windowTitle);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}