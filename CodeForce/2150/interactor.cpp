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

//Igorjan
//rng
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//}}}

int mx = 0;
int n = 300;
int t = 2000;

void run()
{
    writeln(n);
    cout.flush();
    vector<int> a(2 * n);
    iota(all(a), 1);
    for (int& x: a)
        x = (x % n) + 1;
    shuffle(all(a), rng);
    a.pop_back();
    //cerr << "n = " << n << endl;
    int q = 0;
    while (true) {
        char c;
        int x;
        int l;
        readln(c, x);
        if (c == '?') {
            ++q;
            readln(l);
            vector<int> b(l);
            readln(b);
            bool has = false;
            for (int index: b)
                has |= a[index - 1] == x;
            writeln(has ? 1 : 0);
            cout.flush();
        } else {
            int cnt = count(all(a), x);
            if (cnt == 1) {
                cerr << "Requests: " << q << endl;
                mx = max(mx, q);
            } else {
                cerr << x << endl;
                for (int x : a)
                    cerr << x << " ";
                exit(1);
            }
            break;
        }
    }
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    writeln(t);
    fori(t) run();
    cerr << "Max requests: " << mx << " / " << n * 4 + 2 * floor(log2(n)) << endl;
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
