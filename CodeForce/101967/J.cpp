// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (short i = m; i <  (short) (n); ++i)
#define ROF(i, m, n) for (short i = m; i >= (short) (n); --i)
#define forn(i, n)   for (short i = 0; i < (short) (n); ++i)
#define  fori1(n)    for (short i = 1; i < (short) (n); ++i)
#define  forj1(n)    for (short j = 1; j < (short) (n); ++j)
#define   fori(n)    for (short i = 0; i < (short) (n); ++i)
#define   forj(n)    for (short j = 0; j < (short) (n); ++j)

typedef vector<long long> vll;
typedef  pair<short, short>   pii;
typedef  valarray<short>    va;
typedef   vector<short>     vi;
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

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();

void writeln(){cout<<"\n";}ttti void print(T&& a);ttti void priws(T&& a);ttti void read(T& a);
ttta void readln(Args&... args){(read(args),...);}tthti void writeln(H&& h,T&&...t){priws(h);(print(t),...);writeln();}
ttti void writeln_range(T f,T s){if(f!=s)for(auto i=f;i!=s;++i)writeln(*i);}
vector<string>split(string&s,string d){vector<string> v;size_t p=0;while((p=s.find(d))!=string::npos)v.pb(s.substr(0,p)),s.erase(0,p+d.length());v.pb(s);return v;}
ttta void err(string v,Args...args){auto vv=split(v,", ");auto it=vv.begin();(writeln(*it++,"=",args),...);}

//Igorjan
//}}}

#ifdef ONLINE_JUDGE
static const short N = 2004;
#else
static const short N = 14;
#endif
pii field[N][N];
#define x first
#define y second
vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};

void dump()
{
    return;
    fori(N)
        forj(N)
        {
            if (field[i][j].x == -1)
                printf(".");
            else if (field[i][j].x == -2)
                printf("*");
            else if (field[i][j].x > i)
                printf("V");
            else if (field[i][j].x < i)
                printf("^");
            else if (field[i][j].y > j)
                printf(">");
            else if (field[i][j].y < j)
                printf("<");
            if (j == N - 1)
                printf("\n");
        }
    printf("\n");
}

void run()
{
    fori(N) forj(N) field[i][j] = {-2, -2};
    ints(n);
    pii s;
    forn(q, n)
    {
        short x, y;
        readln(x, y); s = {x, y};
        fori(2) forj(2) field[2 * x + i][2 * y + j] = {-1, -1};
    }
    dump();

    auto dumpCycle = [&](int i, int j) {
        i *= 2; j *= 2;
        field[i][j]         = {i, j + 1};
        field[i][j + 1]     = {i + 1, j + 1};
        field[i + 1][j + 1] = {i + 1, j};
        field[i + 1][j]     = {i, j};
    };

    function<void(short, short)> dfs = [&](int i, int j) {
        forn(q, 4)
        {
            int u = i + dx[q];
            int v = j + dy[q];
            if (u < 0 || v < 0 || field[u * 2][v * 2].x != -1) continue;
            dumpCycle(u, v);
            dump();
            int a = i * 2, b = j * 2;
            if (dy[q] == 1)
                field[a][b + 1] = {a, b + 2},
                field[a + 1][b + 2] = {a + 1, b + 1};
            if (dy[q] == -1)
                field[a][b - 1] = {a, b},
                field[a + 1][b] = {a + 1, b - 1};
            if (dx[q] == 1)
                field[a + 1][b + 1] = {a + 2, b + 1},
                field[a + 2][b] = {a + 1, b};
            if (dx[q] == -1)
                field[a][b] = {a - 1, b},
                field[a - 1][b + 1] = {a, b + 1};
            dump();
            dfs(u, v);
        }
    };

    dumpCycle(s.x, s.y);
    dfs(s.x, s.y);

    s.x *= 2; s.y *= 2;
    auto [i, j] = s;
    writeln(s);
    while (field[i][j] != s)
        writeln(field[i][j]),
        //ans.pb(field[i][j]),
        tie(i, j) = field[i][j];
    //writeln(ans);
    dump();
}

//{{{
int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
#ifndef ONLINE_JUDGE
    writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}

#define a _a
#define n _n
ttti   ostream&operator<<(ostream&os,vector<T>&a);
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>&a){return os<<a.first<<" "<<a.second;}
ttti   ostream&operator<<(ostream&os,vector<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   ostream&operator<<(ostream&os,valarray<T>&a){if(a.size())os<<a[0];else os<<"\n";fori1(a.size())os<<"\n "[is_fundamental<T>::value]<<a[i];return os;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti   istream&operator>>(istream&is,valarray<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&& a){cout<<" "<<a;}
ttti void priws(T&& a){cout<<a;}
ttti void read(T& a){cin>>a;} //}}}
