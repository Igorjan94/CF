n = int(input())
l = [0] * n
r = [0] * n
c = [0] * n
for i in range(n):
    l[i], r[i] = map(int, input().split())
m = int(input())
for i in list(map(int, input().split())):
    c[i - 1] += 1
for i in range(n):
    print("Red" if c[i] > r[i] else ("Orange" if c[i] >= l[i] else "Green"))
