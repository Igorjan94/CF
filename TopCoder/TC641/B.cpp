//template igorjan94 version from 05 December 2014
#include <bits/stdc++.h>

#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define FOR(i, m, n) for (int i = m; i <  n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define forn1(i, n)  for (int i = 1; i < n; ++i)
#define forn(i, n)   for (int i = 0; i < n; ++i)
#define  fori1(n)    for (int i = 1; i < n; ++i)
#define  forj1(n)    for (int j = 1; j < n; ++j)
#define   fori(n)    for (int i = 0; i < n; ++i)
#define   forj(n)    for (int j = 0; j < n; ++j)

#define     fst      first
#define     snd      second
#define      pb      push_back
#define      ll      long long
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int> >
#define     pll      pair<long long, long long>
#define   whole(a)   a.begin(), a.end()

using namespace std;

#define method      int count(vector <int> x, vector <int> y)

#define classname   TrianglesContainOriginEasy

int ori(pii& a, pii& b, pii& c)
{
    ll s = -(c.fst * b.snd - b.fst * c.snd) - a.fst * c.snd + a.snd * c.fst + a.fst * b.snd - a.snd * b.fst;
    if (s < 0)
        return -1;
    if (s > 0)
        return 1;
    return 0;
}

class classname
{
    public :
        method
        {
            vector<pii> a;
            int ans = 0;
            int n = x.size();
            fori(n)
                a.pb({x[i], y[i]});
            pii zero = {0, 0};
            fori(n)
                FOR(j, i + 1, n)
                    FOR(k, j + 1, n)
                        {
                            int r = ori(a[i], a[j], a[k]);
                            if (ori(a[i], a[j], zero) == r && ori(a[k], a[i], zero) == r && ori(a[j], a[k], zero) == r)
                                ans++;
                        }
            return ans;
        }
};
