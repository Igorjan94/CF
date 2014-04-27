#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define enter printf("\n");
#define pb push_back

using namespace std;
int INF = 1000000007;
vector< vector<int> > a;
vector<int> used;
string FILENAME = "bugs";
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

queue<int> q;
vector<bool> visited;
bool bfs(int v)
{
    used[v] = 1;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        visited[v] = true;
        q.pop();
        for (int i = 0; i < a[v].size(); i++)
            if (used[a[v][i]])
            {
                if ((used[a[v][i]] - used[v]) % 2 == 0)
                {
                    while (!q.empty())
                        q.pop();
                    return true;
                }
            } else
            {
                used[a[v][i]] = used[v] + 1;
                q.push(a[v][i]);
            }
    }
    return false;
}

void run()
{
    int n, m;
    readln(n, m);
    visited.clear();
    visited.resize(n + 1);
    used.clear();
    used.resize(n + 1);
    a.clear();
    a.resize(n + 1);
    int x, y;
    for (int i = 0; i < m; i++)
    {
        readln(x, y);x--;y--;
        a[x].pb(y);
        a[y].pb(x);
    }
//    for (int i = 0; i < n; i++)
  //      for (int j = 0; j < a[i].size(); j++)
    //    printf("%d %d\n", i, a[i][j]);
    bool ans = false;
    for (int i = 0; i < n && !ans; i++)
        if (!visited[i])
            ans |= bfs(i);
                //writeln(used);

    if (ans)
        printf("Suspicious bugs found!"); else
        printf("No suspicious bugs found!");
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
