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
    double time = clock();
    string t;
    readln(t);
    string s = "A";
    fori1(26)
        s = s + char(i + 65) + s;
    int l = s.size();
    int d = t.size();
    string ans(26, 'a');
    vector<int> hasAns(26, -1);
    vector<int> used(26, -1);
    vector<int> p(d);
    iota(all(p), 0);
    random_shuffle(all(p));
    fori(l - d)
    {
        if (i % 1000 == 0 && (clock() - time) / CLOCKS_PER_SEC > 0.9) break;
        bool ok = true;
        forn(q, d)
        {
            int j = p[q];
            int ii = s[i + j] - 65;
            int jj = t[j] - 65;
            if (hasAns[ii] < i)
            {
                if (used[jj] == i)
                    ok = false;
                used[jj] = i;
                hasAns[ii] = i;
                ans[ii] = t[j];
            }
            ok &= ans[ii] == t[j];
            if (!ok) break;
        }
        if (ok)
        {
            forn(q, 26)
                if (hasAns[q] < i)
                    forj(26)
                        if (used[j] < i) {
                            ans[q] = j + 65;
                            used[j] = i;
                            break;
                        }
            writeln(ans);
            writeln(i + 1);
            return;
        }
    }

    writeln("No solution");
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
