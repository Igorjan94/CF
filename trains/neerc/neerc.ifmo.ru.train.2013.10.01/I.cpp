#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#define INF 1000000007

using namespace std;

vector< vector<int> > g;
vector< vector<bool> > used;
vector<int> t, ans;
int n, m, k;
set<int> helpi[2];
vector< set<int> > helpj[2];
bool f = false;

void dfs(int i, int j, int t)
{
    if (used[i][j] || g[i][j] <= t)
        return;
    used[i][j] = true;
    helpj[!f][i].insert(j);
    helpi[!f].insert(i);
    if (i > 0)
        dfs(i - 1, j, t);
    if (i < n - 1)
        dfs(i + 1, j, t);
    if (j > 0)
        dfs(i, j - 1, t);
    if (j < m - 1)
        dfs(i, j + 1, t);
}

void run()
{
    scanf("%d %d\n", &n, &m);
    g.clear();
    g.resize(n + 1);
    for (int i = 0; i < n; i++)
    {
        helpi[0].insert(i);
        g[i].resize(m + 1);
        for (int j = 0; j < m; j++)
            scanf("%d", &g[i][j]);
    }
    int ttt;
    scanf("%d\n", &ttt);
    t.clear();
    t.resize(ttt + 1);
    for (int i = 0; i < ttt; i++)
        scanf("%d", &t[i]);
    int c = 0;
    helpj[0].clear();
    helpj[0].resize(n + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            helpj[0][i].insert(j);
    for (int k = 0; k < ttt; k++)
    {
        if (k > 0 && t[k - 1] == t[k])
        {
            printf("%d%c", c, k == ttt - 1 ? '\n' : ' ');
            continue;
        }
        helpj[!f].clear();
        helpj[!f].resize(n + 1);
        helpi[!f].clear();
        c = 0;
        used.clear();
        used.resize(n + 1);
        for (int i = 0; i < n; i++)
            used[i].resize(m + 1, false);
        for (set<int>::iterator it = helpi[f].begin(); it != helpi[f].end(); it++)
            for (set<int>::iterator it2 = helpj[f][*it].begin(); it2 != helpj[f][*it].end(); it2++)
                if (!used[*it][*it2] && g[*it][*it2] > t[k])
                    dfs(*it, *it2, t[k]),
                    c++;
        printf("%d%c", c, k == ttt - 1 ? '\n' : ' ');
        f = !f;
    }
}

int main()
{
   // freopen("matching.in", "r", stdin);
 //   freopen("matching.out", "w+", stdout);
    int T;
    scanf("%d\n", &T);
    for (int TT = 0; TT < T; TT++)
        run();
    return 0;
}
