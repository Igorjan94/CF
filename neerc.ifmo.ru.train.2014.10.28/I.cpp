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
 
int main() {
//    freopen(TASKNAME".in", "r", stdin);
//    freopen(TASKNAME".out", "w", stdout);
    int n;
    cin >> n;
    vi a(n);
    fori(n)
        cin >> a[i];
    sort(all(a));
    int i = 0;
    ll sum = 0;
    while (i < n - 1 && a[i] + sum <= a.back())
        sum += a[i++];
    cout <<  i + 1 << "\n";
    return 0;
}