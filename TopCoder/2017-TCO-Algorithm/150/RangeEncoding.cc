#include <bits/stdc++.h>

#define fori(n) for(int i = 0; i < (int) (n); i++)
#define forj(n) for(int j = 0; j < (int) (n); j++)

using namespace std;

class RangeEncoding 
{
public:
    int minRanges(vector <int> arr) 
    {
        int ans = 1;
        for (int i = 1; i < arr.size(); ++i)
            if (arr[i] != arr[i - 1] + 1)
                ans++;
        return ans;
    }
};
