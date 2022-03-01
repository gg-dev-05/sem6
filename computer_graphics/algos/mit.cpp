#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

#define ll long long
#define ld long double

#define rep(i, a, b) for (ll i = a; i < b; i++)
#define repb(i, a, b) for (ll i = a; i >= b; i--)

#define err() cout << "--------------------------" << endl;
#define errA(A)           \
    for (auto i : A)      \
        cout << i << " "; \
    cout << endl;
#define err1(a) cout << #a << " " << a << endl
#define err2(a, b) cout << #a << " " << a << " " << #b << " " << b << endl
#define err3(a, b, c) cout << #a << " " << a << " " << #b << " " << b << " " << #c << " " << c << endl
#define err4(a, b, c, d) cout << #a << " " << a << " " << #b << " " << b << " " << #c << " " << c << " " << #d << " " << d << endl

#define pb push_back
#define all(A) A.begin(), A.end()
#define allr(A) A.rbegin(), A.rend()
#define ft first
#define sd second

#define pll pair<ll, ll>
#define V vector<ll>
// #define S set<ll>
#define VV vector<V>
#define Vpll vector<pll>

#define endl "\n"

const ll logN = 20;
const ll M = 1000000007;
const ll INF = 1e18;
#define PI 3.14159265

const ll N = 100005;

// Matrices using vectors

ld add(ld a, ld b) {
    return a + b;
}

ld mult(ld a, ld b) {
    return a * b;
}

struct matrix {
    ll n, m;
    vector<vector<ld>> arr;

    matrix(ll n1, ll m1) {
        n = n1;
        m = m1;
        arr.resize(n, vector<ld>(m, 0));
    }
    void null() {
        rep(i, 0, n) rep(j, 0, m) arr[i][j] = 0;
    }
    void iden() {
        null();
        rep(i, 0, n) arr[i][i] = 1;
    }
    matrix operator+(const matrix o) const {
        matrix res(n, m);
        rep(i, 0, n) rep(j, 0, m) res.arr[i][j] = add(arr[i][j], o.arr[i][j]);
        return res;
    }
    matrix operator*(const matrix o) const {
        matrix res(n, o.m);
        rep(i, 0, n) rep(j, 0, o.m) {
            ld temp = 0;
            rep(k, 0, m) temp = add(temp, mult(arr[i][k], o.arr[k][j]));
            res.arr[i][j] = temp;
        }
        return res;
    }
    void print() {
        rep(i, 0, n) {
            rep(j, 0, m) cout << fixed << setprecision(3) << setfill(' ') << setw(8) << arr[i][j] << " ";
            cout << endl;
        }
        err();
    }
};

void print(matrix m) {
    rep(i, 0, m.n) {
        rep(j, 0, m.m) cout << fixed << setprecision(3) << setfill(' ') << setw(8) << m.arr[i][j] << " ";
        cout << endl;
    }
    err();
}

// matrix matexpo(matrix a,ll n){
//     matrix res(a.n,a.m);
//     res.iden();
//     while(n){
//         if(n&1) res = res*a;
//         a = a*a;
//         n/=2;
//     }
//     return res;
// }

// 3 Dimension

matrix rotX(ld s, ld c) {
    err2(s, c);
    matrix m(4, 4);
    m.iden();
    m.arr[1][1] = c;
    m.arr[1][2] = -s;
    m.arr[2][1] = s;
    m.arr[2][2] = c;
    return m;
}

matrix rotY(ld s, ld c) {
    err2(s, c);
    matrix m(4, 4);
    m.iden();
    m.arr[0][0] = c;
    m.arr[0][2] = s;
    m.arr[2][0] = -s;
    m.arr[2][2] = c;
    return m;
}

matrix rotZ(ld s, ld c) {
    err2(s, c);
    matrix m(4, 4);
    m.iden();
    m.arr[0][0] = c;
    m.arr[0][1] = -s;
    m.arr[1][0] = s;
    m.arr[1][1] = c;
    return m;
}

matrix rotX(ld theta) {
    matrix m(4, 4);
    m.iden();
    err1(theta);
    ld tmp = theta;
    m.arr[1][1] = cos(tmp);
    m.arr[1][2] = -sin(tmp);
    m.arr[2][1] = sin(tmp);
    m.arr[2][2] = cos(tmp);
    return m;
}

matrix rotY(ld theta) {
    matrix m(4, 4);
    m.iden();
    err1(theta);
    ld tmp = theta;
    m.arr[0][0] = cos(tmp);
    m.arr[0][2] = sin(tmp);
    m.arr[2][0] = -sin(tmp);
    m.arr[2][2] = cos(tmp);
    return m;
}

matrix rotZ(ld theta) {
    matrix m(4, 4);
    m.iden();
    err1(theta);
    ld tmp = theta;
    m.arr[0][0] = cos(tmp);
    m.arr[0][1] = -sin(tmp);
    m.arr[1][0] = sin(tmp);
    m.arr[1][1] = cos(tmp);
    return m;
}

