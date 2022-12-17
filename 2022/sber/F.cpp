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
int getResult(vector<int> a, vector<int> s)
{
    int n = a.size();
    vector<pair<int, int>> x;
    fori(n)
        x.pb({a[i], s[i]});
    auto get = [&](vector<pair<int, int>> x) {
        int time = numeric_limits<int>::max();
        pii ans = {-1, -1};
        fori(x.size())
            FOR(j, i + 1, x.size())
                if (x[i].first == x[j].first)
                    return pair(0, pair(i, j));
                else if (x[i].second > x[j].second)
                {
                    int dx = (x[j].first - x[i].first);
                    int dy = (x[i].second - x[j].second);
                    if (dx % dy == 0)
                    if (int cur = dx / dy; cur < time)
                        time = cur,
                        ans = {i, j};
                }
        return pair(time, ans);
    };
    while (true)
    {
        sort(all(x));
        auto [time, ans] = get(x);
        if (ans.first == -1) break;
        auto [i, j] = ans;
        forn(k, x.size())
            x[k].first += time * x[k].second;
        x[i].second += x[j].second;
        x.erase(x.begin() + j);
    }
    return x.size();
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
