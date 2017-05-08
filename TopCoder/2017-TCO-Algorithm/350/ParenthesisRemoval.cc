#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)

using namespace std;


class ParenthesisRemoval 
{
public:
    int MOD = 1000000007;
    int countWays(string s) 
    {
        int n = s.size();
        int ans = 1;
        int b = 0;
        fori(n)
        {
            if (s[i] == '(')
                b++;
            else
                ans = (ans * 1ll * b) % MOD,
                --b;
        }
        return ans;
    }
};
