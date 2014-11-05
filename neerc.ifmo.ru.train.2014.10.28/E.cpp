#define TASKNAME ""
 
#include <bits/stdc++.h>
 
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)a.size()
#define fst first
#define snd second
#define fori(n) for(int i = 0; i < n; ++i)
#define fori1(n) for(int i = 1; i < n; ++i)
#define forj(n) for(int j = 0; j < n; ++j)
 
using namespace std;
 
vector <pair <int, int> > ans;
vector<int> a;
 
int main()
{
   // freopen("in.in.c", "r", stdin);
    int n;
    cin >> n;
    int x, y, count = 0;
    fori(n)
    {
        cin >> x >> y;
        x -= y;
        a.pb(x);
        if (x > 0)
            count++;
    }
    if (count * 2 > n)
    {
        cout << 0 << "\n";
        return 0;
    }
    fori(n - 1)
        if (a[i] <= 0 && a[i + 1] <= 0 ||
            a[i] > 0 && a[i + 1] <= 0 && a[i] + a[i + 1] > 0 ||
            a[i] <= 0 && a[i + 1] > 0 && a[i] + a[i + 1] > 0)
            ans.pb({i + 1, i + 2}),
            ++i;
    if (count * 2 <= n - ans.size())
    {
        cout << "-1\n";
        return 0;
    }
    else
    {
        int i = 0;
        while (count * 2 <= n - i)
            ++i;
        cout << i << "\n";
        forj(i)
            cout << ans[j].fst << " " << ans[j].snd << "\n";
    }
}