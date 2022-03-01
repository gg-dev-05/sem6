#include <bits/stdc++.h>
using namespace std;
struct Point {
    double x;
    double y;
};
double m, c;
int main() {
    Point f, s;
    f.x = 1, f.y = 10, s.x = 10, s.y = 1;
    double dx, dy;
    dx = abs(s.x - f.x);
    dy = abs(s.y - f.y);

    Point new_c, old_c;
    new_c.x = f.x;
    new_c.y = f.y;

    if (dy > dx) {
        swap(f.x, f.y);
        swap(s.x, s.y);
        swap(dx, dy);
        swap(new_c.x, new_c.y);
    }

    double p_new = 2 * dy - dx, p_old;
    cout << "k | Xi | Yi | Pi | Pi+1 | Xi+1 | Yi+1\n";
    for (int k = 1; k <= (int)dx; k++) {
        old_c = new_c;
        p_old = p_new;
        if (p_new < (double)0) {
            if (new_c.x < s.x)
                new_c.x += 1.0;
            else
                new_c.x -= 1.0;
            p_new += 2 * dy;
        } else {
            if (new_c.y < s.y)
                new_c.y += 1.0;
            else
                new_c.y -= 1.0;

            if (new_c.x < s.x)
                new_c.x += 1.0;
            else
                new_c.x -= 1.0;

            p_new += 2 * (dy - dx);
        }

        if (dy > dx)
            cout << k - 1 << "    " << old_c.y << "    " << old_c.x << "    " << p_old << "    " << p_new << "    " << new_c.y << "    " << new_c.x << "\n";
        else
            cout << k - 1 << "    " << old_c.x << "    " << old_c.y << "    " << p_old << "    " << p_new << "    " << new_c.x << "    " << new_c.y << "\n";
    }
    return 0;
}