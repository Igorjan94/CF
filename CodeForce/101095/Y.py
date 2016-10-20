def f(): return list(map(int, input().split()))

n, t = f()
e = f()[0]
cities = []
ans = [0] * n
ok = 0
for i in range(n):
    cities.append([])
for i in range(e):
    h, p = f()
    cities[h - 1].append(p)

for i in range(n):
    cities[i] = list(reversed(sorted(cities[i])))
    if i + 1 == t:
        cities[i] = []
        continue
    j = 0
    while j < len(cities[i]) and cities[i][j] > 0:
        if cities[i][j] > 1:
            cities[i] = cities[i][:-(cities[i][j] - 1)]
            # print(cities[i])
        j += 1
    if j < len(cities[i]):
        ok += 1
    ans[i] = j

if ok == 0:
    print(' '.join(map(str, ans)))
else:
    print("IMPOSSIBLE")
