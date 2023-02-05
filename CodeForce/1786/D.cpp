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

vector<tuple<string, string, string, string, char, char>> swaps;

void run()
{
    ints(n);
    vector<string> s(n);
    readln(s);
    map<string, set<int>> m;
    fori(n)
        sort(all(s[i])),
        m[s[i]].insert(i);

    auto del = [&](string i, int j) {
        m[i].erase(j);
        if (m[i].empty())
            m.erase(i);
    };
    vector<pair<pair<int, char>, pair<int, char>>> ans;
    while (SZ(m) > 1)
    {
        for (auto& [f, t, nf, nt, c, d]: swaps)
            if (m.contains(f) && m.contains(t))
            {
                int i = *m[f].begin();
                int j = *m[t].begin();
                del(f, i);
                del(t, j);

                m[nf].insert(i);
                m[nt].insert(j);
                ans.pb({{i + 1, c}, {j + 1, d}});
                break;
            }
    }

    writeln(ans.size());
    if (ans.size())
        writeln(ans);
}

//{{{
int main()
{
    set<tuple<string, string, string, string, char, char>> swapsGood, swapsBad;
    set<string> strings;
    fori(3)
        forj(3)
            forn(k, 3)
            {
                string t;
                t.pb("win"[i]);
                t.pb("win"[j]);
                t.pb("win"[k]);
                sort(all(t));
                strings.insert(t);
            }

    auto get = [&](const string& s) {
        set<char> ans(all(s));
        return ans.size();
    };

    for (string f: strings)
        for (string t: strings)
        {
            int wf = get(f);
            int wt = get(t);
            fori(3)
                forj(3)
                    if (f[i] != t[j])
                    {
                        string nf(f);
                        string nt(t);
                        nf[i] = t[j];
                        nt[j] = f[i];
                        sort(all(nf));
                        sort(all(nt));
                        int qf = get(nf);
                        int qt = get(nt);
                        if (wf == qf && wt == qt)
                            continue;
                        if (wf > qf || wt > qt)
                            continue;
                        if (f == nt && t == nf)
                            continue;
                        if (wf < qf && wt < qt)
                            swapsGood.insert({f, t, nf, nt, f[i], t[j]});
                        else if (wf < qf || wt < qt)
                            swapsBad.insert({f, t, nf, nt, f[i], t[j]});
                    }
        }
    for (auto& x: swapsGood)
        swaps.pb(x);
    for (auto& x: swapsBad)
        swaps.pb(x);

    ios_base::sync_with_stdio(false); cin.tie(0);
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
