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

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.out", "w+", stdout);
    scanf("%d\n", &n);
    edges.resize(n + 1);
    int x, y = 1;
    char s[5001][101];
    char g;
    for (int i = 0; i < n; i++)
    {
       scanf("%s\n", &s[i + 1]);
       while (true)
       {
            scanf("%d%c", &y, &g);
            edges[i + 1].push_back(y);
            if (g == '\n')
                break;
       }
    }
    d.resize(n + 1, -1);
    int c = 0;
    for (int i = 1; i <= n; i++)
    {
        used.clear();
        used.resize(n + 1, false);
        if (dfs(i))
           c++;
    }
    for (int i = 1; i <= n; i++)
        printf("%s%c", s[d[i]], i == n ? '\n' : ' ');
//    printf("%d", c);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
