#include <stdio.h>
#include <vector>

using namespace std;

vector<vector<int>> b;
int n, m, k, s1, s2;

void bfs(int i, int j)
{
    if (b[i][j] || !k)
        return;
    k--;
    b[i][j] = 2;
    bfs(i + 1, j);
    bfs(i - 1, j);
    bfs(i, j + 1);
    bfs(i, j - 1);
}

int main()
{
    scanf("%d %d %d\n", &n, &m, &k);
    k = -k;
    b.resize(n + 2);
    for (int i = 0; i <= n + 1; i++)
        b[i].resize(m + 2, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m + 1; j++)
            if (!(b[i][j] = (int)(getchar() != '.')))
                k++,
                s1 = i,
                s2 = j;
    bfs(s1, s2);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            putchar(b[i][j] == 0 ? 'X' : b[i][j] == 1 ? '#' : '.');
        printf("\n");
    }
    return 0;
}
