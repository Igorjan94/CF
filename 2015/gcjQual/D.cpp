#include <bits/stdc++.h>

std::string ans[2] = {"GABRIEL", "RICHARD"};

int main()
{
    int t, x, n, m;
    std::cin >> t;
    for (int test = 0; test < t; )
    {
        std::cin >> x >> n >> m;
        if (n > m)
            std::swap(n, m);
        std::cout << "Case #" << ++test << ": " << ans[((n * m) % x != 0) || (n < x && m < x) || (x > 6) || (n <= x - 2)] << "\n";
    }
}
