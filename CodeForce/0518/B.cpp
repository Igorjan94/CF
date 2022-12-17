//Igorjan94, template version from 16 February 2015
#include <bits/stdc++.h>

using namespace std;
#define count asasdaiusdyfoiuqwfd
int count[300];

int main()
{
    string s, t;
    cin >> s >> t;
    for (char c : s)
        count[c]++;
    int ura = 0, zopa = 0;
    for (char& c : t)
        if (count[c])
            ura++,
            count[c]--,
            c = 0;
    for (char c : t)
        if (c && count[c ^ 32])
            zopa++,
            count[c ^ 32]--;
    cout << ura << " " << zopa;
    return 0;
}
