#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

const int INF = 1000000001;
int n;
vector< vector< int > > a;
vector<int> dr, dc, p, minpos, minv;
vector<bool> vis;

int dfs(int k, int m)
{
    vis[k] = true;
    int t = p[k];
    int temp = k;
    int d = INF;
    for (int j = 1; j <= n; j++)
        if (!vis[j])
        {
            if (a[t][j] >= m && a[t][j] - dr[t] - dc[j] < minv[j])
            {
                minv[j] = a[t][j] - dr[t] - dc[j];
                minpos[j] = k;
            }
            if (minv[j] < d)
            {
                d = minv[j];
                temp = j;
            }
        }
    for (int j = 0; j <= n; j++)
        if (vis[j])
        {
            dr[p[j]] += d;
            dc[j] -= d;
        } else
            minv[j] -= d;
    return p[temp] != 0 ? dfs(temp, m) : temp;
}

void rec(int k)
{
     p[k] = p[minpos[k]];
     if (minpos[k] != 0)
         rec(minpos[k]);
}

int ans(int m)
{
    dr.clear();
    dc.clear();
    p.clear();
    minpos.clear();
    dr.resize(n + 1);
    dc.resize(n + 1);
    p.resize(n + 1);
    minpos.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        p[0] = i;
        minv.clear();
        vis.clear();
        minv.resize(n + 1, INF);
        vis.resize(n + 1, false);
        rec(dfs(0, m));
    }
    for (int i = 1; i <= n; i++)
        if (a[i][p[i]] < m)
            return -1;
    return 1;
}

int main()
{
    freopen("minimax.in", "r", stdin);
    freopen("minimax.out", "w+", stdout);
    scanf("%d\n", &n);
    a.resize(n + 1);
    int mx = -1, mn = INF;
    for (int i = 1; i <= n; i++)
    {
        a[i].resize(n + 1);
        for (int j = 1; j <= n; j++)
           scanf("%d", &a[i][j]),
           mx = max(mx, a[i][j]),
           mn = min(mn, a[i][j]);
        scanf("\n");
    }
    int l = mn, r = mx, m;
    while (l < r)
    {
        if (l == r - 1)
        {
            ans(r) > 0 ? m = r : m = l;
            break;
        }
        m = (r + l) / 2;
        ans(m) > 0 ? l = m : r = m;
    }
    printf("%d\n", m);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
