#include <bits/stdc++.h>
using namespace std;

void run()
{
    string s;
    cin >> s;
    vector<int> a(26, 0);
    int prev = -1;
    int n = s.size();
    for (int i = 0; i < n; ++i)
        a[s[i] - 'a']++;
    if (*max_element(a.begin(), a.end()) > (n + 1) / 2)
    {
        cout << "IMPOSSIBLE" << "\n";
        return;
    }
    for (int q = n; q > 0; --q)
    {
        int i = max_element(a.begin(), a.end()) - a.begin();
        if ((q & 1) == 0 || a[i] != (q + 1) / 2)
        {
            for (i = 0; !a[i]; i++);
            if (i == prev)
                for (++i; i < 26 && !a[i]; ++i);
        }
        cout << (char) (i + 'a');
        a[i]--;
        prev = i;
    }
    cout << "\n";
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        run();
    return 0;
}
