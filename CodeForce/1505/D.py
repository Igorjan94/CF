n, m = map(int, input().split())
a = []
while n > 0:
    a.append(n % m)
    n //= m
print("YES" if len(set(a)) == len(a) else "NO")

