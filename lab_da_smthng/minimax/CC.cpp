#define ll int
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#define qw printf("ololo\n");

using namespace std;

const int INF = 1000000001;
int n, size;
vector< vector< bool > > b;
vector< vector< int > > answer;
vector<int> dr, dc, p, minpos, minv;
vector<bool> vis;

struct edge
{
    int y;
    ll p, c, f, opp;
    edge(int e, ll r, ll t, ll u, int a)
    {
        y = e;
        c = r;
        f = t;
        p = u;
        opp = a;
    }
    edge(){};
};

vector<int> place, pp;
vector<ll> fi, d;
vector< vector< edge > > edges;
priority_queue< pair<ll, int> > q;
vector<bool> in;
int s = 0;
int f, u, v, m;
ll w, curd, mn, dfi;

int dijkstra()
{
    q.push(make_pair(0, s));
    d.clear();
    d.resize(2 * n + 2, INF);
    d[s] = 0;
    mn = INF;
    while (!q.empty())
    {
        u = q.top().second;
        curd = -q.top().first;
        q.pop();
        if (curd > d[u])
            continue;
        for (int i = 1; i < edges[u].size(); i++)
        {
            if (edges[u][i].c <= edges[u][i].f)
                continue;
            v = edges[u][i].y;
            w = edges[u][i].p;
            if (u == v)
                continue;
            dfi = d[u] + w;
            if (d[v] > dfi)
            {
                d[v] = dfi;
                pp[v] = u;
                mn = min(edges[u][i].c - edges[u][i].f, mn);
                place[v] = i;
                q.push(make_pair(-d[v], v));
            }
        }
    }
    return (d[f] == INF) ? -1 : d[f];
}

int dfs(int k)
{
    vis[k] = true;
    int t = p[k];
    int temp = k;
    int d = INF;
    for (int j = 1; j <= n; j++)
        if (!vis[j])
        {
            if (edges[t][j].f == 1 && edges[t][j].p - dr[t] - dc[j] < minv[j])
            {
                minv[j] = edges[t][j].p - dr[t] - dc[j];
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
        edges[p[i]][i].f = 0,
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
    b.resize(n + 2);
    answer.resize(z + 1);
    size = 1;
    f = 2 * n + 1;
    edges.resize(2 * n + 2);
    place.resize(2 * n + 2);
    pp.resize(2 * n + 2);
    int x, y, add;
    int price = 0, c;
    edge e = edge(0, 0, 0, 0, -1);
    for (int i = 0; i <= 2 * n + 1; i++)
        edges[i].push_back(e);
    for (int i = 1; i <= n; i++)
    {
        b[i].resize(n + 1, false);
        edge r0 = edge(i, z, 0, 1, n + 1);
        edges[0].push_back(r0);
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &x);
            edge r = edge(n + j, 1, 0, x, edges[n + j].size());
            edge r5 = edge(i, 0, 0, -x, edges[i].size());
            edges[i].push_back(r);
            edges[j + n].push_back(r5);
        }
        scanf("\n");
    }
    for (int i = 1; i <= n; i++)
    {
        edge r8 = edge(0, 0, 0, -1, i);
        edge r2 = edge(2 * n + 1, z, 0, 1, edges[2 * n + 1].size());
        edge r7 = edge(i + n, 0, 0, -1, edges[i + n].size());
        edges[i].push_back(r8);
        edges[i + n].push_back(r2);
        edges[2 * n + 1].push_back(r7);
    }
    fclose(stdin);
    while (true)
    {
        add = dijkstra();
        if (add == -1)
            break;
        for (int v = f; v != s; v = pp[v])
            edges[pp[v]][place[v]].f += mn,
            edges[edges[pp[v]][place[v]].y][ edges[pp[v]][place[v]].opp ].f -= mn;
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
