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
    double t = (x1 * y2 - x2 * y1) + (y1 * x3 - x1 * y3) + (x2 * y3 - x3 * y2);
    return t > eps ? -1 : t < -eps ? 1 : 0;
}
 
double distance(double sx, double sy, double a, double b, double c, double d)
{
    if (a >= sx)
        return dist(sx, sy, a, b);
    if (c <= sx)
        return dist(sx, sy, c, d);
    //cout << "lol " << sy << " " << b << "\n";
    return sy - b;
}

int main()
{
//    freopen("in", "r", stdin);
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
 //       fori(a.size())
//        a.pb(segment(a.back().x - 1, a.back().y, a.back().q + 1, a.back().w));
        fori1(a.size() - 1)
        {
/*            cout << "S = " << sx << " " << sy << "\n";
            cout << "T = " << t.x << " " << t.y << " " << t.q << " " << t.w << "\n";
            cout << "a[i] = " << a[i].x << " " << a[i].y << " " << a[i].q << " " << a[i].w << "\n";
            cout << "answer = " << answer << "\n\n";
  */          //cout << "ori s tb a[i]e " << ori(sx, sy, t.x, t.y, a[i].q, a[i].w) << "\n";
            //cout << "ori s te a[i]b " << ori(sx, sy, t.q, t.w, a[i].x, a[i].y) << "\n";
            if (ori(sx, sy, t.x, t.y, a[i].q, a[i].w) != -1)
                answer += dist(sx, sy, t.x, t.y),
                sx = t.x,
                sy = t.y,
                t = a[i];
            else
            if (ori(sx, sy, t.q, t.w, a[i].x, a[i].y) != 1)
                answer += dist(sx, sy, t.q, t.y),
                sx = t.q,
                sy = t.w,
                t = a[i];
            else
            {
                if (ori(sx, sy, t.x, t.y, a[i].x, a[i].y) != 1)
                    t.x = a[i].x,
                    t.y = a[i].y;
                if (ori(sx, sy, t.q, t.w, a[i].q, a[i].w) != -1)
                    t.q = a[i].q,
                    t.w = a[i].w;
            }
        }
        //cout << "answer = " << answer << "\n";
        //cout << "S = " << sx << " " << sy << "\nT = ";
        //cout << t.x << " " << t.y << " " << t.q << " " << t.w << "\nF = ";
        //cout << a.back().x << " " << a.back().y << " " << a.back().q << " " << a.back().w << "\n";
        if (((abs(ori(sx, sy, t.x, t.y, a.back().x, a.back().y) +
            ori(sx, sy, t.x, t.y, a.back().q, a.back().w)) == 2 &&
            ori(sx, sy, sx, -1000000, t.x, t.y) == -1) ||

            (abs(ori(sx, sy, t.q, t.w, a.back().x, a.back().y) +
            ori(sx, sy, t.q, t.w, a.back().q, a.back().w)) == 2 &&
            ori(sx, sy, sx, -1000000, t.q, t.w) == 1)))
            answer += min(dist(sx, sy, t.x, t.y) + distance(t.x, t.y, a.back().x, a.back().y, a.back().q, a.back().w),
                          dist(sx, sy, t.q, t.w) + distance(t.q, t.w, a.back().x, a.back().y, a.back().q, a.back().w));
        else
            answer += distance(sx, sy,  a.back().x, a.back().y, a.back().q, a.back().w);
        printf("%.11lf\n", answer);
    }
}
