// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <bits/stdc++.h>
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

ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"  "[is_fundamental<typename T::value_type>::value]<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} 
//Igorjan
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

double ms() {
    return 1000.0 * clock() / CLOCKS_PER_SEC;
}

struct polymino
{
    int d;
    vector<pii> a;
    int left = 1;
    polymino() {}

    bool operator<(const polymino& o) const {
        return tie(d, a) < tie(o.d, o.a);
    }
};

istream& operator>>(istream& is, polymino& p) {
    is >> p.d;
    p.a.resize(p.d);
    return is >> p.a;
}

int ask(const vector<pii>& x) {
    writeln("q", x.size(), x);
    for (auto& p: x)
        writeln("#c", p, "red");
    cout.flush();
    int v;
    readln(v);
    return v;
}

int answer(const vector<pii>& x) {
    writeln("a", x.size(), x);
    cout.flush();
    int v;
    readln(v);
    return v;
}

void run()
{
    double start = ms();
    ints(n, m);
    double eps;
    vector<polymino> a(m);
    readln(eps, a);
    sort(all(a));
    reverse(all(a));
    vector<polymino> b(1, a[0]);
    fori1(m)
        if (a[i].a == b.back().a)
            ++b.back().left;
        else
            b.pb(a[i]);
    a = b;
    m = a.size();
    for (auto& p: a)
        if (auto& [x, y] = p.a[0]; x || y)
        {
            fori1(p.d)
                p.a[i].first -= x,
                p.a[i].second -= y;
            x = 0;
            y = 0;
        }
    vector field(n, vector(n, -1));
    vector stillAlive(n, vector(n, false));

    auto dump = [&](polymino& p, int i, int j) {
        for (auto& [x, y]: p.a)
        {
            int I = i + x;
            int J = j + y;
            if (field[I][J] == -1)
                field[I][J] = 1;
        }
        --p.left;
    };
    auto possible = [&](const polymino& p) {
        vector<pii> starts;
        fori(n)
            forj(n)
            {
                bool can = true;
                for (auto& [x, y]: p.a)
                {
                    int I = i + x;
                    int J = j + y;
                    can &= I >= 0 && J >= 0 && I < n && J < n && field[I][J] != 0;
                    if (!can)
                        break;
                }
                if (can)
                {
                    starts.pb({i, j});
                    for (auto& [x, y]: p.a)
                    {
                        int I = i + x;
                        int J = j + y;
                        stillAlive[I][J] = true;
                    }
                }
            }
        return starts;
    };

    forn(Q, n * n)
    {
        int left = 0;
        for (auto& p: a) left += p.left;
        if (left == 0)
            break;
        vector<pii> pp;
        fori(n)
            forj(n)
                if (field[i][j] == -1)
                    pp.pb({i, j});
        if (pp.size() == 0)
            break;
        
        auto [x, y] = pp[rng() % pp.size()];
        auto calcRes = [&](bool recolor = false) {
            if (recolor) {
                fori(n)
                    forj(n)
                        stillAlive[i][j] = false;
            }
            int ss = 0;
            for (auto& p: a) if (p.left)
                ss += possible(p).size();
            if (recolor)
                fori(n)
                    forj(n)
                        if (field[i][j] == -1) 
                            if (!stillAlive[i][j])
                                writeln("#c", i, j, "black"),
                                field[i][j] = 0;
            return ss;
        };
        if (ms() - start < 2500) {
            int mx = calcRes(true);
            if (m < 5) for (auto& [i, j]: pp) if (field[i][j] == -1) {
                field[i][j] = 0;
                int cur = calcRes();
                if (cur < mx || (cur == mx && rng() % 2 == 0))
                    mx = cur,
                    tie(x, y) = pair(i, j);
                field[i][j] = -1;
            }
        } else {
            writeln("# FAIL");
        }
        field[x][y] = ask({{x, y}});
        for (auto& p: a) if (p.left)
        {
            auto starts = possible(p);
            if (starts.size() == p.left)
                for (auto& [i, j]: starts)
                    dump(p, i, j);
        }
    }

    vector<pii> ans;
    fori(n)
        forj(n)
            if (field[i][j] > 0)
                ans.pb({i, j});
    int xxx = answer(ans);
    exit(xxx);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << ms() << "ms\n";
    return 0;
}
//}}}
