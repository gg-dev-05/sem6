// 190001016
// Garvit Galgat

#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int leftEdge[500], rightEdge[500], totalPoints, xInitial, yInitial;
vector<pair<int, int>> points;

void utility(int xInitial, int yInitial, int xFinal, int yFinal) {
    float x, slope;

    // swap points if yinitial is higher than yfinal
    if (yInitial > yFinal)
        swap(xInitial, xFinal), swap(yInitial, yFinal);

    // calculating slopes
    if (yInitial == yFinal)
        slope = (xFinal - xInitial);
    else
        slope = (xFinal - xInitial) / (yFinal - yInitial);

    x = xInitial;
    for (int y = yInitial; y <= yFinal; y++) {
        if (x < leftEdge[y])
            leftEdge[y] = x;
        if (x > rightEdge[y])
            rightEdge[y] = x;

        x += slope;
    }
}

void ScanlineAlgorithm() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    for (int i = 0; i < 500; i++)
        leftEdge[i] = 500, rightEdge[i] = 0;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < totalPoints; i++)
        glVertex2i(points[i].first, points[i].second);

    glEnd();

    for (int i = 0; i < totalPoints; i++)
        utility(points[i].first, points[i].second, points[(i + 1) % totalPoints].first, points[(i + 1) % totalPoints].second);

    for (int y = 0; y < 500; y++) {
        for (int x = leftEdge[y]; x < rightEdge[y]; x++) {
            glBegin(GL_POINTS);
            glColor3f(0, 0, 1);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
    }

    glFlush();
}

int main(int argc, char *argv[]) {
    cout << "Enter number of points: ";
    cin >> totalPoints;
    cout << "\nEnter the points in order \n";
    for (int i = 0; i < totalPoints; i++) {
        cout << "\nPoint :";
        cin >> xInitial >> yInitial;
        points.push_back({xInitial, yInitial});
    }
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Polygon Filling Algorithm");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(ScanlineAlgorithm);
    glutMainLoop();
    return 0;
}