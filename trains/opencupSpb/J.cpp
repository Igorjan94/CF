#include <bits/stdc++.h>

#define fori(n) for (int i = 0; i < n; ++i)
#define print fori(n) cout << f[i] << "\n"; cout.flush();
#define scan fori(n) cin >> f[i];

using namespace std;

int main()
{
    int n = 3;
    vector<string> f(n);
    while (true)
    {
        scan;
        bool end = true;
        fori(n)
            end &= f[i] == "xxx";
        if (end)
            break;
        f[1][1] = 'x';
        print;
        scan;
        if (f[0][1] == 'o' || f[1][0] == 'o' || f[2][1] == 'o' || f[1][2] == 'o')
        {
            /*
               .o. ... ... ...
               .x. ox. .xo .x.
               ... ... ... .o.
            */
            f[0][0] = 'x';
            /*
                x?.
                ?x?
                .?.
            */
            print;
            scan;
            if (f[2][2] != 'o')
            {
                f[2][2] = 'x';
                print;
            } 
            else
            {
            /*
                x?.
                ?x?
                .?o
            */
                f[1][0] == 'o' || f[2][0] == 'o' ? f[0][2] = 'x' : f[2][0] = 'x';
                print;
                scan;
            /*
                x.x x.x    xo. x..
                ox. .xo || .x. .x.
                ..o ..o    x.o xoo
            */
                if (f[0][2] == '.' || f[2][0] == '.')
                {
                    f[2][0] = f[0][2] = 'x';
                    print;
                }
                else
                {
                    f[0][2] == 'o' ? f[1][0] = 'x' : f[0][1] = 'x';
                    print;
                }
            }
        } 
        else
        {
            f[0][0] == 'o' || f[2][2] == 'o' ? f[0][2] = 'x' : f[0][0] = 'x';
            print;
            scan;
            if (f[0][0] == 'x')
            {
                if (f[2][2] != 'o')
                {
                    f[2][2] = 'x';
                    print;
                } else
                {
                    if (f[2][0] == 'o')
                    {
                    /*
                        x.o
                        .x.
                        ..o
                    */
                        f[0][1] = 'x';
                        print;
                        scan;
                        f[0][2] == '.' ? f[0][2] = 'x' : f[2][1] = 'x';
                        print;
                    }
                    else
                    {
                    /*
                        x..
                        .x.
                        o.o
                    */
                        f[1][0] = 'x';
                        print;
                        scan;
                        f[2][0] == '.' ? f[2][0] = 'x' : f[1][2] = 'x';
                        print;
                    }
                }
            } else
            {
                if (f[2][0] != 'o')
                {
                    f[2][0] = 'x';
                    print;
                } else
                {
                    if (f[2][2] == 'o')
                    {
                    /*
                        x.o
                        .x.
                        ..o
                    */
                        f[0][1] = 'x';
                        print;
                        scan;
                        f[0][0] == '.' ? f[0][0] = 'x' : f[2][1] = 'x';
                        print;
                    }
                    else
                    {
                    /*
                        x..
                        .x.
                        o.o
                    */
                        f[1][2] = 'x';
                        print;
                        scan;
                        f[2][2] == '.' ? f[2][2] = 'x' : f[1][0] = 'x';
                        print;
                    }
                    
                }
            }
        }
    }
    return 0;
}
