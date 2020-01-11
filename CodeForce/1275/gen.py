n = 2 * 10 ** 5
q = 10 ** 5
print(n, q)
print(*list(i for i in range(n)))
for i in range(q):
    print(0, n - 5, i % 256, (i + 1) % 256, (i + 2) % 256, (i + 3) % 256)
