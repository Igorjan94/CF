#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#include <ctime>

using namespace std;
vector< vector<int> > edges;
bool vertex[502][502];
bool edge[502][502];
vector<int> ss;
int n, m;


void dfs(int v, int d)
{
    if (v == n - 1 || ss[d] < v)
        throw 1;
    if (clock()*100000/CLOCKS_PER_SEC >= 1900)
    {
        throw 0;
    }
    for (int i = 0; i < edges[v].size(); i++)
    {
        int u = edges[v][i];
        if (!vertex[u][d + 1] && (i != 0 || !edge[v][d]))
            dfs(u, d + 1); else
                continue;
    }
}

int main()
{
 //   freopen("input.txt", "r", stdin);
    //freopen("output.out", "w+", stdout);
    int q;
    scanf("%d %d\n%d\n", &n, &m, &q);
    char c;
    edges.resize(n + 1);
    vertex[q][0] = true;
    if (q == 0)
    {
        printf("NO\n");
        return 0;
    }
    ss.push_back(q);
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            edges[i].push_back(i + 1);
        scanf("%c", &c);
        if (c == 'L')
        {
            q--;
            edge[q][i] = true;
        } else
        {
            edge[q][i] = true;
            q++;
        }
        ss.push_back(q);
        vertex[q][i + 1] = true;
    }
    int x, y;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d\n", &x ,&y);
        if (x < y)
            edges[x].push_back(y); else
            edges[y].push_back(x);
    }
    try
    {
        dfs(0, 0);
    }
    catch(int e)
    {
        if (e == 1)
        printf("YES\n"); else
        printf("NO\n");
        return 0;
    }
 //   fclose(stdin);
 //   fclose(stdout);
    printf("NO\n");
    return 0;
}
