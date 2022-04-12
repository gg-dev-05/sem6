#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>

using namespace std;

vector<int> Color = {0, 1, 0};
vector<int> Border = {1, 0, 0};

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

class EdgeEntry {
   public:
    int y_max;
    int x;
    int del_x;
    int del_y;
    int inc;
    EdgeEntry *next;

    EdgeEntry(int y_max, int x, int del_x, int del_y) {
        this->y_max = y_max;
        this->x = x;
        this->del_x = del_x;
        this->del_y = del_y;
        this->next = NULL;
        this->inc = del_x;
    }
};

vector<Point> points;
int y_lower = INT_MAX;
int y_upper = INT_MIN;

vector<vector<Point>> Edges;

bool compare(vector<Point> &P1, vector<Point> &P2) {
    return P1[0].y < P2[0].y;
}

void create_edges() {
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

void createEdgeTable(vector<EdgeEntry *> &EdgeTable) {
    int edgesIndex = 0;
    int n = Edges.size();
    for (int y = y_lower; y <= y_upper; y++) {
        EdgeEntry *head = new EdgeEntry(0, 0, 0, 0);
        EdgeEntry *ptr = head;
        EdgeTable[y] = head;
        while (edgesIndex < n) {
            if (Edges[edgesIndex][0].y == y) {
                int del_x = Edges[edgesIndex][1].x - Edges[edgesIndex][0].x;
                int del_y = Edges[edgesIndex][1].y - Edges[edgesIndex][0].y;
                EdgeEntry *Curr = new EdgeEntry(Edges[edgesIndex][1].y, Edges[edgesIndex][0].x, del_x, del_y);
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
    glColor3f(Color[0], Color[1], Color[2]);
    glBegin(GL_POINTS);
    for (int x = start; x < end; x++) {
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

void paint(vector<int> &fillPoints, int y) {
    sort(fillPoints.begin(), fillPoints.end());
    for (int i = 0; i < fillPoints.size(); i++) {
        if (i % 2 == 1)
            fill(fillPoints[i - 1], fillPoints[i], y);
    }
}

void UpdateEdgeTable(EdgeEntry *head, int y, vector<EdgeEntry *> &EdgeTable) {
    EdgeEntry *ptr = head->next;
    EdgeEntry *prev = head;
    vector<int> fillPoints;

    while (ptr) {
        if (ptr->y_max <= y) {
            prev->next = ptr->next;
            ptr = ptr->next;
            continue;
        } else {
            int del_x = ptr->del_x;
            int del_y = ptr->del_y;
            int value = 0;
            value += del_x / del_y;
            if ((del_x % del_y) > del_y / 2) {
                value++;
            }
            ptr->del_x += ptr->inc;
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
    paint(fillPoints, y);
}

void fill_shape(int z) {
    create_edges();

    vector<EdgeEntry *> EdgeTable(y_upper + 1);

    createEdgeTable(EdgeTable);

    EdgeEntry *head = new EdgeEntry(0, 0, 0, 0);
    for (int y = y_lower; y < y_upper; y++) {
        UpdateEdgeTable(head, y, EdgeTable);
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Outline of shape
    glLineWidth(3);
    glColor3f(Border[0], Border[1], Border[2]);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < points.size(); i++) {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
    glFlush();

    cout << "Start Fill? (Y/n)";
    int x;
    cin >> x;

    sleep(1);
    fill_shape(x);

    glFlush();
}

int main(int C, char *V[]) {
    freopen("concave.in", "r", stdin);
    int n;
    cout << "\nEnter number of points of shape: ";
    cin >> n;
    cout << "\n Enter the points in clockwise manner \n";
    for (int i = 0; i < n; i++) {
        int x, y;
        cout << "\nPoint " << i + 1 << " : ";
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    glutInit(&C, V);
    glutInitWindowPosition(0, 000);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Scan Line Filling");
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 800, 0, 800);
    glutDisplayFunc(draw);
    glutMainLoop();
}