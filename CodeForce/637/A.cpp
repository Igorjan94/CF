#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    map<int, pair<int, int>> m;
    for (int i = 0; i < n; ++i)
        m[a[i]].first++,
        m[a[i]].second = -i;
    cout << (max_element(m.begin(), m.end(), [](pair<int, pair<int, int>> x, pair<int, pair<int, int>> y) {
        return x.second < y.second;
    })->first) << "\n";
    return 0;
}
