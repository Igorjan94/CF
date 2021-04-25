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

void run(int n, int b)
{
    vector<vector<int>> a(n);
    forn(q, n * b)
    {
        ints(d);
        int ans = -1;
        if (d == 9 || d == 8 && q + b >= n * b || d == 7 && q + 5 >= n * b)
        {
            fori(n)
                if (ans == -1 && SZ(a[i]) == b - 1)
                    ans = i;
            fori(n)
                if (ans == -1 && SZ(a[i]) == b - 2)
                    ans = i;
            fori(n)
                if (ans == -1 && SZ(a[i]) < b - 2)
                    ans = i;
        }
        else
        {
            if (d == 8 || d == 7)
            {
                int mx = -1;
                fori(n)
                    if (SZ(a[i]) < b - 1 && mx < SZ(a[i]))
                        ans = i, mx = SZ(a[i]);
            }
            else
            {
                fori(n)
                    if (ans == -1 && SZ(a[i]) < b - 2)
                        ans = i;
            }
            fori(n)
                if (ans == -1 && SZ(a[i]) < b)
                    ans = i;
        }
        a[ans].pb(d);
        writeln(ans + 1); cout.flush();
    }
    fori(n)
    {
        forj(b)
            cerr << " " << a[i][j];
        cerr << endl;
    }
    cerr << endl;
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    int t, n, b;
    ll p;
    readln(t, n, b, p);
    fori(t) run(n, b);
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
