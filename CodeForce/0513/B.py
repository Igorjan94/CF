[n, m] = list(map(int, input().split()))
a = [0] * n
l = 0
r = n
m -= 1
for i in range(1, n + 1):
    deg = 1 << max(n - i - 1, 0)
    if m >= deg:
        m -= deg
        r -= 1
        a[r] = i
    else:
        a[l] = i
        l += 1
print(' '.join(str(x) for x in a))
