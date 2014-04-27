#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

vector< vector<int> > edges;
vector<int> d;
vector<bool> used;
int n, m, k;

bool dfs(int v, int m)
{
     if (used[v])
        return false;
     used[v] = true;
     for (int i = 1; i <= n; i++)
     {
         if (edges[v][i] < m)
            continue;
         if (d[i] == -1 || dfs(d[i], m))
         {
            d[i] = v;
            return true;
         }
     }
     return false;
}

int ans(int m)
{
    d.clear();
    d.resize(n + 1, -1);
    int c = 0;
    for (int i = 1; i <= n; i++)
    {
        used.clear();
        used.resize(n + 1, false);
        if (dfs(i, m))
           c++;
    }
    return c;
}

int main()
{
    freopen("minimax.in", "r", stdin);
    freopen("minimax.out", "w+", stdout);
    scanf("%d\n", &n);
    edges.resize(n + 1);
    int x, mx = -1, mn = 1000000001;
    for (int i = 1; i <= n; i++)
    {
        edges[i].resize(n + 1);
        for (int j = 1; j <= n; j++)
            scanf("%d", &edges[i][j]),
            mx = max(mx, edges[i][j]),
            mn = min(mn, edges[i][j]);
        scanf("\n");
    }
    int l = mn, r = mx, m;
    while (l < r)
    {
        if (l == r - 1)
        {
            ans(r) >= n ? m = r : m = l;
            break;
        }
        m = (r + l) / 2;
        ans(m) >= n ? l = m : r = m;
    }
    printf("%d\n", m);
    fclose(stdin);
    fclose(stdout);
    return 0;
}

