#include <bits/stdc++.h>
#include <iostream>
#include <future>

using namespace std;

int n = 100;
vector<long long> ans;

long long f(int a, int index)
{
    long long res = a;
    for (int i = 0; i < 10e7; i++)
        res += i;
    ans[index] = res;
    return res;
}

int main()
{
    ans.resize(n);
    vector<future<long long>> fff;
    for (int i = 0; i < n; i++)
        fff.push_back(async(f, i, i));
    for (int i = 0; i < fff.size(); i++)
        printf("Case %d: %lld\n", i, fff[i].get());
    printf("\n");
    return 0;
}
