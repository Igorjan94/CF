// Igorjan94, template version from 13 October 2017. C++17 version, modified 07 August 2018 (&&, whole) {{{
#include <bits/stdc++.h>

using namespace std;

#define FILENAME "input"

#define FOR(i, m, n) for (int i = m; i <  (int) (n); ++i)
#define ROF(i, m, n) for (int i = m; i >= (int) (n); --i)
#define forn(i, n)   for (int i = 0; i < (int) (n); ++i)
#define  fori1(n)    for (int i = 1; i < (int) (n); ++i)
#define  forj1(n)    for (int j = 1; j < (int) (n); ++j)
#define   fori(n)    for (int i = 0; i < (int) (n); ++i)
#define   forj(n)    for (int j = 0; j < (int) (n); ++j)
#define     SZ(a)    int(a.size())

typedef  pair<int, int>   pii;
typedef  valarray<int>    va;
typedef   vector<int>     vi;
typedef    long long      ll;

#define    pb    push_back
#define whole(a) begin(a), end(a)
#define   next   next__
#define   prev   prev__
#define  count   count__

#define wr(args...) err(#args, args)

#define ttt12i template<class T1, class T2> inline
#define  tthti template<class H, class...T> inline
#define  ttta  template<class... Args> inline
#define  ttti  template<class T> inline

const int MOD = 1000000007;
const int INTMAX = numeric_limits<int>::max();
const ll LLMAX = numeric_limits<ll>::max();

//Igorjan
//}}}

string run()
{
    int n;
    cin >> n;
    vector<string> a(n);
    fori(n)
        cin >> a[i];
    string ans;
    for (int i = 0; i < 500 * 500 && a.size(); ++i)
    {
        set<char> cur;
        for (auto& j : a)
            cur.insert(j[i % j.size()]);
        if (cur.size() == 3)
            return "IMPOSSIBLE";
        if (cur.size() == 1)
        {
            char c = *cur.begin();
            if (c == 'R')
                ans += 'P';
            else if (c == 'P')
                ans += 'S';
            else if (c == 'S')
                ans += 'R';
            return ans;
        }
        if (cur.size() == 2)
        {
            char c = *cur.begin();
            char d = *cur.rbegin();
            char b = '?';
            if (c > d) c = d;
            if (c == 'P' && d == 'R')
                b = 'P';
            else if (c == 'P' && d == 'S')
                b = 'S';
            else if (c == 'R' && d == 'S')
                b = 'R';
            ans += b;
            for (int j = SZ(a) - 1; j >= 0; --j)
                if (a[j][i % a[j].size()] != b)
                    a.erase(a.begin() + j);
        }
    }
    if (a.size())
        return "IMPOSSIBLE";
    else
        return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    int t;
    cin >> t;
    fori(t)
        cout << "Case #" << (i + 1) << ": " << run() << "\n";
#ifndef ONLINE_JUDGE
    //writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}
