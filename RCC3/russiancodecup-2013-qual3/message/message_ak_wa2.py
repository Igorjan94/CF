t = int(input())

MOD = 10**9 + 7

def count(f, a):
    return sum(1 if f(x) else 0 for x in a)

for i in range(t):
    s = input().strip()
    n = len(s) // 2
    a, b = s[:n], s[n:]
    qq = count(lambda x: x == ('?', '?'), zip(a, b))
    err = count(lambda x: x == ('a', 'b') or x == ('b', 'a'), zip(a, b))
    q = s.count('?')
    if err:
        print (pow(2, q, MOD))
    else:
        all = pow(2, q, MOD)
        good = 1 if qq == 0 else pow(2, qq // 2 + 1, MOD)
        print ((all - good) % MOD)
