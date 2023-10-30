// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
#include <ostream>
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct point 
{
    double x, y, z, d;
    point() {}
};

ostream& operator<<(ostream& os, const point& p) {
    return os << p.x << " " << p.y << " " << p.z;
}

istream& operator>>(istream& is, point& p) {
    return is >> p.x >> p.y >> p.z >> p.d;
}
double sqr(double x) { return x * x; }

void run()
{
    ints(n);
    vector<point> a(n);
    readln(a);
    shuffle(all(a), rng);
    a.resize(min(n, 10));
    auto get = [&](double x0, double y0, double z0) {
        double ans = 0;
        for (auto& [x, y, z, d]: a)
            ans += fabs(sqrt(sqr(x - x0) + sqr(y - y0) + sqr(z - z0)) - d);
        return ans;
    };
    double eps = 0.002;
    double x0, y0, z0;
    double ans = numeric_limits<double>::max();
    for (double phi = 0.0; phi <= 2 * 3.1415926; phi += eps)
        for (double theta = 0.0; theta <= 3.1415926; theta += eps)
        {
            double x = a[0].x + a[0].d * sin(phi) * cos(theta);
            double y = a[0].y + a[0].d * sin(phi) * sin(theta);
            double z = a[0].z + a[0].d * cos(phi);
            auto cur = get(x, y, z);
            if (cur < ans)
                ans = cur,
                x0 = x,
                y0 = y,
                z0 = z;
        }

    writeln(x0, y0, z0);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(9);
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
