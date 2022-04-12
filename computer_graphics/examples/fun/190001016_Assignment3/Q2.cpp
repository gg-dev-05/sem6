// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>

/**
 * initialPoint.first  = x coordinate
 * initialPoint.second = y coordinate
 */
std::pair<int, int> initialPoint;

/**
 * finalPoint.first  = x coordinate
 * finalPoint.second = y coordinate
 */
std::pair<int, int> finalPoint;

/**
 * @brief drawing lines using mid point line drawing algorithm
 *
 * @return std::vector<std::pair<int, int>> vector containing all points in order
 */
std::vector<std::pair<int, int>> drawWithMidPointLineDrawingAlgo() {
    std::vector<std::pair<int, int>> MPLDAPoints;

    int delta_x = finalPoint.first - initialPoint.first;
    int delta_y = finalPoint.second - initialPoint.second;

    // boolean for inverting the line W.R.T Y-AXIS
    bool invertWRT_Y_AXIS = false;

    // boolean for inverting the line W.R.T Y = X Lin
    bool invertWRT_Y_X = false;

    // since the slope of the line is -ve thus we invert the line w.r.t Y axis
    if (delta_x * delta_y < 0) {
        // set boolean to true to invert back the points after calculation
        invertWRT_Y_AXIS = true;
        initialPoint.first *= -1;
        finalPoint.first *= -1;
    }

    // if slope of the line > 1, invert the line w.r.t Y = X to make its
    // slope < 1
    if (abs(delta_y) > abs(delta_x)) {
        invertWRT_Y_X = true;
        std::swap(initialPoint.first, initialPoint.second);
        std::swap(finalPoint.first, finalPoint.second);
        delta_x *= -1;
        delta_y *= -1;
    }

    // consider the initial point as the one on the left side of the screen
    if (initialPoint.first > finalPoint.first) {
        std::swap(initialPoint, finalPoint);
    }

    // re calculating deltas after changes
    delta_x = finalPoint.first - initialPoint.first;
    delta_y = finalPoint.second - initialPoint.second;

    // mid point line drawing algorithm for slope b/w 0 & 1
    double decisionParameter = delta_y + 1.0 * delta_x / 2.0;
    int y = initialPoint.second;
    for (int x = initialPoint.first; x <= finalPoint.first; x++) {
        if (x == finalPoint.first && y == finalPoint.second) break;
        MPLDAPoints.push_back({x, y});
        if (decisionParameter > 0) {
            x++;
            y++;
            decisionParameter += delta_y - delta_x;
        } else {
            decisionParameter += delta_y;
        }
    }

    // invert back the line if we inverted it previously
    if (invertWRT_Y_X) {
        for (auto &i : MPLDAPoints) {
            std::swap(i.first, i.second);
        }
    }

    // invert back the line if we inverted it previously
    if (invertWRT_Y_AXIS) {
        for (auto &i : MPLDAPoints) {
            i.first *= -1;
        }
    }

    return MPLDAPoints;
}

void draw() {
    auto bresenham_points = drawWithMidPointLineDrawingAlgo();

    for (auto i : bresenham_points) {
        printf("(%d,%d)\n", i.first, i.second);
    }

    // plotting the points
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 0);
    for (auto i : bresenham_points) {
        glVertex2f(i.first, i.second);
    }
    glEnd();

    glFlush();
}

int main(int argc, char *argv[]) {
    int x1, x2, y1, y2;
    std::cin >> initialPoint.first >> initialPoint.second >> finalPoint.first >> finalPoint.second;

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Assignment 3 : (MID POINT LINE DRAWING ALGORITHM)");
    glutDisplayFunc(draw);
    gluOrtho2D(-50, 50, -50, 50);
    glutMainLoop();
}