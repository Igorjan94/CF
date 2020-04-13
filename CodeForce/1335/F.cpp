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
    ints(n, m);
    vector<string> colors(n);
    vector<string> field(n);
    readln(colors, field);

    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    map<char, int> directions = {
        {'L', 2},
        {'R', 3},
        {'D', 1},
        {'U', 0}
    };
    int cur = 0;
    int black = 0;
    int ans = 0;
    vector<vector<int>> used(n, vector<int>(m, -1));
    fori(n)
        forj(m)
            if (used[i][j] == -1)
            {
                bool found = false;
                pii cycle;
                int u = i;
                int v = j;
                do {
                    used[u][v] = cur;
                    int d = directions[field[u][v]];
                    u += dx[d];
                    v += dy[d];
                } while (used[u][v] != cur);
                cur++;
                int maxLength = 0;
                do {
                    used[u][v] = cur;
                    int d = directions[field[u][v]];
                    u += dx[d];
                    v += dy[d];
                    maxLength++;
                } while (used[u][v] != cur);
                cur++;
                vector<vector<pii>> levels(maxLength);
                function<void(int, int, int)> dfs = [&](int i, int j, int d) {
                    used[i][j] = cur;
                    levels[d % maxLength].pb({i, j});
                    for (int k = 0; k < 4; ++k)
                    {
                        int u = i + dx[k];
                        int v = j + dy[k];
                        if (u < 0 || u >= n || j < 0 || j >= m)
                            continue;
                        if (u + dx[directions[field[u][v]]] != i || v + dy[directions[field[u][v]]] != j)
                            continue;
                        if (used[u][v] == cur)
                        {
                            maxLength = d + 1;
                            continue;
                        }
                        dfs(u, v, d + 1);
                    }
                };
                dfs(u, v, 0);
                for (auto& layer: levels)
                {
                    ans++;
                    bool found = false;
                    for (auto& [i, j]: layer)
                        if (colors[i][j] == '0')
                        {
                            black++;
                            found = true;
                            break;
                        }
                }
                cur++;
            }
    writeln(ans, black);
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
