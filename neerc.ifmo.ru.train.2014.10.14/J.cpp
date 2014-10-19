#include <iostream>
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
long long res = 0, ost = 0;
 
int inf = 1e+9 + 9;
 
int pow (int x, int k){
    long long res = 1;
    for (int i = 0; i < k; ++i){
        res *= x;
        if (res >= inf)
            return inf;
    }
    int c = res;
    return c;
}
 
int next(int x, int k){
    int l = 1;
    int r = x + 1;
    int m = (l + r) / 2;
    while (r > l + 1){
        m = (r + l) / 2;
        if (pow(m, k) > x)
            r = m;
        else
            l = m;
    }
    res = l;
}
 
int sz[100500];
int dp[100500];
int ans[100500];
 
 
int n;
int main(){
    freopen("cube.in", "r", stdin);
    freopen("cube.out", "w", stdout);
    cin >> n;
    for (int k = 2; k <= 10; ++k){
        sz[0] = 0;
        dp[0] = 0;
        ans[0] = 0;
        sz[1] = 1;
        dp[1] = 1;
        ans[1] = 1;
 
        for (int i = 2; i <= n; ++i){
            sz[i] = inf;
            int cr = next(i, k);
            for (int j = 1; j <= cr; ++j){
                int gg = pow(j, k);
                if (sz[i - gg] + 1 < sz[i]){
                    sz[i] = sz[i - gg] + 1;
                    dp[i] = i - gg;
                    ans[i] = j;
                }
            }
        }
 
        cout << sz[n] << " ";
        int q = n;
        for (int i = 0; i < sz[n]; ++i){
            cout << ans[q] << " ";
            q = dp[q];
        }
        cout << endl;
 
    }
}