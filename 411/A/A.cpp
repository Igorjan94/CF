#include <bits/stdc++.h>

using namespace std;

#define N 101
int n, m, k, x;
int a[N][N];
int dead[N];
int ans[N];

int main()
{
    scanf("%d %d %d\n", &n, &m, &k);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    for (int j = 0; j < m; j++)
        for (int h = 1, c = 0; h <= k; h++)
            if (!dead[h])
            {
                for (int i = 0; i < n; i++)
                {
                    if (a[i][j] == h)
                        c++;
                    if (dead[a[i][j]])
                        if (!ans[i])
                            ans[i] = j;
                }
                if (c > 1)
                {
                    for (int i = 0; i < n; i++)
                        if (a[i][j] == h)
                            if (!ans[i])
                                ans[i] = j;
                    dead[h] = 1;
                }
            }
    for (int i = 0; i < n; i++)
        printf("%d\n", ans[i]);
}
