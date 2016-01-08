#include <bits/stdc++.h>
#define problem "distance"
 
using namespace std;
 
 
char s[100001];
char t[100001];
 
int main()
{
    ios_base::sync_with_stdio(false);
    freopen(problem".in", "r", stdin);
    freopen(problem".out", "w", stdout);
 
    cin >> s;
    cin >> t;
    int k;
    cin >> k;
 
    int r = k + 2;
 
    int n = strlen(s);
    int m = strlen(t);
 
    if (abs(m - n) > k)
    {
        cout << "Infinity\n";
        return 0;
    }
 
    vector<vector<int>> dp(n + 1, vector<int>(2 * r + 1, r * 2));
 
    for (int i = 0, j = 0; j < dp[i].size(); j++)
    {
        dp[i][j] = j;
    }
 
    for (int i = 0, j = 0; i <= r; i++)
    {
        if (i <= n)
        {
            dp[i][j] = i;
        }
    }
 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < dp[i].size(); j++)
        {
            if (i <= r)
            {
                int x = i - 1, y = j - 1;
 
                if (s[x] == t[y])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j - 1];
 
                    if (dp[i][j] > dp[i][j - 1]) {
                        dp[i][j] = dp[i][j - 1];
                    }
 
                    if (dp[i][j] > dp[i - 1][j]) {
                        dp[i][j] = dp[i - 1][j];
                    }
 
                    ++dp[i][j];
                }
            }
            else
            {
                int x = i - 1, y = i - r + j - 1;
                if (s[x] == t[y])
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
 
                    if (j > 1 && dp[i][j] > dp[i][j - 1]) {
                        dp[i][j] = dp[i][j - 1];
                    }
 
                    if (dp[i][j] > dp[i - 1][j + 1]) {
                        dp[i][j] = dp[i - 1][j + 1];
                    }
 
                    ++dp[i][j];
                }
            }
        }
    }
 
 
    int ans = dp[n][r];
 
    if (ans <= k) {
        cout << ans << '\n';
    } else {
        cout << "Infinity\n";
    }
 
    return 0;
}