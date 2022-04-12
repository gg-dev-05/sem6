// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "helper.hpp"

int RADIUS;
int xCenter;
int yCenter;

std::vector<std::pair<int, int>> bresenhamCircle() {
    std::vector<std::pair<int, int>> points;

    int x = 0, y = RADIUS;
    int d = 3 - 2 * RADIUS;
    while (y >= x) {
        points.push_back({x, y});
        x++;
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }

    // find coordinates for other octants
    recurseForOctants(points);

    // shift origin to new center
    shiftOrigin(points, xCenter, yCenter);

    return points;
}

void draw() {
    auto points = bresenhamCircle();
    for (auto i : points) {
        printf("(%d,%d)\n", i.first, i.second);
    }

    // plotting the points
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 0);
    for (auto i : points) {
        glVertex2f(i.first, i.second);
    }
    glEnd();

    glFlush();
}

int main(int argc, char *argv[]) {
    input(RADIUS, xCenter, yCenter);
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Assignment 4 : Bresenham Circle");
    glutDisplayFunc(draw);
    gluOrtho2D(-100, 100, -100, 100);
    glutMainLoop();
}
