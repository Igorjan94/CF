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
#define     cnd      second
#define      pb      push_back
#define      ll      long long
#define      vi      vector<int>
#define     pii      pair<int, int>
#define     vll      vector<long long>
#define     vvi      vector<vector<int> >
#define     pll      pair<long long, long long>
#define   whole(a)   a.begin(), a.end()

#define argmax(a) max_element(whole(a)) - (a).begin()
#define argmin(a) min_element(whole(a)) - (a).begin()

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

#define method      int meet(int t, vi q, vi p)

#define classname   BuyingTshirts

class classname
{
    public :
        method
        {
            int ans = 0;
            int sum1 = 0, sum2 = 0;
            fori(q.size())
            {
                sum1 += q[i];
                sum2 += p[i];
                if (sum1 >= t && sum2 >= t)
                    ans++;
                sum1 %= t;
                sum2 %= t;
            }
            return ans;
        }
};
