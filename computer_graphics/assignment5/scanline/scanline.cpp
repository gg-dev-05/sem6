// 190001016
// Garvit Galgat

#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int totalPoints;
vector<int> boundaryColor = {1, 0, 0};
vector<int> fillColor = {0, 1, 0};

class Point {
   public:
    int x;
    int y;
    Point() {}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Edge {
   public:
    int x;
    int y;
    Edge() {}
    Edge(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class EdgeData {
   public:
    int yMaximum;
    int x;
    int deltaX;
    int deltaY;
    int increment;
    EdgeData *next;

    EdgeData(int yMaximum, int x, int deltaX, int deltaY) {
        this->yMaximum = yMaximum;
        this->x = x;
        this->deltaX = deltaX;
        this->deltaY = deltaY;
        this->next = NULL;
        this->increment = deltaX;
    }
};

vector<Point> points;
int y_lower = INT_MAX;
int y_upper = INT_MIN;
vector<vector<Point>> Edges;

bool compare(vector<Point> &P1, vector<Point> &P2) {
    return P1[0].y < P2[0].y;
}

void createEdges() {
    int n = points.size();
    for (int i = 1; i < n; i++) {
        if (points[i - 1].y < points[i].y) {
            Edges.push_back({points[i - 1], points[i]});
        } else {
            Edges.push_back({points[i], points[i - 1]});
        }
        y_lower = min(y_lower, Edges.back()[0].y);
        y_upper = max(y_upper, Edges.back()[1].y);
    }
    if (points[0].y < points[n - 1].y) {
        Edges.push_back({points[0], points[n - 1]});
    } else {
        Edges.push_back({points[n - 1], points[0]});
    }
    sort(Edges.begin(), Edges.end(), compare);
}

void createEdgeTable(vector<EdgeData *> &edgeTable) {
    int edgesIndex = 0;
    int n = Edges.size();
    for (int y = y_lower; y <= y_upper; y++) {
        EdgeData *head = new EdgeData(0, 0, 0, 0);
        EdgeData *ptr = head;
        edgeTable[y] = head;
        while (edgesIndex < n) {
            if (Edges[edgesIndex][0].y == y) {
                int deltaX = Edges[edgesIndex][1].x - Edges[edgesIndex][0].x;
                int deltaY = Edges[edgesIndex][1].y - Edges[edgesIndex][0].y;
                EdgeData *Curr = new EdgeData(Edges[edgesIndex][1].y, Edges[edgesIndex][0].x, deltaX, deltaY);
                ptr->next = Curr;
                ptr = Curr;
            } else {
                break;
            }
            edgesIndex++;
        }
    }
}

void fill(int start, int end, int y) {
    glColor3f(fillColor[0], fillColor[1], fillColor[2]);
    glBegin(GL_POINTS);
    for (int x = start; x < end; x++) {
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

void markLine(vector<int> &fillPoints, int y) {
    sort(fillPoints.begin(), fillPoints.end());
    for (int i = 0; i < fillPoints.size(); i++) {
        if (i % 2 == 1)
            fill(fillPoints[i - 1], fillPoints[i], y);
    }
}

void UpdateEdgeTable(EdgeData *head, int y, vector<EdgeData *> &EdgeTable) {
    EdgeData *ptr = head->next;
    EdgeData *prev = head;
    vector<int> fillPoints;

    while (ptr) {
        if (ptr->yMaximum <= y) {
            prev->next = ptr->next;
            ptr = ptr->next;
            continue;
        } else {
            int deltaX = ptr->deltaX;
            int deltaY = ptr->deltaY;
            int value = 0;
            value += deltaX / deltaY;
            if ((deltaX % deltaY) > deltaY / 2) {
                value++;
            }
            ptr->deltaX += ptr->increment;
            fillPoints.push_back(ptr->x + value);
        }
        prev = ptr;
        ptr = ptr->next;
    }

    prev->next = EdgeTable[y]->next;
    ptr = prev->next;
    while (ptr) {
        fillPoints.push_back(ptr->x);
        ptr = ptr->next;
    }
    markLine(fillPoints, y);
}

void fill_shape() {
    createEdges();

    vector<EdgeData *> EdgeTable(y_upper + 1);

    createEdgeTable(EdgeTable);

    EdgeData *head = new EdgeData(0, 0, 0, 0);
    for (int y = y_lower; y < y_upper; y++) {
        UpdateEdgeTable(head, y, EdgeTable);
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3);
    glColor3f(boundaryColor[0], boundaryColor[1], boundaryColor[2]);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < points.size(); i++) {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
    glFlush();

    fill_shape();

    glFlush();
}

int main(int argc, char *argv[]) {
    freopen("convex.in", "r", stdin);
    cout << "Enter the total number of  points:";
    cin >> totalPoints;
    for (int i = 0; i < totalPoints; i++) {
        int x, y;
        printf("Point %d\n", i + 1);
        printf("X:");
        cin >> x;
        printf("Y:");
        cin >> y;
        printf("\n");
        points.push_back({x, y});
    }

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Scanline Algorithm");
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    glutDisplayFunc(draw);
    glutMainLoop();
}