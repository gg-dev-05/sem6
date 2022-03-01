#include <GL/glut.h>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

std::vector<std::pair<int, int>> points;
std::pair<int, int> startingPoint;
std::vector<float> boundaryColor = {1, 0, 0};
std::vector<float> fillColor = {0, 0, 1};

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, -1, 1, 1, -1};

int selection = 0;
int minX = INT32_MAX, maxX = INT32_MIN, minY = INT32_MAX, maxY = INT32_MIN;

void fillPixel(int xCoordinate, int yCoordinate) {
    glBegin(GL_POINTS);
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glVertex2i(xCoordinate, yCoordinate);
    glEnd();
    glFlush();
}

bool isInside(int xCoordinate, int yCoordinate) {
    if (minX <= xCoordinate && xCoordinate <= maxX && minY <= yCoordinate && yCoordinate <= maxY)
        return true;
    printf("(%d,%d) is outside the boundary\n", xCoordinate, yCoordinate);
    return false;
}

bool recurseOnThisPoint(float colors[3]) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (colors[i] == fillColor[i])
            count++;
        else
            break;
    }
    if (count == 3) return false;
    count = 0;
    for (int i = 0; i < 3; i++) {
        if (colors[i] == boundaryColor[i])
            count++;
        else
            return true;
    }
    if (count == 3) return false;
    return true;
}

void boundaryFillAlgorithm(int xCoordinate, int yCoordinate) {
    if (!isInside(xCoordinate, yCoordinate)) return;
    float colors[3];
    glReadPixels(xCoordinate, yCoordinate, 1.0, 1.0, GL_RGB, GL_FLOAT, colors);
    if (recurseOnThisPoint(colors)) {
        fillPixel(xCoordinate, yCoordinate);
        if (selection == 0) {
            for (int i = 0; i < 4; i++)
                boundaryFillAlgorithm(xCoordinate + dx[i], yCoordinate + dy[i]);
        } else {
            for (int i = 0; i < 8; i++)
                boundaryFillAlgorithm(xCoordinate + dx[i], yCoordinate + dy[i]);
        }
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);
    glColor3f(boundaryColor[0], boundaryColor[1], boundaryColor[2]);
    glBegin(GL_LINE_LOOP);
    for (auto i : points) {
        glVertex2d(i.first, i.second);
        minX = std::min(minX, i.first);
        maxX = std::max(maxX, i.first);
        minY = std::min(minY, i.second);
        maxY = std::max(maxY, i.second);
    }
    glEnd();
    glFlush();

    boundaryFillAlgorithm(startingPoint.first, startingPoint.second);
}

int main(int argc, char *argv[]) {
    freopen("convex.in", "r", stdin);
    int n;
    std::cout << "Enter the total number of  points:";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        printf("Point %d\n", i + 1);
        printf("X:");
        std::cin >> x;
        printf("Y:");
        std::cin >> y;
        printf("\n");
        points.push_back({x, y});
    }
    std::cout << "[0]: 4-neighbours\n[1]: 8-neighbours\n";
    std::cin >> selection;

    std::cout << "Enter Starting Point (X):";
    std::cin >> startingPoint.first;
    std::cout << "Enter Starting Point (Y):";
    std::cin >> startingPoint.second;

    if (selection != 0 && selection != 1) {
        std::cout << "Invalid Selection\n";
        return 1;
    }

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Boundary Filling Algorithm");
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    glutDisplayFunc(draw);
    glutMainLoop();
}
