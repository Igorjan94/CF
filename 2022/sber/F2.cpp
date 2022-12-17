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
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}
vector<int> getResult(vector<int> s)
{
    int n = s.size();
    vector<int> p(n);
    iota(all(p), 0);
    auto get = [&](int x, int y, int sx, int sy) -> pair<vector<int>, int> {
        if (sx < sy)
            return {{y}, sy - sx};
        if (sx > sy)
            return {{x}, sx - sy};
        return {{x}, 0};
    };
    vector<int> ans(4);
    int vars = 0;
    do
    {
        int a = p[0];
        int b = p[1];
        int c = p[2];
        int d = p[3];
        auto [es, se] = get(a, b, s[a], s[b]);
        auto [fs, sf] = get(c, d, s[c], s[d]);
        for (int e: es)
            for (int f: fs)
            {
                auto [ws, _] = get(e, f, se, sf);
                for (int w: ws)
                    ans[w]++,
                    vars++;
            }
    }
    while (next_permutation(all(p)));
    for (int& x: ans)
        x = round(((x * 1.0) / vars) * 100);
    return ans;
}

//{{{
//int main()
//{
    //ios_base::sync_with_stdio(false);
    //vector<string> s(2);
    //writeln(getResult({3, 11}, {5, 1}));
    //cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    //return 0;
//}

#define a _a
#define n _n
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a);
template<typename T,typename D=decltype(*begin(declval<T>())),typename enable_if<!is_same<T,basic_string<char>>::value>::type* =nullptr>
ostream&operator<<(ostream&os,T const&a){auto it=begin(a);if(it!=end(a))os<<*it++;while(it!=end(a))os<<"\n "<<*it++;return os;}
ttt12i ostream&operator<<(ostream&os,pair<T1,T2>const&a){return os<<a.first<<" "<<a.second;}
ttt12i istream&operator>>(istream&is,pair<T1,T2>&a){return is>>a.first>>a.second;}
ttti   istream&operator>>(istream&is,vector<T>&a){fori(a.size())is>>a[i];return is;}
ttti void print(T&&a){cout<<" "<<a;}
ttti void priws(T&&a){cout<<a;}
ttti void read(T&a){cin>>a;} //}}}
