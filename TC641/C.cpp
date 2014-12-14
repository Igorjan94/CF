//template igorjan94 version from 05 December 2014
#include <bits/stdc++.h>

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

using namespace std;

#define method      string shuffle(vector <int> a)

#define classname   ShufflingCardsDiv2

class classname
{
    public :
        method
        {
            int n = a.size();
            vi x, y;
            fori(n)
                (i % 2 ? y : x).pb(a[i]);
            int c = n / 2;
            int N = (c + 1) / 2;
            int count = 0;
            fori(x.size())
                if (x[i] <= c)
                    count++;
            return count == N ? "Possible" : "Impossible";
        }
};
