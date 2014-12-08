#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
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

int main()
{
    int a, b, w, x, c;
    cin >> a >> b >> w >> x >> c;
    if (c <= a)
    {
        cout << 0 << endl;
        return 0;
    }
    ll count = 0;
    int delta = 0;
    c -= a;
    vector<pii> v(w);
    vector<bool> used(w, false);
    fori(w)
        if (i >= x)
            v[i] = make_pair(i - x, 1);
        else
            v[i] = make_pair(i + w - x, 0);

    while (!used[b] && delta != c)
    {
        used[b] = true;
        delta += v[b].second;
        b = v[b].first;
        count++;
    }
    if (delta == c)
    {
        cout << count << endl;
        return 0;
    }

    if (c % delta)
        count = count * (c / delta),
        c %= delta;
    else
        count = count * (c / delta - 1),
        c = delta;

    while (c)
    {
        c -= v[b].second;
        b = v[b].first;
        count++;
    }
    cout << count << endl;
    return 0;
}
