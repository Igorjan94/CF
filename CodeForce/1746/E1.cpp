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
//}}}

void run()
{
    ints(n);
    vi a(n);
    iota(all(a), 1);

    auto ask = [&](vector<int>& x) {
        writeln("?", x.size(), x);
        string s;
        readln(s);
        return s == "YES";
    };

    vector<int> x[4], nxt;

    auto makeNext = [&](int i, int j = -1, int k = -1) {
        nxt.clear();
        copy(all(x[i]), back_inserter(nxt));
        if (j != -1)
            copy(all(x[j]), back_inserter(nxt));
        if (k != -1)
            copy(all(x[k]), back_inserter(nxt));
    };

    auto dump = [&]() {
        fori(4) x[i].clear();
    };

    while (a.size() > 3)
    {
        dump();
        int q = a.size() / 4;
        int m1 = q;
        int m2 = q * 2;
        int m3 = q * 3;

        copy(a.begin(), a.begin() + m1, back_inserter(x[0]));
        copy(a.begin() + m1, a.begin() + m2, back_inserter(x[1]));
        copy(a.begin() + m2, a.begin() + m3, back_inserter(x[2]));
        copy(a.begin() + m3, a.end(), back_inserter(x[3]));
        makeNext(0, 1);
        int a0 = ask(nxt);
        makeNext(0, 2);
        int a1 = ask(nxt);
        if (a0 && a1)
            makeNext(0, 1, 2);
        else if (!a0 && !a1)
            makeNext(1, 2, 3);
        else if (a0 && !a1)
            makeNext(0, 1, 3);
        else
            makeNext(0, 2, 3);
        a = nxt;
    }
        
    if (a.size() == 3)
    {
        dump();
        int m1 = a.size() / 3;
        int m2 = a.size() - m1;
        copy(a.begin(), a.begin() + m1, back_inserter(x[0]));
        copy(a.begin() + m1, a.begin() + m2, back_inserter(x[1]));
        copy(a.begin() + m2, a.end(), back_inserter(x[2]));
        bool a0 = ask(x[0]);
        bool a1 = ask(x[1]);
        bool a2 = ask(x[1]);
        bool a3 = ask(x[0]);

        if (a1 == a2)
        {
            if (a1)
                makeNext(1);
            else
                makeNext(0, 2);
        }
        else if ((a0 && a1) || (a2 && a3))
        {
            makeNext(0, 1);
        }
        else if ((a0 && !a1) || (!a2 && a3))
            makeNext(0, 2);
        else
            makeNext(1, 2);
        a = nxt;
    }
    writeln("!", a[0]);
    string s; readln(s);
    if (s == ":(")
    {
        writeln("!", a[1]);
        readln(s);
    }
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
