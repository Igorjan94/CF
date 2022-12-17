#include <iostream>

int main()
{
    float x = 0;
    int n = 0;
    std::cout.precision(8);
    while (true)
    {
        n++;
        x += 1.0 / n;
        if (n % 100000 == 0)
            std::cout << x << "\n" << "n == " << n << "\n";
    }
}
