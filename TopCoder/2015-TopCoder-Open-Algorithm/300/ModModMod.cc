#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)

using namespace std;

class ModModMod 
{
    set<int> ss;
    long long f(long long x)
    {
        auto temp = ss.lower_bound(-x);
        if (temp == ss.end())
            return x;
        return f(x % (-*temp));
    }
public:
    long long findSum(vector <int> m, int R) 
    {
        int n = m.size();
        long long ans = 0;
        int last = m[0];
        ss.insert(-last);
        for (int i = 1; i < n; ++i)
            if (m[i] < last)
                ss.insert(-m[i]),
                last = m[i];
        fori(R + 1)
            ans += f(i);
        return ans;
    }
};