matrix T(ld x, ld y, ld z) {
    matrix m(4, 4);
    m.iden();
    m.arr[0][3] = x;
    m.arr[1][3] = y;
    m.arr[2][3] = z;
    return m;
}

matrix S(ld x, ld y, ld z) {
    matrix m(4, 4);
    m.iden();
    m.arr[0][0] = x;
    m.arr[1][1] = y;
    m.arr[2][2] = z;
    return m;
}

matrix refXY() {
    matrix m(4, 4);
    m.iden();
    m.arr[2][2] = -1;
    return m;
}

matrix shearXY(ld x, ld y) {
    matrix m(4, 4);
    m.iden();
    m.arr[0][2] = x;
    m.arr[1][2] = y;
    return m;
}

vector<ld> cross_product(vector<ld> a, vector<ld> b) {
    vector<ld> res(3);
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = -a[0] * b[2] + a[2] * b[0];
    res[2] = a[0] * b[1] - a[1] * b[0];
    return res;
}

vector<ld> unit(vector<ld> a) {
    ld den = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] /= den;
    a[1] /= den;
    a[2] /= den;
    return a;
}

matrix rot_pro(vector<ld> vpn, vector<ld> vup) {
    matrix m(4, 4);
    m.iden();
    vector<ld> Rz = unit(vpn);
    vector<ld> Rx = unit(cross_product(vup, Rz));
    vector<ld> Ry = cross_product(Rz, Rx);
    rep(i, 0, 3) {
        m.arr[0][i] = Rx[i];
        m.arr[1][i] = Ry[i];
        m.arr[2][i] = Rz[i];
    }
    return m;
}

// 2 Dimension

matrix rot(ld theta) {
    matrix m(3, 3);
    m.iden();
    err1(theta);
    ld tmp = theta;
    m.arr[0][0] = cos(tmp);
    m.arr[0][1] = -sin(tmp);
    m.arr[1][0] = sin(tmp);
    m.arr[1][1] = cos(tmp);
    return m;
}

matrix rot(ld s, ld c) {
    matrix m(3, 3);
    m.iden();
    m.arr[0][0] = c;
    m.arr[0][1] = -s;
    m.arr[1][0] = s;
    m.arr[1][1] = c;
    return m;
}

matrix T(ld x, ld y) {
    matrix m(3, 3);
    m.iden();
    m.arr[0][2] = x;
    m.arr[1][2] = y;
    return m;
}

matrix S(ld x, ld y) {
    matrix m(3, 3);
    m.iden();
    m.arr[0][0] = x;
    m.arr[1][1] = y;
    return m;
}

matrix refX() {
    matrix m(3, 3);
    m.iden();
    m.arr[1][1] = -1;
    return m;
}

matrix round(matrix m) {
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++) {
            ld f = (double)round(1000 * m.arr[i][j]);
            m.arr[i][j] = f / 1000;
        }
    return m;
}

matrix get() {
    matrix m(4, 4);
    m.iden();
    ld zmin = -0.4;
    err1(zmin);
    err1(1 / (1 + zmin));
    m.arr[2][2] = 1 / (1 + zmin);
    m.arr[3][2] = -1;
    m.arr[2][3] = -zmin / (1 + zmin);
    m.arr[3][3] = 0;
    m.print();
    return m;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // matrix res = T(90, 1910) * S(20, 20) * S(66, 66) * S(1.0 / 100, 1.0 / 100) * T(-25, -15);
    // res.print();
    // matrix res = T(1, 1);
    // matrix res = rotY(90.0 * PI / 180.0);
    // matrix res = rotX(60.0 * PI / 180.0) * T(-2, -2, -2);
    // res.print();

    // matrix P(3, 3);
    // matrix P(4, 4);

    // P.arr = {{50, 75, 100}, {90, 15, 90}, {1, 1, 1}};
    // P.arr = {{28, 53, 71, 44}, {33, 53, 48, 64}, {39, 64, 48, 73}, {1, 1, 1, 1}};
    // P.arr = {{3}, {2}, {1}, {1}};

    ld x = 35, y = 33, z = 25, d1 = sqrt(x * x + z * z), d = sqrt(x * x + y * y + z * z);
    ld x1 = 5, y1 = 7, z1 = 15;  // pointed shifted to origin
    matrix T1 = T(-x1, -y1, -z1);
    matrix T2 = rotY(-x / d1, z / d1);
    matrix T3 = rotX(y / d, d1 / d);
    matrix T4 = rotZ(30.0 * PI / 180.0);
    matrix T5 = rotX(-y / d, d1 / d);
    matrix T6 = rotY(x / d1, z / d1);
    matrix T7 = T(x1, y1, z1);
    matrix P(4, 4);
    P.arr = {{28, 53, 71, 44}, {33, 71, 53, 64}, {39, 64, 48, 73}, {1, 1, 1, 1}};

    matrix res = T7 * T6 * T5 * T4 * T3 * T2 * T1;
    matrix final = res * P;
    res.print();
    final.print();

    // matrix T = res * P;
    // T.print();

    return 0;
}