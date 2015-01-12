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
 
const double EPS = 1e-9;
const int INF = 1e9;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
 
struct tri
{
    ll x;
    bool f;
    int i;
    tri(ll x, bool a, int q)
    {
        this->x = x;
        f = a;
        i = q;
    }
 
    bool operator<(tri const& a) const
    {
        if (x != a.x)
            return x < a.x;
        return f > a.f;
    }
};
 
int main() {
  //  freopen("in.in.c", "r", stdin);
//    freopen(TASKNAME".out", "w", stdout);
    int n;
    ll m;
    cin >> n >> m;
    vector<tri> a;
    ll x;
    int y;
    fori(n)
        cin >> x >> y,
        a.pb(tri(x, y == 1, i + 1));
    sort(a.rbegin(), a.rend());
   // fori(n)
  //      cout << a[i].x << " " << a[i].f << " " << a[i].i << "\n";
    int i = 0;
    ll sum = 0;
    int count = 0;
    while (i < n && sum < m)
        count += a[i].f,
        sum += a[i++].x;
 
 
    int l = i - 1;
    int r = i;
    while (true){
        while (l + 1 && a[l].f)
            l--;
        while (r < n && !a[r].f)
            r++;
    //    cout << l << " " << r << endl;
        if (l <= -1 || r >= n)
            break;
        if (!a[l].f && a[r].f && sum - a[l].x + a[r].x >= m){
            sum = sum - a[l].x + a[r].x;
            swap (a[l], a[r]);
            count++;
            l--;
            r++;
        }
        else
            break;
    }
    cout << i << " " << count << "\n";
    forj(i)
        cout << a[j].i << " ";
    return 0;
}