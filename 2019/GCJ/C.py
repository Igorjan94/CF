import math
import sys

def main():
    n, l = map(int, input().split())
    a = list(map(int, input().split()))
    b = [0] * (l + 1)
    for i in range(l - 1):
        if a[i] != a[i + 1]:
            pi = math.gcd(a[i], a[i + 1])
            b[i + 1] = pi
            for j in range(i, -1, -1):
                b[j] = a[j] // b[j + 1]
            for j in range(i + 2, l + 1):
                b[j] = a[j - 1] // b[j - 1]
    c = list(sorted(list(set(b))))
    d = {}
    if len(c) != 26:
        sys.exit(1)
    for i in range(len(c)):
        d[c[i]] = chr(ord('A') + i)
    print(''.join(map(lambda x: d[x], b)))

for t in range(int(input())):
    sys.stdout.write("Case #{}: ".format(t + 1))
    main()
