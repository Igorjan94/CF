// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(size(a))

typedef  pair<int, int>   pii;
typedef   vector<int>     vi;
typedef    long long      ll;

#define pb push_back
#define all(a) begin(a), end(a)
#define ints(a...) int a; readln(a)

[[maybe_unused]] const int MOD = 1000000007;
[[maybe_unused]] const int INTMAX = numeric_limits<int>::max();

#define ttt12i template<class T1, class T2> inline
#define  ttti  template<class T> inline

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
template<class... Args> inline void readln(Args&... args){(read(args),...);}
template<class H, class...T> inline void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}

//Igorjan
//point
#define pointtt template<typename T = int>

pointtt struct point
{
    T x, y;
    point(){}
    point(T _x, T _y) : x(_x), y(_y) {}
    point operator=(const point& b) { x = b.x; y = b.y; return *this; }
    point operator+(const point& b) const { return point(x + b.x, y + b.y); }
    point operator-(const point& b) const { return point(x - b.x, y - b.y); }
    point operator-() const { return point(-x, -y); }
    T operator*(const point& b) const { return x * b.x + y * b.y; }
    T operator^(const point& b) const { return x * b.y - y * b.x; }
    T operator==(const point& b) const { return x == b.x && y == b.y; }
    T operator!() const { return x * x + y * y; }
    bool operator<(const point& b) const { return x == b.x ? y < b.y : x < b.x; }
};
pointtt istream&operator>>(istream&is,point<T>&a){return is>>a.x>>a.y;}
pointtt ostream&operator<<(ostream&os,point<T>&a){return os<<a.x<<" "<<a.y;}
pointtt T dist(const point<T>&a,const point<T>&b){return!point<T>(a-b);}
//dist from point C to line AB equals to answer.first / sqrt(answer.second);
pointtt pair<T,T> dist(const point<T>&a,const point<T>&b,const point<T>&c){return{abs((a-b)*c)+(a^b),dist(a,b)};}
static const int CW = 1;
static const int CCW = -1;
pointtt int orientation(const point<T>&a,const point<T>&b,const point<T>&c){T q=a.x*b.y-a.y*b.x-a.x*c.y+a.y*c.x+b.x*c.y-b.y*c.x;return q>0?CCW:q<0?CW:0;}

//}}}

void run()
{
    ints(n);
    if (n <= 2) return writeln("Yes");
    vector<point<ll>> a;
    fori(n)
    {
        ints(t);
        if (t == 0)
        {
            ints(r, x, y);
            a.emplace_back(x * 2, y * 2);
        }
        else
        {
            ints(x1, y1, x2, y2, x3, y3, x4, y4);
            int mnx = min({x1, x2, x3, x4});
            int mny = min({y1, y2, y3, y4});
            int mxx = max({x1, x2, x3, x4});
            int mxy = max({y1, y2, y3, y4});
            a.emplace_back(mnx + mxx, mny + mxy);
        }
    }
    int k = 0;
    int j = 1;
    while (j < n && a[k] == a[j]) ++j;
    if (j == n) return writeln("Yes");
    fori(n)
        if (orientation(a[i], a[j], a[k]) != 0)
            return writeln("No");
    writeln("Yes");
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
