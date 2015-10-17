n, k = map(int, input().split())
a = [0] * k
r = map(int, input().split())
for x in r:
    a[x - 1] += 1
ans = 0
k = n // k
for x in a:
    ans += abs(x - k)
print(ans // 2)

