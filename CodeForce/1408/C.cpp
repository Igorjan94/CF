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
//}}}

void run()
{
    ints(n, l);
    vi a(n);
    readln(a);
    a.insert(a.begin(), 0);
    a.push_back(l);
    n += 2;
    cout << fixed << setprecision(10);
    auto get = [&](const vector<int>& a) {
        vector<pair<double, double>> c(n);
        double s = 0;
        fori(n)
        {
            c[i] = pair(s, (i == 0 ? 0 : c[i - 1].second) + (i == 0 ? 0 : abs(a[i - 1] - a[i]) / s));
            s += 1;
        }
        return c;
    };
    auto c = get(a);
    reverse(all(a));
    auto d = get(a);
    reverse(all(d));
    reverse(all(a));
    //fori(n)
        //writeln(a[i], c[i].second, d[i].second);
    fori(n)
        if (c[i].second >= d[i].second)
        {
            double s1 = c[i - 1].first + 1;
            double t1 = c[i - 1].second;
            double x1 = a[i - 1];
            double s2 = d[i].first + 1;
            double t2 = d[i].second;
            double x2 = a[i];
            //writeln(x1, s1, t1);
            //writeln(x2, s2, t2);
            double dt = t2 - t1;
            double s = s1 + s2;
            double num = dt * s1 * s2 + s2 * x1 + s1 * x2;
            double x = num / s;
            double ans = t1 + (x - x1) / s1;
            writeln(ans);
            return;
        }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t); fori(t) run();
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
