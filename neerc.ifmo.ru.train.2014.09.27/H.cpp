#include <bits/stdc++.h>
using namespace std;
 
 
bool seg_cross (pair <int, int> p1, pair <int, int> p2){
    int x = p1.first, y = p1.second, x2 = p2.first, y2 = p2.second;
    return ((x < x2 && x2 < y) || (x < y2 && y2 < y) || (x2 < x && x < y2) || (x2 < y && y < y2));
}
 
bool f1[100239], f2[100239];
vector <pair <int, int> > a, a1;
pair <int, int> seg [100239];
 
int scan(vector <pair <int, int> > a)
{
    int ans = 0, curr = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); ++i) {
        curr += a[i].second;
        ans = max (ans, curr);
    }
    return ans;
}
 
int main() {
   //     freopen("input.in.c", "r", stdin);
   int t, n;
    cin >> t;
    while (t --> 0){
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> seg[i].first >> seg[i].second;
        bool ok = seg_cross(seg[0], seg[1]);
        for (int i = 2; i < n; ++i){
            f1[i] = seg_cross(seg[0], seg[i]);
            f2[i] = seg_cross(seg[1], seg[i]);
        }
        bool _f1 = false, _f2 = false;
        for (int i = 2; i < n; ++i){
            if (f1[i] && !f2[i])
                _f1 = true;
            if (!f1[i] && f2[i])
                _f2 = true;
        }
        ok = (ok || (_f1 && _f2));
        for (int i = 0; i < n; ++i){
            a.push_back(make_pair(seg[i].first, 1));
            a.push_back({seg[i].second, -1});
            a1.push_back(make_pair(seg[i].first, 1));
            a1.push_back({seg[i].second, -1});
        }
     //   cout << "pwqw       " << scan(a) << endl;
        if (ok)
            cout << scan(a) << endl;
        else {
            a.push_back({seg[0].first, 1});
            a.push_back({seg[0].second, -1});
            int temp = scan(a);
            a1.push_back({seg[1].first, 1});
            a1.push_back({seg[1].second, -1});
            cout << min(temp, scan(a1)) << endl;
        }
        a.clear();
        a1.clear();
    }
}