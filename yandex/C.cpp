#include <iostream>
#include <stdio.h>

using namespace std;

string a, s = "0000";

int findd(int k, char c) {
    for (int i = k; i < 8; i++)
        if (a[i] == c)
            return i;
    return -1;
}

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    cin >> a;
    int k = 0, prev = 0;
    for (int i = 0; i < 4; i++) {
        while (findd(k, s[i]) == -1)
            s[i]++;
        prev = k;
        k = findd(k, s[i]) + 1;
        if (8 - k + 1 < 4 - i) {
            s[i--]++;
            k = prev;
            continue;
        }
    }
    cout << s << "\n";
    return 0;
}
