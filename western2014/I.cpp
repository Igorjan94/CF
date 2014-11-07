#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

const int MaxN = 1239;


int a[MaxN][MaxN];

int n, k;
int main()
{
    cin >> k >> n;
    if (!(k - 1)){
        int sum = 0, mx = -1, x;
        for (int i = 0; i < n; ++i){
            cin >> x;
            mx = max(mx, x);
            sum += x;
        }
        sum += mx;
        cout << sum;
        return 0;
    }


    int x;
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[j][i];
    for (int i = 0; i < n; ++i)
        sort(a[i], a[i] + k);


    int maxi = -1, d = -1;
    for (int i = 0; i < n; ++i){
        int nxt = min (2 * a[i][0], a[i][1]);
        if (d < nxt - a[i][0]){
            maxi = i;
            d = nxt - a[i][0];
        }
    }
    a[maxi][0] *= 2;
    if (a[maxi][0] > a[maxi][1])
        swap (a[maxi][0], a[maxi][1]);
    int sum = 0;
    for (int i = 0; i < n; ++i){
        sum += a[i][0];
    }

    cout << sum;


}