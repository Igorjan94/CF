#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <bits/stdc++.h>
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
    int a, b, k;
    ll ans = 0;

    void input(QTextStream &in)
    {
        in >> a >> b >> k;
    }

    void solve()
    {
        forn(i, k)
            forn(q, a)
                forn(w, b)
                    if ((q & w) == i)
                        ans++;
    }

    void output(QTextStream &out)
    {
        out << ans << "\n";
    }
};

#endif // SOLUTION_HPP
