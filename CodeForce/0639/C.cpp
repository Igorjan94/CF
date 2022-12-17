#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n, k, i, j, ans = 0;
    cin >> n >> k;
    vector<long long> a(n + 1), suf(n + 1, 0), pref(n + 1, 0);
    for (int q = 0; q <= n; ++q)
        cin >> a[q];
    for (i = 0; ((pref[i] + a[i]) % 2 == 0) && i < n; ++i)
        pref[i + 1] = (pref[i] + a[i]) / 2;
    for (j = n; (abs(suf[j] + a[j]) * 2 < 1000000000000ll) && j > 0; --j)
        suf[j - 1] = (suf[j] + a[j]) * 2;
    for (int q = j; q <= i; ++q)
        if (abs(pref[q] + suf[q]) <= k && ((pref[q] + suf[q] != 0) || (q != n)))
            ans++;
    cout << ans << "\n";
    return 0;
}
