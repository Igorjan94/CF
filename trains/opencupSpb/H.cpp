#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll go(ll temp)
{
    for (int k = 2; k <= temp; ++k)
    {
        if (temp % k == 0)
            return -1;
        temp -= temp / k;
    }
    return temp;
}

int main()
{
    int t;
    ll x;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cin >> x;
        cout << go(x) << "\n";
    }
    return 0;
}
