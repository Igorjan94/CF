#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

const int INF = 1000000001;
int n, size;
vector< vector< int > > a;
vector< vector< bool > > b;
vector< vector< int > > answer;
vector<int> dr, dc, p, minpos, minv;
vector<bool> vis;

int dfs(int k)
{
    vis[k] = true;
    int t = p[k];
    int temp = k;
    int d = INF;
    for (int j = 1; j <= n; j++)
        if (!vis[j] && !b[t][j])
        {
            if (a[t][j] - dr[t] - dc[j] < minv[j])
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
    return p[temp] != 0 ? dfs(temp) : temp;
}

void rec(int k)
{
     p[k] = p[minpos[k]];
     if (minpos[k] != 0)
         rec(minpos[k]);
}

int ans()
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
        rec(dfs(0));
    }
    answer[size].resize(n + 1);
    for (int i = 1; i <= n; i++)
        b[p[i]][i] = true,
        answer[size][p[i]] = i;
    size++;
    return -dc[0];
}

int main()
{
    freopen("multiassignment.in", "r", stdin);
    freopen("multiassignment.out", "w+", stdout);
    int z;
    scanf("%d %d\n", &n, &z);
    a.resize(n + 1);
    b.resize(n + 1);
    answer.resize(z + 1);
    size = 1;
    for (int i = 1; i <= n; i++)
    {
        a[i].resize(n + 1);
        b[i].resize(n + 1, false);
        for (int j = 1; j <= n; j++)
           scanf("%d", &a[i][j]);
        scanf("\n");
    }
    int cost = 0;
    for (int i = 1; i <= z; i++)
        cost += ans();
    printf("%d\n", cost);
    for (int i = 1; i <= z; i++)
        for (int j = 1; j <= n; j++)
            printf("%d%c", answer[i][j], j == n ? '\n' : ' ');
    fclose(stdin);
    fclose(stdout);
    return 0;
}
