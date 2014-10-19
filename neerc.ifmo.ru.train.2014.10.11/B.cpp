#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
 
using namespace std;
 
 
int a[500000], t[1000000];
 
 
void run()
{
    int w, h, n, x;
    cin >> h >> w >> n;
    h = min (h, n);
    int two = 2;
    while (two < h)
        two *= 2;
    for (int i = 0; i < h; ++i){
        a[i] = w;
    }
    for (int i = h; i < two; ++i)
        a[i] = 0;
    for (int i = two - 1; i < two * 2 - 1; ++i)
        t[i] = a[i - two + 1];
 
    for (int i = two - 2; i >= 0; --i)
        t[i] = max(t[2 * i + 1], t[2 * i + 2]);
 
    for (int i = 0; i < n; ++i){
        cin >> x;
        int rq = 0;
        if (t[rq] < x){
            cout << -1 << endl;
            continue;
        }
        while (rq < two - 1){
            int to = 2 * rq + 2;
            if (t[2 * rq + 1] >= x)
                to = 2 * rq + 1;
            rq = to;
   //         cout << rq << endl;
        }
        t[rq] -= x;
        cout << rq - two + 2 << endl;
        rq = (rq - 1) / 2;
        while (rq){
            t[rq] = max(t[2 * rq + 1], t[2 * rq + 2]);
            rq = (rq - 1) / 2;
        }
        t[rq] = max(t[2 * rq + 1], t[2 * rq + 2]);
 
 
    }
 
}
 
int main()
{
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);
    run();
    return 0;
}