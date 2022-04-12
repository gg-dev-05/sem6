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

std::vector<std::pair<int, int>> ddaMidPoint() {
    std::vector<std::pair<int, int>> points;

    int x = 0, y = RADIUS;
    int d = 1 - RADIUS;
    while (x <= y) {
        points.push_back({x, y});
        x++;
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            y--;
            d += 2 * (x - y) + 5;
        }
    }

    // find coordinates for other octants
    recurseForOctants(points);

    // shift origin to new center
    shiftOrigin(points, xCenter, yCenter);

    return points;
}

void draw() {
    auto points = ddaMidPoint();
    for (auto i : points) {
        printf("(%d,%d)\n", i.first, i.second);
    }

    // plotting the points
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
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
    glutCreateWindow("Assignment 4 : Mid Point Algorithm Circle");
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(draw);
    gluOrtho2D(0, 1000, 0, 1000);
    glutMainLoop();
}
