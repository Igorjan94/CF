#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <queue>

using namespace std;

int n, k, l, classes;
vector<int> s, c, c1, head, a, a1, temp, a_1;

template <class T>
void writeln(vector<T> &a)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
//    copy(a.begin(), a.end(), ostream_iterator<T>(cout, " "));
    printf("\n");
}

void read(string ss)
{
    int i = 0;
    char d;
    for (int j = 0; j < ss.size(); j++)
    {
        d = ss[j];
        s[i] = d - 'a' + 1;
        a[i] = i++;
    }
    s[i] = 0;
    a[i] = i++;
    n = i;
}

void radix(vector<int> &a)
{
    for (int i = 0; i < n; i++)
        head[s[a[i]] + 1]++;
    head[0] = 0;
    for (int i = 1; i < 28; i++)
        head[i] += head[i - 1];
    for (int i = 0; i < n; i++)
        temp[head[s[a[i]]]++] = a[i];
    c[a[0]] = 0;
    classes = 1;
    a = temp;
    for (int i = 1; i < n; i++)
    {
        if (s[a[i]] != s[a[i - 1]])
            classes++;
        c[a[i]] = classes - 1;
    }
}

void suffix_array(vector<int> &s)
{
    radix(a);
    for (int l = 1; l < n; l *= 2)
    {
        head.clear();
        head.resize(classes, 0);
        for (int i = 0; i < n; i++)
            head[c[a1[i] = (a[i] - l + n) % n]]++;
        for (int i = 1; i < classes; i++)
            head[i] += head[i - 1];
        for (int i = n - 1; i >= 0; i--)
            a[--head[c[a1[i]]]] = a1[i];
        classes = 1;
        c1[a[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
                classes++;
            c1[a[i]] = classes - 1;
        }
        c = c1;
    }
}

bool qq(string ss)
{
    for (int i = 0; i < ss.size(); i++)
        if (ss[i] != 'a' + i)
            return false;
    return true;
}

int main()
{
    freopen("distinct.out", "w+", stdout);
    //freopen("distinct.in", "r", stdin);
//    int m;
    //scanf("%d", &m);
    for (int m = 2; m < 40; m++)
    {
        //cout << m << "\n";
        if (m == 1)
        {
            cout << "a\n";
            return 0;
        }

        //cout << m << "\n";
        string ss = "aa";
        while (true)
        {
            n = 100;

            s.clear();
            c.clear();
            head.clear();
            a.clear();
            a1.clear();
            a_1.clear();
            c1.clear();
            temp.clear();

            s.resize(n);
            c.resize(n);
            head.resize(n);
            a.resize(n);
            a_1.resize(n + 1);
            a1.resize(n);
            c1.resize(n);
            temp.resize(n);
            read(ss);
///        cout << ss << "\n";
            suffix_array(s);
            int z = 0;
            long long ans = 0;
            for (int i = 0; i < n; i++)
                a_1[a[i]] = i;
            int i;
            for (int j = 0; j < n; j++)
            {
                i = a_1[j];
                for (; s[a[i] + z] == s[a[(i + 1) % n] + z]; z++);
                ans = ans + n - 1 - a[i] - z;
                if (z > 0)
                    z--;
            }
//        cout << ans << "\n";
            if (ans == m)
            {
                cout << ss << "\n";
                break;
            }
            if (qq(ss))
            {
                int h = ss.size() + 1;
                ss = "";
                for (int g = 0; g < h; g++)
                    ss.push_back('a');
            }
            else
            {
                if (ss[ss.size() - 1] == ss[ss.size() - 2] + 1)
                {
                    int i = ss.size() - 1;
                    while (i >= 1 && ss[i - 1] == ss[i] - 1)
                        ss[i--] = 'a';
                    ss[i]++;
                }
                else
                    ss[ss.size() - 1]++;
            }
        }
    }
    return 0;
}
