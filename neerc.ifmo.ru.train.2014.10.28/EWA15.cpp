#define TASKNAME ""
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int MaxN = 4 * 100000;
int a[MaxN];
 
 
vector <pair <int, int> > ans;
int main()
{
   // freopen("in.in.c", "r", stdin);
    int n, p = 0, q = 0;
    cin >> n;
    q = n;
    for (int i = 0; i < n; ++i){
        int x, y;
        cin >> x >> y;
        a[i] = x - y;
        if (a[i] > 0)
            p++;
    }
    int s = q - 2 * p;
    s++;
    if (s <= 0){
        cout << 0;
        return 0;
    }
    for (int ok = 0; ok < n - 1; ++ok){
        if (a[ok] <= 0 && a[ok + 1] <= 0){
            ok++;
            ans.push_back({ok - 1, ok});
        } else
        if (a[ok] <= 0 && a[ok + 1] > 0 && (a[ok] + a[ok + 1] > 0)){
            ok++;
            ans.push_back({ok - 1, ok});
        } else
        if (a[ok + 1] <= 0 && a[ok] > 0 && (a[ok] + a[ok + 1] > 0)){
            ok++;
            ans.push_back({ok - 1, ok});
        }
    }
    if (ans.size() < s)
        cout << -1;
    else
    {
        cout << s << endl;
        for (int i = 0; i < s; ++i){
            cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
        }
    }
 
//    freopen(TASKNAME".out", "w", stdout);
}