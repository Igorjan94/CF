#include <bits/stdc++.h>
 
#define fori(n) for (int i = 0; i < n; ++i)
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)
 
#define fst first
#define snd second
#define pb push_back
 
using namespace std;
 
int main()
{
    //freopen("in.c", "r", stdin);
    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
            return 0;
        string s;
        int m;
        int count = 0, ans = 0;
        fori(n)
        {
            cin >> s >> m;
            if (s[0] == 'D')
            {
                count += m;
                cout << "DROP 2 " << m << "\n";
            }
            else
            {
                int c = min(m, ans);
                if (ans)
                    cout << "TAKE 1 " << c << "\n";
                m -= c;
                ans -= c;
                if (m)
                {
                    cout << "MOVE 2->1 " << count << "\n";
                    ans += count;
                    count = 0;
                    cout << "TAKE 1 " << m << "\n";
                    ans -= m;
                }
            }
        }
        cout << "\n";
    }
}