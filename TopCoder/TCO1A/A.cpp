#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)

using namespace std;
class Similars 
{
public:
    int maxsim(int L, int R) 
    {
        int ans = 0;
        set<int> a;
        for (int i = L; i <= R; i++)
        {
            int j = i;
            int temp = 0;
            while (j >= 10)
                temp |= (1 << (j % 10)),
                j /= 10;
            temp |= (1 << j);
            if (a.find(temp) != a.end())
                ans = max(ans, __builtin_popcount(temp));
            a.insert(temp);
        }
        for (auto x : a)
            for (auto y : a)
                if (x != y)
                    ans = max(ans, __builtin_popcount(x & y));
        return ans;
    }
};
