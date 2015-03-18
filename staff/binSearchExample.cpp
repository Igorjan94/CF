#include "library.h"

int main()
{
    auto f = [](int x)
    {
        return power(x + 123, 3);
    };
    cout << fixed << (bin_search(-1000, 1000, [&f](int m)
        {
            return f(m) > 0;
        }, 1)) << "\n";
    return 0;
}
