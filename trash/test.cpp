#include <iostream>

using namespace std;

void sort(int*);

int main() {
    int a[12];
    int min; cin >> min;
    for (int i = 0; i < 12; i++)
        cin >> a[i];
    sort(a);
    int s = 0;
    int c = 0;
    while (s < min) {
        s += a[c++];
    }
    if (c > 12)
        c = -1;
    cout << c << endl;
    return 0;
}

void sort(int *a) {
    for (int i = 1; i < 12; i++) {
        for (int j = 0; j < 12-i; j++)
            if (a[j] < a[(j+1)]) {
                int temp = a[j];
                a[j] = a[(j+1)];
                a[(j+1)] = temp;
            }
    }
}
