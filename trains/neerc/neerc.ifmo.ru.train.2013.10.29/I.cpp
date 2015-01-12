#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct tri
{
    int x, y, i;
    tri(){}
    tri(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->i = z;
    }
    bool operator<(tri const& a) const
    {
        if (y == a.y)
            return x < a.x;
        return y < a.y;
    }
};

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, a, b;
    scanf("%d %d %d\n", &n, &a, &b);

    vector<tri> a1, a2, a3, a4;
    int x, y;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x ,&y);
        a1.push_back(tri(x, y, i + 1));
    }
    sort(a1.begin(), a1.end());
    long long count = 0;
    for (int i = 0; i < a1.size(); i++)
    {
        if (a1[i].x == 1)
            if (a2.size() < a && a2.size() + a3.size() + a4.size() < a + b)
                a2.push_back(a1[i]),
                count += a1[i].y;
        if (a1[i].x == 2)
            if (a3.size() < b && a2.size() + a3.size() + a4.size() < a + b)
                a3.push_back(a1[i]),
                count += a1[i].y;
        if (a1[i].x == 3)
            if (a2.size() + a3.size() + a4.size() < a + b)
                a4.push_back(a1[i]),
                count += a1[i].y; else
                break;
    }
    cout << a2.size() + a3.size() + a4.size() << " " << count << endl;
    int k = 1;
    for (int i = 0; i < a2.size(); i++, k++)
        printf("%d %d\n", a2[i].i, k);
    int j = 0;
    for (int i = 0; i < min(a - a2.size(), a4.size()); i++, j++, k++)
        printf("%d %d\n", a4[i].i, k);
    k = max(a + 1, k);
    for (int i = 0; i < a3.size(); i++, k++)
        printf("%d %d\n", a3[i].i, k);
    for (int i = j; i < a4.size(); i++, k++)
        printf("%d %d\n", a4[i].i, k);

    return 0;
}
