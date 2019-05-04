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

char ask(int x)
{
    cout << x + 1 << endl;
    char c;
    cin >> c;
    return c;
}

void run()
{
    string ans;
    vector<int> positions(119);
    iota(whole(positions), 0);
    set<char> was;
    forn(q, 4)
    {
        map<char, vector<int>> m;
        for (int x: positions)
            m[ask(x * 5 + q)].pb(x);
        int mn = MOD;
        char add;
        for (auto& x: m)
            if (x.second.size() < mn)
                mn = x.second.size(),
                add = x.first;
        positions = m[add];
        ans += add;
        was.insert(add);
    }
    string temp = "ABCDE";
    for (char c: temp)
        if (was.find(c) == was.end())
            ans += c;
    swap(ans[3], ans[4]);
    cout << ans << endl;
    char c;
    cin >> c;
    if (c == 'N') exit(1);
}

int main()
{
#ifndef ONLINE_JUDGE
    double time = clock();
#endif
    ios_base::sync_with_stdio(false);
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    int t, f;
    cin >> t >> f;
    fori(t)
        run();
#ifndef ONLINE_JUDGE
    //writeln("execution time =", (clock() - time) / CLOCKS_PER_SEC);
#endif
    return 0;
}
