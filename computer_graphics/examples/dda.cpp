// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include "helper.hpp"

int RADIUS = 50;
int xCenter = 0;
int yCenter = 0;

std::vector<std::pair<int, int>> ddaCircle() {
    std::vector<std::pair<int, int>> points;
    double dtheta = 1.0 / RADIUS;
    double cos_dtheta = cos(dtheta);
    double sin_dtheta = sin(dtheta);
    double x = RADIUS, y = 0;

    // calculating coordinates for 1st Octant
    std::pair<double, double> prev = {x, y};
    for (double theta = 0; theta <= M_PI / 4.0; theta += dtheta) {
        points.push_back(prev);
        x = prev.first * cos_dtheta - prev.second * sin_dtheta;
        y = prev.second * cos_dtheta + prev.first * sin_dtheta;
        prev = {x, y};
    }

    // find coordinates for other octants
    recurseForOctants(points);

    // shift origin to new center
    shiftOrigin(points, xCenter, yCenter);

    return points;
}

void draw() {
    auto points = ddaCircle();
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
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Assignment 4 : DDA Circle");
    glutDisplayFunc(draw);
    gluOrtho2D(-100, 100, -100, 100);
    glutMainLoop();
}
