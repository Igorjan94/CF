// Igorjan94, template version from 19 March 2015 (deleted unused defines & reorganization from 05 November 2015)
#include <bits/stdc++.h>

using namespace std;

int N;

int readln(vector<int>& a, int i = 0) { return i == N ? 1 : (scanf("%d", &a[i]) + readln(a, i + 1)); }
int readln(vector<vector<int>>& g, int i = 0) { return i == N ? 1 : readln(g[i]) + readln(g, i + 1); }

int rec(vector<vector<int>>& g, int i = 0, int j = 0, int k = 0)
{
    g[j][k] = min(g[j][k], g[j][i] + g[i][k]);
    bool x = (k == N - 1);
    k = (k + 1) % N;
    bool y = x && (j == N - 1);
    x ? j = (j + 1) % N : j = j;
    bool z = y && (i == N - 1);
    y ? i = (i + 1) % N : i = i;
    return z ? 0 : rec(g, i, j, k);
}

int mx(vector<vector<int>> a, int& m, int i = 0)
{
    m = max(m, *max_element(a[i].begin(), a[i].end()));
    return i == N - 1 ? 1 : mx(a, m, i + 1);
}

int main()
{
    cin >> N;
    vector<vector<int>> g(N, vector<int>(N));
    readln(g);
    rec(g);
    int ans = 0;
    mx(g, ans);
    cout << ans << "\n";
    return 0;
}
