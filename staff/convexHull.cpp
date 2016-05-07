#include <bits/stdc++.h>

using namespace std;

#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define pointtt template<typename T>
pointtt struct point
{
    T x, y;
    point(T _x, T _y) : x(_x), y(_y) {}
    point(){}
    point operator+(point b) { return point(x + b.x, y + b.y); }
    point operator-() { return point(-x, -y); }
    T operator!() { return x * x + y * y; }
    bool operator<(point b) { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(point<T>&a,point<T>&b){return!point<T>(a+-b);}
pointtt int orientation(point<T>&a,point<T>&b,point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?1:q<0?-1:0;}
pointtt vector<point<T>>convexHull(vector<point<T>>a){sort(a.begin(),a.end());int n=a.size(),j=-1,k=0;ROF(i,n-2,0)a.push_back(a[i]);fori(a.size()){for(;j>k&&orientation(a[j-1],a[j],a[i])!=1;--j);a[++j]=a[i];if(!k&&i==n-1)k=j;}a.resize(j);return a;}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<point<int>> a(n);
    fori(n)
        cin >> a[i];
    a = convexHull(a);
    a.push_back(a[0]);
    double ans = 0;
    for (int i = 1; i < a.size(); ++i)
        ans += sqrt(dist(a[i - 1], a[i]));
    cout.precision(10);
    cout << fixed << ans << "\n";
    return 0;
}
