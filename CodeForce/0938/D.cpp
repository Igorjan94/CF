#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<ll, int>>> g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v; ll w;
        cin >> u >> v >> w; --u; --v;
        g[u].emplace_back(w, v);
        g[v].emplace_back(w, u);
    }
    vector<ll> d(n);
    set<pair<ll, int>> q;
    for (int i = 0; i < n; ++i)
        cin >> d[i],
        q.insert({d[i], i});
    vector<bool> used(n, false);
    while (!q.empty())
    {
        auto [dist, u] = *q.begin();
        q.erase(q.begin());
        used[u] = true;
        for (auto& [w, v] : g[u])
            if (!used[v] && d[v] > dist + 2 * w)
                q.erase({d[v], v}),
                d[v] = dist + 2 * w,
                q.insert({d[v], v});
    }
    for (int i = 0; i < n; ++i)
        cout << d[i] << " \n"[i == n - 1];
    return 0;
}
