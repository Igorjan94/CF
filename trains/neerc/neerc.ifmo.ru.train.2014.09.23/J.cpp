#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

const int MAXN = 500002;
string s;
int n, gap;
int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

bool sufCmp(int i, int j)
{
    if (pos[i] != pos[j])
        return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < n && j < n) ? pos[i] < pos[j] : i > j;
}

void buildsA()
{
    n = s.size();
//    s.push_back('!');
    REP(i, n)
        sa[i] = i,
        pos[i] = s[i];
    for (gap = 1;; gap *= 2)
    {
        sort(sa, sa + n, sufCmp);
        REP(i, n - 1)
            tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
        REP(i, n)
            pos[sa[i]] = tmp[i];
        if (tmp[n - 1] == n - 1)
            break;
    }
}

void buildLCP()
{
    for (int i = 0, k = 0; i < n; ++i)
        if (pos[i] != n - 1)
        {
            for (int j = sa[pos[i] + 1]; max(i + k, j + k) < n && s[i + k] == s[j + k];)
                ++k;
            lcp[pos[i]] = k;
            if (k)
                --k;
        }
}

int main()
{
    //freopen("input.in", "r", stdin);
    int z;
    std::cin >> z;
    if (z == 1)
    {
        printf("0");
        return 0;
    }
    std::cin >> s;
    int countP = 0, countL = 0, posP = -1, posL = -1;
    REP(i, s.size())
        s[i] == 'L' ? countL++, posL = i : (countP++, posP = i);
    buildsA();
    buildLCP();
    int pos[MAXN];
    REP(i, n)
        pos[sa[i]] = i;
    int ans[MAXN];
    REP(i, n - 1)
        if (pos[i] == 0)
            ans[i] = lcp[pos[i]];
        else
            ans[i] = max(lcp[pos[i]], lcp[pos[i] - 1]);
    ans[n - 1] = 1;
    if (countL == 1)
        ans[posL] = 0;
    if (countP == 1)
        ans[posP] = 0;
    REP(i, n)
        printf("%d\n", ans[i]);
    return 0;
}
