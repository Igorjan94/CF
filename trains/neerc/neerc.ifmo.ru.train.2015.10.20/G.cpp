#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int n, m, k = 10001;
    scanf("%d", &n);
 
    vector<pair<int,int>> g;
 
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        g.push_back({x, y});
    }
 
 
    vector<vector<pair<double, double>>> s(k);
    vector<vector<pair<double, double>>> t(k);
 
    double eps = 1e-9;
    scanf("%d", &m);
 
    for (int i = 0; i < m; i++)
    {
        int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
 
        int u = min(y + r, k - 1);
        int d = max(y - r, 0);
 
        for (int j = d; j <= u; j++)
        {
            int dy = j - y;
            double dr = sqrt(r * r - dy * dy) + eps;
            s[j].push_back({x - dr, x + dr});
        }
    }
    for (int y = 0; y < k; y++)
    {
        sort(s[y].begin(), s[y].end());
 
        double curL = -2, curR = -1;
 
        for (auto &seg : s[y])
        {
            if (curR < seg.first)
            {
                t[y].push_back({curL, curR});
                curL = seg.first;
                curR = seg.second;
            }
            else
            {
                curR = max(curR, seg.second);
            }
        }
        t[y].push_back({curL, curR});
    }
 
    int ans = n;
    for (int i = 0; i < n; i++)
    {
        int x = g[i].first, y = g[i].second;
        int len = t[y].size();
        int l = 0, r = len - 1;
 
        while (r - l > 1)
        {
            int mid = (r + l) / 2;
 
            if (t[y][mid].first < x)
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }
 
 
        l -= 2;
        r += 2;
 
        bool ok = false;
 
        for (int j = l; j <= r; j++)
        {
            if (0 <= j && j < len)
            {
                pair<double, double> seg = t[y][j];
                ok |= (seg.first <= x) && (x <= seg.second);
            }
 
        }
 
        if (ok)
        {
            --ans;
        }
 
    }
 
 
 
 
 
    printf("%d\n", ans);
}
