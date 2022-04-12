// 190001016
// Garvit Galgat

#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

int n;
vector<pair<int, int>> pts;

int nbd;
vector<float> borderColor = {1, 0, 0};
vector<float> fillColor = {0, 1, 0};

void boundaryFillAlgorithm(int xCoordinate, int yCoordinate) {
    float color[3];
    glReadPixels(xCoordinate, yCoordinate, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    vector<float> cmp = {color[0], color[1], color[2]};
    if ((color[0] != borderColor[0] || color[1] != borderColor[1] || color[2] != borderColor[2]) &&
        cmp != fillColor) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2f(xCoordinate, yCoordinate);
        glEnd();
        glFlush();
        if (nbd == 1) {
            boundaryFillAlgorithm(xCoordinate, yCoordinate - 1);
            boundaryFillAlgorithm(xCoordinate, yCoordinate + 1);
            boundaryFillAlgorithm(xCoordinate + 1, yCoordinate);
            boundaryFillAlgorithm(xCoordinate + 1, yCoordinate - 1);
            boundaryFillAlgorithm(xCoordinate + 1, yCoordinate + 1);
            boundaryFillAlgorithm(xCoordinate - 1, yCoordinate - 1);
            boundaryFillAlgorithm(xCoordinate - 1, yCoordinate);
            boundaryFillAlgorithm(xCoordinate - 1, yCoordinate + 1);
        } else {
            boundaryFillAlgorithm(xCoordinate + 1, yCoordinate);
            boundaryFillAlgorithm(xCoordinate, yCoordinate - 1);
            boundaryFillAlgorithm(xCoordinate - 1, yCoordinate);
            boundaryFillAlgorithm(xCoordinate, yCoordinate + 1);
        }
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(pts[i].first, pts[i].second);
    }
    glEnd();
    glFlush();
    int xInitial, yInitial;
    cout << "\n Enter an interior point: ";
    cin >> xInitial >> yInitial;
    boundaryFillAlgorithm(xInitial, yInitial);

    glFlush();
}

int main(int argc, char *argv[]) {
    cout << "\nNumber of points: ";
    cin >> n;
    cout << "Enter points (clockwise direction):";
    for (int i = 0; i < n; i++) {
        int xi, yi;
        cin >> xi >> yi;
        pts.push_back({xi, yi});
    }

    cout << "0: 4-neighbourhood\n1: 8-neighbourhood";
    cin >> nbd;
    if (nbd != 0 && nbd != 1) {
        cout << "Incorrect Input";
        exit(0);
    }
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Boundary Filling Algorithm");
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 800, 0, 800);
    glutDisplayFunc(draw);
    glutMainLoop();
}