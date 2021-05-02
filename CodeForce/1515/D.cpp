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
    ints(n, l, r);
    vi a(n);
    readln(a);
    if (l > r)
        swap(l, r),
        reverse(all(a));
    //[LEFT           || RIGHT                      ]
    //[c1, c2, c3, c4 || c5, c6, c7, c8, c9, ..., cn]
    //[1, 1 || 2, 2]
    map<int, int> left;
    map<int, int> right;
    fori(n)
        if (i < l)
            left[a[i]]++;
        else
            right[a[i]]++;
    int ans = 0;
    int oddLeft = 0;
    int oddRight = 0;
    int canLeft = 0;
    int canRight = 0;
    for (auto& [color, count]: right)
    {
        int eq = min(left[color], count);
        count -= eq;
        left[color] -= eq; //No action
        canRight += count / 2; //Change parity
        oddRight += count;
    }
    for (auto& [color, count]: left)
    {
        canLeft += count / 2; //Change parity
        oddLeft += count;
    }
    //odd == change color and parity
    int odd = min(oddLeft, oddRight);
    oddLeft -= odd;
    oddRight -= odd;
    oddLeft = clamp(oddLeft - canLeft, oddLeft / 2, oddLeft);
    oddRight = clamp(oddRight - canRight, oddRight / 2, oddRight);
    writeln(ans + odd + oddLeft + oddRight);
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
