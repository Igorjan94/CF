#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#define ll long long

using namespace std;

struct edge
{
    int y, opp;
    ll p, c, f;
    edge(int e, ll r, ll t, ll u, int o)
    {
        y = e;
        c = r;
        f = t;
        p = u;
        opp = o;
    }
    edge(){};
};

const ll INF = 140737488355328;//==2^63
vector<int> place, p;
vector<ll> fi, d;
vector< vector< edge > > edges;
priority_queue< pair<ll, int> > q;
vector<bool> in;
int s = 1;
int f, u, v, n, m;
ll w, curd, mn, dfi;

void FordBellman()
{
    fi.resize(n + 1);
    in.resize(n + 1, false);
    fi[s] = 0;
    in[s] = true;
    queue<int> qfb;
    qfb.push(s);
    int u, v;
    ll w;
    while (!qfb.empty())
    {
        u = qfb.front();
        qfb.pop();
        in[u] = false;
        for (int i = 0; i < edges[u].size(); i++)
        {
            if (edges[u][i].c <= edges[u][i].f)
                continue;
            v = edges[u][i].y;
            w = edges[u][i].p + fi[u];
            if (fi[v] > w)
            {
                fi[v] = w;
                if (!in[v])
                    in[v] = true,
                    qfb.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < edges[i].size(); j++)
            edges[i][j].p += (fi[i] - fi[edges[i][j].y]);
 }

int dijkstra()
{
    q.push(make_pair(0, s));
    d.clear();
    d.resize(n + 1, INF);
    d[s] = 0;
    mn = INF;
    if (s == f)
        return 0;
    while (!q.empty())
    {
        u = q.top().second;
        curd = -q.top().first;
        q.pop();
        if (curd > d[u])
            continue;
        for (int i = 0; i < edges[u].size(); i++)
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
                p[v] = u;
                mn = min(edges[u][i].c - edges[u][i].f, mn);
                place[v] = i;
                q.push(make_pair(-d[v], v));
            }
        }
    }
    return (d[f] == INF) ? -1 : d[f];
}

int main()
{
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w+", stdout);
    scanf("%d %d\n", &n, &m);
    f = n;
    edges.resize(n + 1);
    place.resize(n + 1);
    p.resize(n + 1);
    int x, y, add;
    long long price = 0, pp, c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %I64d %I64d", &x, &y, &c, &pp);
        edge r = edge(y, c, 0, pp, edges[y].size());
        edges[x].push_back(r);
        edge r1 = edge(x, 0, 0, -pp, edges[x].size() - 1);
        edges[y].push_back(r1);
    }
    fclose(stdin);
    FordBellman();
    while (true)
    {
        add = dijkstra();
        if (add == -1)
            break;
        for (int v = f; v != s; v = p[v])
        {
            edges[p[v]][place[v]].f += mn;
            edges[ edges[p[v]][place[v]].y ][ edges[p[v]][place[v]].opp ].f -= mn;
        }
        price += mn * add + fi[n] - fi[1];
    }
    cout << price << end;
    fclose(stdout);
    return 0;
}
