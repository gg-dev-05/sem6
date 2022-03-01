#include <bits/stdc++.h>
using namespace std;

void bresenham(int x1, int y1, int xn, int yn) {
    int dx = abs(xn - x1);
    int dy = abs(yn - y1);

    if (dy > dx) {
        swap(x1, y1);
        swap(xn, yn);
        swap(dx, dy);
    }

    int x = x1, y = y1;
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        cout << x << " " << y << endl;
        x < xn ? x++ : x--;
        if (p < 0) {
            p += 2 * dy;
        } else {
            y < yn ? y++ : y--;
            p += 2 * (dy - dx);
        }
    }
}
int main(int argc, char const *argv[]) {
    bresenham(1, 10, 10, 1);
    return 0;
}
