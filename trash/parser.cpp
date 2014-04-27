#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string s;
    while (getline(cin, s))
    {
        if (s == "\n")
            continue;
        int k = s.find("\"");
        cout << s.substr(0, k) << endl;
    }
    return 0;
}
