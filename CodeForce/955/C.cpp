#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long  ll;

ll sss(ll x)
{
    ll temp = sqrt(x) - 1;
    while ((temp + 1) * (temp + 1) <= x)
        ++temp;
    return temp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    ll q, l, r;
    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> s;
    for (ll i = 2; i <= 1000000; ++i)
        for (ll x = i * i; ; x *= i)
        {
            if (ll temp = sss(x); temp * temp != x)
                s.insert(x);
            if (double(x) * i >= 1000000000000000001ll)
                break;
        }
    for (cin >> q; q > 0; --q)
        cin >> l >> r,
        cout << sss(r) - sss(l - 1) + s.order_of_key(r + 1) - s.order_of_key(l) << "\n";
    return 0;
}
