#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, ans = 0;
    scanf("%d", &n);
	vector<long long> a(n), b(n, 0);
    for (int i = 0; i < n; ++i)
        scanf("%lld", &a[i]);
    partial_sum(a.begin(), a.end(), b.begin());
    map<long long, int> x;
    for (auto y : b)
        x[y]++;
    for (auto y : x)
        ans = max(ans, y.second);
    printf("%d\n", n - ans);
    return 0;
}
