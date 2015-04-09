#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)
#define INF 1000000007

using namespace std;

class FoldingPaper2 
{
public:
    int solve(int w, int h, int A) 
    {
        auto f = [](int i, int j, int w, int h){
            int ans = 0;
            if (w < i || h < j)
                return INF;
            while (i * 2 <= w)
                w = (w + 1) / 2,
                ans++;
            while (j * 2 <= h)
                h = (h + 1) / 2,
                ans++;
            if (i < w)
                ans++;
            if (j < h)
                ans++;
            return ans;
        };
        int ans = INF;
        fori(A + 1)
            if (i && (A % i == 0))
                ans = min(ans, f(A / i, i, w, h));
        return ans == INF ? -1 : ans;
    }
};
