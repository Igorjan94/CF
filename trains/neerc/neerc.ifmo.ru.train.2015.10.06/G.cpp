#include <stdio.h>
#include <iostream>
#include <map>
#define problem "log"
 
using namespace std;
 
#define ll long long
 
ll mul(ll a, ll b, ll mod)
{
    ll c = 0;
 
    for (; b > 0; b /= 2)
    {
        if (b % 2 == 1)
        {
            c = (c + a) % mod;
        }
        a = (a + a) % mod;
    }
 
    return c;
}
 
ll pow(ll a, ll b, ll mod)
{
    ll c = 1;
 
    for (; b > 0; b /= 2)
    {
        if (b % 2 == 1)
        {
            c = mul(c, a, mod);
        }
 
        a = mul(a, a, mod);
    }
    return c;
}
 
ll phi(ll n)
{
    ll p = 1;
 
    for (ll d = 2; d*d <= n; d++)
    {
        if (n % d == 0)
        {
            ll q = 1;
            while (n % d == 0)
            {
                n /= d;
                q *= d;
            }
 
            p *= q - (q / d);
        }
    }
 
    return p;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    freopen(problem".in", "r", stdin);
    freopen(problem".out", "w", stdout);
 
 
    ll a, b, n;
    cin >> a >> b >> n;
    ll m = 0;
 
 
    a = a % n;
    b = b % n;
 
 
    if (n <= 200)
    {
 
        for (ll x = 0; x <= n ; x++)
        {
            if (pow(a, x, n) == b)
            {
                cout << x << "\n";
                return 0;
            }
        }
        cout << -1 << "\n";
        return 0;
    }
 
    for (ll x = 0; x <= 20 ; x++)
        {
            if (pow(a, x, n) == b)
            {
                cout << x << "\n";
                return 0;
            }
        }
 
    if (a == 0)
    {
        if (b == 0) {
            cout << 0 << "\n";
        } else {
            cout << -1 << "\n";
        }
        return 0;
    }
 
    if (b == 1)
    {
        cout << 0 << "\n";
        return 0;
    }
 
    if (a == b)
    {
        cout << 1 << "\n";
        return 0;
    }
 
    while (m * m <= n)
    {
        ++m;
    }
 
    map<ll, ll> q;
 
    ll am = pow(a, m, n);
 
    ll amx = 1;
 
    for (ll x = 0; x <= m; x++)
    {
        q[amx] = x;
        amx = mul(amx, am, n);
    }
 
    ll bay = b;
    auto it = q.begin();
    for (ll y = 0; y <= m; y++)
    {
        if ((it = q.find(bay)) != q.end())
        {
            ll z = (it->second) * m - y;
 
            if (0 <= z && z <= n)
            {
                if (pow(a, z, n) == b)
                {
                    cout << z << "\n";
                    return 0;
                }
            }
        }
 
        bay = mul(bay, a, n);
 
    }
    cout << "-1\n";
 
    return 0;
}