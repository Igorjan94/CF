#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <bits/stdc++.h>
#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QTextStream>
#include <QDebug>
#define enter printf("\n")
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;

struct Solution
{
    int n, m, count;
    vector<vector<int>> a;
    int ans = 0;
    int dfscount = 0;

    void input(QTextStream &in)
    {
        in >> n >> m >> count;
        a.resize(n + 2);
        fori(n + 1)
            a[i].resize(m + 2);
    }

    void dfs(int i, int j, vector<vector<int>> aa, int cur = 1)
    {
        if (i == 0 || j == 0 || i == n + 1 || j == m + 1)
            return;
        aa[i][j] = 1;
        if (cur == count)
            throw aa;
        dfscount++;
        int temp = 0;
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                if (!(i + dx == 0 || j + dy == 0 || i + dx == n + 1 || j + dy == m + 1))
                    if (aa[i + dx][j + dy] == 0)
                        aa[i + dx][j + dy] = 1,
                        temp++;
        if (cur + temp > count || temp == 0)
            return;
        else
            for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++)
                    if (dx * dx + dy * dy)
                        dfs(i + dx, j + dy, aa, cur + temp);
    }

    void solve()
    {
        if (n == 1)
        {
            ans = 1;
            a[1][1] = 2;
            forn1(j, m - count)
                a[1][j + 1] = 1;
            return;
        }
        if (m == 1)
        {
            ans = 1;
            a[1][1] = 2;
            forn1(j, n - count)
                a[j + 1][1] = 1;
            return;
        }
        if (n == 2 || m == 2)
            if (count % 2 && count != n * m - 1)
            {
                ans = 0;
                return;
            }
        if (count == 0)
        {
            ans = 1;
            fori(n + 1)
                forj(m + 1)
                    a[i][j] = 1;
            a[1][1] = 2;
            return;
        }
        count = n * m - count;
        forn1(i, n + 1)
            forn1(j, m + 1)
                try
                {
                    dfs(i, j, a);
                }
                catch(vector<vector<int>> e)
                {
                    ans = 1;
                    e[i][j] = 2;
                    fori(n+1)
                        forj(m+1)
                            a[i][j] = e[i][j];
                    return;
                }
        ans = 0;
    }

    void output(QTextStream &out)
    {
        if (ans == 0)
            out << "Impossible\n";
        else
            forn1(i, n + 1)
            {
                forn1(j, m + 1)
                    out << (a[i][j] == 0 ? '*' : a[i][j] == 1 ? '.' : 'c');
                out << "\n";
            }
    }
};

#endif // SOLUTION_HPP
