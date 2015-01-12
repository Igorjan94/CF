T = int(input())
for TT in range(T):
    n, m, p, q, t = map(int, input().split())
    k = n % (t / p)
    z = m % (t / q)
    print(1 + n / (t / p) + m / (t / q) - (k == 0) - (z == 0) + ((t / p, k)[k == 0] * p + (t / q, z)[z == 0] * q > t))
