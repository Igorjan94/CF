q1, p1, q2, p2, a = map(int, input().split())
ans = 2 ** 60
for i in range(a + 1):
    ans = min(ans, (i // q1 + (i % q1 != 0)) * p1 + ((a - i) // q2 + ((a - i) % q2 != 0)) * p2)
print(ans)
