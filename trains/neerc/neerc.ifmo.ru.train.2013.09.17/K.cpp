#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define ll long long
#define enter printf("\n");
#define pb push_back

using namespace std;
int INF = 1000000007;
vector<int> d;
vector< vector< pair<int, int> > > edges;
int a[101][101];
int n;
string FILENAME = "honeymoon";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int dijkstra()
{
    priority_queue< pair<int, int> > q;
    q.push(make_pair(0, 0));
    d.clear();
    d.resize(n * n, INF);
    d[0] = 0;
    int u, curd, v, w;
    while (!q.empty())
    {
          u = q.top().second;
          curd = -q.top().first;
          q.pop();
          if (curd > d[u])
             continue;
          for (int i = 0; i < edges[u].size(); i++)
          {
              v = edges[u][i].first;
              w = edges[u][i].second;
              if (u == v)
                  continue;
              if (d[v] > d[u] + w)
              {
                  d[v] = d[u] + w;
                  q.push(make_pair(-d[v], v));
              }
          }
    }
    return d[n * n - 1];
}

void run()
{
    readln(n);
    int x;
    edges.clear();
    edges.resize(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            read(a[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i > 0)
                edges[n * i + j].pb(make_pair(n * (i - 1) + j, a[i][j] - a[i - 1][j]));
            if (j > 0)
                edges[n * i + j].pb(make_pair(n * i + j - 1, a[i][j] - a[i][j - 1]));
            if (i < n - 1)
                edges[n * i + j].pb(make_pair(n * (i + 1) + j, a[i][j] - a[i + 1][j]));
            if (j < n - 1)
                edges[n * i + j].pb(make_pair(n * i + j + 1, a[i][j] - a[i][j + 1]));
        }
    printf("%d", dijkstra());
//    for (int i = 0; i < n * n; i++)
  //      for (int j = 0; j < edges[i].size(); j++)
    //        printf("%d %d %d\n", i, edges[i][j].first, edges[i][j].second);
    writeln(d);
}

int main()
{
   freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
   freopen(FILENAME.append(".out").c_str(), "w", stdout);
   int T;
   readln(T);
   for (int TT = 0; TT < T; TT++)
   {
        printf("Scenario #%d:\n", TT + 1);
        run();
        if (TT < T - 1)
            printf("\n\n");
   }
   return 0;
}
