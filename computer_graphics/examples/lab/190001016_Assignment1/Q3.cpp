// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include "helper.hpp"

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // using white for all lines
    glColor3f(1, 1, 1);

    // wheels
    drawCircle(300, 450, 100);
    drawCircle(700, 450, 100);

    // body
    drawLine(300, 450, 500, 450);
    drawLine(700, 450, 700, 600);
    drawLine(500, 450, 700, 600);
    drawLine(500, 450, 500, 600);
    drawLine(300, 450, 500, 600);
    drawLine(500, 600, 700, 600);

    // handle
    drawLineUsingSlope(650, 650, 100, -M_PI / 4);
    drawLineUsingSlope(650, 650, 40, M_PI / 4);
    drawLineUsingSlope(650 + 100 * cos(M_PI / 4), 650 - 100 * sin(M_PI / 4), 20, M_PI / 4);

    // seat
    glBegin(GL_LINE_LOOP);
    glVertex2f(480, 600);
    glVertex2f(530, 600);
    glVertex2f(530, 630);
    glVertex2f(480, 620);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    char windowTitle[] = "Assignment 1: Q3.cpp";
    initializeWindow(1000, 900, windowTitle);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}