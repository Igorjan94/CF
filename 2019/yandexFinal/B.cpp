// Igorjan94, template version from 13 October 2017. C++17 version, modified 14 september 2019 (writeln<T>, main) {{{
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

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define ints(a...)  int a; readln(a)
#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int INF = 1000000007;
const int INTMAX = numeric_limits<int>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
vector<string>split(string&s,string d){vector<string>v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//hungarian
pair<int, vector<int>> hungarian(vector<vector<int>> const& a)
{
    int n = a.size() + 1;
    int m = a[0].size() + 1;
    vector<int> u(n), v(m), p(m), way(m);
    fori1(n)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m, INF);
        vector<bool> used(m, false);
        do 
        {
            used[j0] = true;
            int i0 = p[j0];
            int delta = INF;
            int j1;
            forj1(m)
                if (!used[j]) 
                {
                    int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,
                        way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],
                        j1 = j;
                }
            forj(m)
                if (used[j])
                    u[p[j]] += delta,
                    v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } 
        while (p[j0] != 0);
        do 
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } 
        while (j0);
    }
    vector<int> ans(n + 1);
    forj1(m)
        ans[p[j] - 1] = j - 1;
    return {-v[0], ans};
}

//}}}



void run()
{
    ints(n);
    vector<tuple<int, int, int>> a(n), b(n);
    fori(n)
    {
        ints(x, y, c);
        a[i] = {x, y, c};
    }
    fori(n)
    {
        ints(x, y, c);
        b[i] = {x, y, c};
    }
    auto get = [&](int i, int j) {
        auto [x1, y1, b1] = a[i];
        auto [x2, y2, b2] = b[j];
        return abs(x2 - x1) + abs(y2 - y1) + abs(b2 - b1);
    };
    vector<vector<int>> m(n, vector<int>(n));
    fori(n) forj(n) m[i][j] = get(i, j);
    auto [price, _] = hungarian(m);
    writeln(price);
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
