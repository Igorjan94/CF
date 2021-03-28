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

int ask(int x, int y, int z)
{
    writeln(x + 1, y + 1, z + 1);
    cout.flush();
    ints(ans);
    return ans - 1;
}

void run(int n)
{
    vector<int> a(n);
    iota(all(a), 0);
    random_shuffle(all(a));
    function<vector<int>(int, vector<int>&, int)> f = [&](int l, vector<int>& a, int r) -> vector<int> {
        int m = SZ(a);
        if (m <= 1) return a;

        int x = a[0];
        int y = a[1];
        vector<int> left, middle, right;
        for (int i = 2; i < m; ++i)
        {
            int mid = ask(x, y, a[i]);
            if (mid == a[i])
                middle.pb(a[i]);
            else if (mid == x)
                left.pb(a[i]);
            else
                right.pb(a[i]);
        }
        
        if (l != -1)
        {
            int temp = ask(l, x, y);
            if (temp == y)
                swap(x, y),
                swap(left, right);
        } else if (r != -1)
        {
            int temp = ask(r, x, y);
            if (temp == x)
                swap(x, y),
                swap(left, right);
        }
        
        vector<int> L = f(l, left, x);
        vector<int> M = f(x, middle, y);
        vector<int> R = f(y, right, r);
        vector<int> b;
        for (int& z: L) b.pb(z);
        b.pb(x);
        for (int& z: M) b.pb(z);
        b.pb(y);
        for (int& z: R) b.pb(z);
        return b;
    };
    vector<int> temp = f(-1, a, -1);
    for (int& z: temp) ++z;
    writeln(temp);
    cout.flush();
    ints(ans);
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    ints(t, n, q);
    fori(t) run(n);
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
