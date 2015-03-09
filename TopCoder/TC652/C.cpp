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

#define method      vector <int> findPath(vector <int> x, vector <int> y)
#define classname   NoRightTurnDiv2

bool ori(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 * y3 - x3 * y2 - x1 * y3 + x3 * y1 + x1 * y2 - x2 * y1) > 0;
}

class classname
{
    public :
        method
        {
            int n = x.size();
            vector<bool> used(n, false);
            vector<int> ans;
            pair<int, int> mn = {x[0], y[0]};
            int cur = 0;
            fori(n)
                if (i)
                    if (mn > make_pair(x[i], y[i]))
                        mn = {x[i], y[i]},
                        cur = i;
            used[cur] = true;
            ans.push_back(cur);
            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    if (!used[j])
                    {
                        bool ok = true;
                        for (int k = 0; k < n; k++)
                            if (!used[k] && k != j)
                                ok &= ori(x[cur], y[cur], x[j], y[j], x[k], y[k]);
                        if (ok)
                        {
                            cur = j;
                            ans.push_back(cur);
                            used[cur] = true;
                            break;
                        }
                    }
            }
            return ans;
        }
};

#ifndef ONLINE_JUDGE
#include "../../writeln.h"

int main()
{
    classname x;
    vector<int> a, b;
    readln(a, b);
    writeln(x.findPath(a, b));
}
#endif
