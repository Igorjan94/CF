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

bool dfs(int v)
{
     if (used[v])
        return false;
     used[v] = true;
     for (int i = 0; i < edges[v].size(); i++)
     {
         int u = edges[v][i];
         if (d[u] == -1 || dfs(d[u]))
         {
            d[u] = v;
            return true;
         }
     }
     return false;
}

void run()
{
    scanf("%d\n", &n);
    edges.clear();
    edges.resize(n + 1);
    d.clear();
    d.resize(n + 1, -1);
    char x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%c", &x);
            if (x == '1')
                edges[i].push_back(j);
        }
        scanf("\n");
    }
//    for (int i = 0; i < n; i++)
  //      for (int j = 0; j < edges[i].size(); j++)
    //        printf("%d%c", edges[i][j], j == edges[i].size() - 1 ? '\n' : ' ');
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        used.clear();
        used.resize(n + 1, false);
        dfs(i);
    }
 	for (int i = 0; i < n; i++)
		if (d[i] != -1)
            c++;
    //printf("%d\n", c);
    printf(c % 4 == 0 ? "YES\n" : "NO\n");
}

int main()
{
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w+", stdout);
    int T;
    scanf("%d\n", &T);
    for (int TT = 0; TT < T; TT++)
        run();
    return 0;
}
