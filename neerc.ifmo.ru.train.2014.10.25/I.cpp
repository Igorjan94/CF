#include <bits/stdc++.h>
 
#define fori(n) for (int i = 0; i < n; ++i)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
 
#define fst first
#define snd second
#define pb push_back
 
using namespace std;
 
int main()
{
    //freopen("in.c", "r", stdin);
    int n, m;
    while (true)
    {
        cin >> n >> m;
        if (n + m == 0)
            return 0;
        vector<pair<int, int> > a;
        int x, y;
        fori(n)
        {
            cin >> x >> y;
            cin >> x >> y;
            a.pb({x, x + y});
        }
        fori(m)
        {
            cin >> x >> y;
            y += x;
            int ans = 0;
            fori(n)
                if (!(a[i].fst >= y || a[i].snd <= x))
                    ans++;
            cout << ans << "\n";
        }
    }
}