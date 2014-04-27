#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

const int INF = 1000000000;

struct e
{
    int y, c, f, opp;
    bool z;
    e() {}
    e(int b, int d, int k, int o)
    {
        z = true;
        y = b;
        c = d;
        f = k;
        opp = o;
    }
};
vector< vector< e > > edges;
queue<int> q;
vector<int> d;
vector<int> cur;
int s = 0;
int t;
int n, m;

bool bfs()
{
    d.clear();
    d.resize(n + 1, -1);
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1)
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < edges[v].size(); i++)
            if (edges[v][i].z)
            {
                int u = edges[v][i].y;
                if (d[u] == -1 && edges[v][i].c > edges[v][i].f)
                {
                    q.push(u);
                    d[u] = d[v] + 1;
                }
            }
    }
    while (!q.empty())
        q.pop();
    return d[t] != -1;
}

int dfs (int v, int flow)
{
    if (flow == 0)
        return 0;
    if (v == t)
        return flow;
    while (cur[v] < edges[v].size())
    {
        while (cur[v] < edges[v].size() && !edges[v][cur[v]].z)
            cur[v]++;
        int u = edges[v][cur[v]++].y;
        if (d[u] != d[v] + 1)
            continue;
        int pushed = dfs(u, min(flow, edges[v][cur[v] - 1].c - edges[v][cur[v] - 1].f));
        if (pushed != 0)
        {
            edges[v][cur[v] - 1].f += pushed;
            edges[u][edges[v][cur[v] - 1].opp].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

int f()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < edges[i].size(); j++)
            edges[i][j].f = 0;
    int flow = 0;
    while (bfs())
    {
        cur.clear();
        cur.resize(n + 1, 0);
        int pushed;
        while (true)
        {
            pushed = dfs(s, INF);
            flow += pushed;
            if (pushed == 0)
                break;
        }
    }
    return flow;
}

vector<int> used;
void deleteEdges(int u)
{
    used[u] = 1;
    for (int i = 0; i < edges[u].size(); i++)
        if (edges[u][i].c)
            if (used[edges[u][i].y] == 1)
                edges[u][i].z = false;
            else if (used[edges[u][i].y] == 0 && edges[u][i].z)
                deleteEdges(edges[u][i].y);
    used[u] = 2;
}

int main()
{
    freopen("start.in", "r", stdin);
//    freopen("maxflow.out", "w+", stdout);
    int k;
    scanf("%d %d\n", &n, &k);
    t = n - 1;
    edges.resize(n + 1);
    int x, y, w;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &x);
            if (x != 0)
            {
                edges[i].push_back(e(j, x, 0, edges[j].size()));
                edges[j].push_back(e(i, 0, 0, edges[i].size() - 1));
            }
        }
    printf("start with %d\n", f());
    used.resize(n + 1, false);
    deleteEdges(0);
    int temp = f();
    int delta = k;
    int mx, indI, indJ, df;
    while (true)
    {
        mx = temp, indI = -1, indJ = -1, df = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < edges[i].size(); j++)
                if (edges[i][j].z && edges[i][j].c)
                {
                    edges[i][j].c += delta;
                    int tt = f();
                    if (tt >= mx && edges[i][j].f > edges[i][j].c - delta)
                    {
                        indI = i;
                        indJ = j;
                        mx = tt;
                        df = edges[i][j].f - edges[i][j].c + delta;
                        printf("df = %d\n", df);
                    }
                    edges[i][j].c -= delta;
                }
        if (indI != -1 && indJ != -1)
        {
            int cc = min(delta, df);
            edges[indI][indJ].c += cc;
            delta -= cc;
            temp = mx;
            printf("%d\n", temp);
            if (delta == 0)
                break;
        }

    }
    printf("%d\n", temp);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
