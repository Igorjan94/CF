#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector< vector<int> > a;
vector< pair<int, int> > in;
vector<int> d;
vector<bool> used;
queue<int> q;

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

int main()
{
  // freopen("input.txt", "r", stdin);
   int n;
   readln(n);
   a.resize(n);
   for (int rr = 0; rr < n; rr++)
   {
       int x, y, z;
       readln(x, y, z);
       if (x == 1)
       {
           in.push_back(make_pair(y, z));
           if (in.size() != 1)
           for (int i = 0; i < in.size() - 1; i++)
           {
            if (in[i].first < in[in.size() - 1].first && in[i].second > in[in.size() - 1].first ||
                in[i].first < in[in.size() - 1].second && in[i].second > in[in.size() - 1].second)
                    a[in.size() - 1].push_back(i);
            if (in[in.size() - 1].first < in[i].first && in[in.size() - 1].second > in[i].first ||
                in[in.size() - 1].first < in[i].second && in[in.size() - 1].second > in[i].second)
                    a[i].push_back(in.size() - 1);
           }
       } else
       {
            y--;z--;
    q.push(y);
    d.clear();
    used.clear();
    d.resize(n + 1, INF);
    used.resize(n + 1, false);
    d[y] = 0;
    used[y] = true;
    bool f = false;
    int u, v;
    while (!q.empty())
    {
          int u = q.front();
          q.pop();
          for (int i = 0; i < a[u].size(); i++)
          {
              int v = a[u][i];
              if (d[v] > d[u] + 1)
              {
                  d[v] = d[u] + 1;
                  if (!used[v])
                  {
                      used[v] = true;
                      q.push(v);
                  }
              }
          }
    }
    f = d[z] != INF;
    if (z >= in.size())
            f = false;
    printf("%s\n", f ? "YES" : "NO");
       }
   }
   return 0;
}
