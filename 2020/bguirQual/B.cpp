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
    string S;
    readln(S);
    int n = S.size();
    vector<int> d(10);
    for (char c: S)
        d[c - 48]++;
    if (d[0] == n)
        if (n == 2)
            return writeln(0, 0);
        else
            return writeln(-1, -1);
    string f;
    auto check = [&](vector<int> d) {
        string s;
        fori1(10)
            while (d[i] && s.size() < 18)
            {
                s += '0' + i;
                d[i]--;
                while (d[0] && (s.size() < 18 || s.size() == 18 && i == 1))
                    s += '0',
                    d[0]--;
            }
        if (accumulate(all(d), 0) == 0)
        {
            if (f.size() > s.size() || f.size() == s.size() && f > s) swap(f, s);
            writeln(f, s);
            exit(0);
        }
    };
    if (d[0])
    {
        d[0]--;
        f = "0";
        check(d);
        f = "";
        d[0]++;
    }
    if (d[1] && d[0] >= 18)
    {
        d[1]--;
        d[0] -= 18;
        f = "1" + string(18, '0');
        check(d);
        d[0] += 18;
        d[1]++;

    }
    fori1(10)
        while (d[i] && f.size() < 18)
        {
            f += '0' + i;
            d[i]--;
            check(d);
            while (d[0] && f.size() < 18 || f.size() == 18 && i == 1)
                f += '0',
                d[0]--,
                check(d);
        }
    writeln(-1, -1);
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
