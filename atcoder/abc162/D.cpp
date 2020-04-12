// Igorjan94, template version from 13 October 2017. C++17 version, modified 18 march 2020 (writeln<tuple>, whole->all) {{{
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include <iomanip>

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

//Igorjan
//}}}

void run()
{
    int n;
    string s;
    cin >> n >> s;
    vector<vector<int>> has(n + 1, {0, 0, 0});
    map<char, int> m = {{'R', 0}, {'G', 1}, {'B', 2}};
    ROF(i, n - 1, 0)
        has[i] = has[i + 1],
        has[i][m[s[i]]]++;
    ll ans = 0;
    fori(n)
        FOR(j, i + 1, n)
        if (s[i] != s[j])
        {
            ans += has[j][0] + has[j][1] + has[j][2] - has[j][m[s[i]]] - has[j][m[s[j]]];
            if (int k = j + (j - i); k < n && s[k] != s[i] && s[k] != s[j])
                ans--;
        }

    cout << ans << "\n";
}

//{{{
int main()
{
    ios_base::sync_with_stdio(false);
    run();
    cerr << fixed << setprecision(0) << "Execution time = " << 1000.0 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
