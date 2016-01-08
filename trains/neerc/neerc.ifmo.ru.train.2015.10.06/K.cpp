#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#define problem "tree"
 
using namespace std;
 
int main()
{
    ios_base::sync_with_stdio(false);
    freopen(problem".in", "r", stdin);
    freopen(problem".out", "w", stdout);
 
    int n, root;
    cin >> n;
    vector<vector<int>> g(n);
 
    vector<int> color(n);
    vector<int> ans(n, 0);
 
    for (int v = 0; v < n; v++)
    {
        int u, c;
        cin >> u >> c;
        color[v] = c;
        if (u == 0)
        {
            root = v;
        }
        else
        {
            g[u - 1].push_back(v);
        }
    }
 
    vector<int> q(n);
 
    int head = 0, tail = 0;
 
    q[tail++] = root;
 
    while (head != tail)
    {
        int u = q[head++];
 
        int m = g[u].size();
 
        for (int i = 0; i < m; i++)
        {
            q[tail++] = g[u][i];
        }
    }
 
    vector<set<int>*> s(n, NULL);
    for (int i = n - 1; i >=0; i--)
    {
        int u = q[i];
 
        int m = g[u].size();
 
        for (int j = 0; j < m; j++)
        {
            int v = g[u][j];
 
            if (s[u] == NULL || s[u]->size() < s[v]->size())
            {
                s[u] = s[v];
            }
        }
 
        for (int j = 0; j < m; j++)
        {
            int v = g[u][j];
 
            if (s[u] != s[v])
            {
                for(set<int>::iterator itr = s[v]->begin(); itr != s[v]->end(); ++itr)
                {
                    s[u]->insert(*itr);
                }
            }
        }
 
        if (s[u] == NULL)
        {
            s[u] = new set<int>();
        }
 
        s[u]->insert(color[u]);
        ans[u] = s[u]->size();
    }
 
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << ' ';
    }
 
 
    return 0;
}