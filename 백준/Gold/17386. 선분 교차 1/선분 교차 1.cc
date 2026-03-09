#include <iostream>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    void read() { cin >> x >> y; }
};

int ccw(Point a, Point b, Point c) {
    ll v = (a.x * b.y) + (b.x * c.y) + (c.x * a.y)
        - (a.x * c.y) - (b.x * a.y) - (c.x * b.y);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

bool isCrossed(Point a, Point b, Point c, Point d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    return (ab < 0 && cd < 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Point a, b, c, d;
    a.read(); b.read();
    c.read(); d.read();

    cout << (isCrossed(a, b, c, d) ? 1 : 0);
    return 0;
}