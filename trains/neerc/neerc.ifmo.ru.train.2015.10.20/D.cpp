#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    int n, k;
    queue<pair<int, int>> q;
    scanf("%d%d", &n, &k);
    int t;
    vector<int> a;
    set<int> available;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &t);
        while (q.size() && q.front().first <= t)
        {
            int u = q.front().second;
            a[u]--;
            if (a[u] == k - 1)
                available.insert(u);
            q.pop();
        }
        int l;
        if (!available.size())
        {
            l = a.size();
            a.push_back(0);
        } else
            l = *available.begin();
        a[l]++;
        if (a[l] < k)
            available.insert(l);
        else
            available.erase(l);
        q.push({t + 1000, l});
        ans = max(ans, (int)a.size());
    }
    printf("%d\n", ans);
}
