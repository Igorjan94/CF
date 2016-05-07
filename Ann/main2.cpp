#include <vector>
#include <iostream>
#include <iomanip>
#include <future>

using std::cout;
using std::vector;

void printArray(vector<vector<double>>& a)
{
    for (int i = 0; i < a.size(); ++i, cout << "\n")
        for (int j = 0; j < a[0].size(); ++j, cout << " ")
            cout << std::fixed << std::setw(5) << a[i][j];
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cout.precision(2);
    int w, n;
    std::cin >> w >> n;
    vector<vector<double>> d(n + 1, vector<double>(w + 1, 0)), a(n + 1, vector<double>(w + 1, 0));
    vector<vector<int>> parent(n + 1, vector<int>(w + 1, -1));
    vector<int> ans;
    for (int i = 1; i <= w; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> d[j][i];
    //printArray(d);

    for (int i = 1; i <= n; ++i)
        for (int c = 0; c <= w; ++c)
            for (int k = 0; k <= c; ++k)
                if (a[i][c] < a[i - 1][c - k] + d[i][k])
                    a[i][c] = a[i - 1][c - k] + d[i][k],
                    parent[i][c] = k;
    //printArray(a);

    std::function<void(int, int)> findans = [&](int k, int s)
    {
        if (k == 0)
            return;
        if (parent[k][s] == -1)
            findans(k - 1, s),
            ans.push_back(0);
        else 
            findans(k - 1, s - parent[k][s]),
            ans.push_back(parent[k][s]);
    };
    findans(n, w);
    cout << "Overall profit is " << std::fixed << a[n][w] << "\n";
    for (int i = 0; i < n; ++i)
        cout << ans[i] << " y. e goes to " << (i + 1) << "-th\n";
    return 0;
}
