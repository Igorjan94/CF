#include <bits/stdc++.h>
 
#define fori(n) for (int i = 0; i < n; ++i)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
 
#define fst first
#define snd second
#define pb push_back
 
double const eps = 0.000000001;
 
using namespace std;
 
struct segment
{
    double x, y, q, w;
    segment(double a, double b, double c, double d)
    {
        x = a;
        y = b;
        q = c;
        w = d;
    }
};
 
double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
 
int ori(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double t = (x1 * y2 - x2 * y1) + (y1 * x3 - x1 * y3) + (x1 * y2 - x2 * y1);
    return t > eps ? -1 : t < -eps ? 1 : 0;
}
 
int main()
{
    //freopen("in.c", "r", stdin);
    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
            return 0;
        double sx, sy, x, y, z;
        cin >> sx >> sy;
        vector<segment> a;
        fori(n)
            cin >> y >> x >> z,
            a.pb(segment(x, y, z, y));
        segment t = a[0];
        double answer = 0;
        fori1(n)
        {
            if (ori(sx, sy, t.x, t.y, a[i].q, a[i].w) == 1)
                answer += dist(sx, sy, t.x, t.y),
                sx = t.x,
                sy = t.y,
                t = a[i];
            else
            if (ori(sx, sy, t.q, t.w, a[i].x, a[i].y) == -1)
                answer += dist(sx, sy, t.q, t.y),
                sx = t.q,
                sy = t.w,
                t = a[i];
            else
            {
                if (ori(sx, sy, t.x, t.y, a[i].x, a[i].y) == -1)
                    t.x = a[i].x,
                    t.y = a[i].y;
                if (ori(sx, sy, t.q, t.w, a[i].q, a[i].w) == 1)
                    t.q = a[i].q,
                    t.w = a[i].w;
            }
        }
        cout << answer << "\n";
    }
}
