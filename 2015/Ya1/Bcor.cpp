#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, a;

    Point() {}
    
    Point(int _x, int _y): x(_x), y(_y), a(-1) {}

    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
};

const int MAXN = 1005;
Point p[MAXN], q[2 * MAXN];

int cp(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

bool operator<(const Point &a, const Point &b) {
    if(a.x < 0 || (a.x == 0 && a.y < 0)) {
        if(b.x < 0 || (b.x == 0 && b.y < 0))
            return cp(a, b) > 0;
        return true;
    }
    if(b.x < 0 || (b.x == 0 && b.y < 0))
        return false;
    return cp(a, b) > 0;
}

bool cmp(const Point &a, const Point &b) {
    return a - q[0] < b - q[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y >> p[i].a;
        sum += p[i].a;
    }
    int ans = sum;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            q[j] = p[j];
        swap(q[i], q[0]);
        sort(q + 1, q + n, cmp);
        for(int j = 1; j < n; j++)
            q[n - 1 + j] = q[j];
        int cur = 0;
        for(int j = 1, k = 1; j < n; j++) {
            while(k < j + n - 1 && cp(q[j] - q[0], q[k] - q[0]) >= 0) {
                cur += q[k].a;
                k++;
            }
            ans = min(ans, int(abs(sum - 2 * cur)));
            cur -= q[j].a;
        }
    }
    cout << ans << '\n';
    return 0;
}
