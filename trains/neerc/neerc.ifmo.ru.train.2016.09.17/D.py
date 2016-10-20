f = open("input.txt", "r")
n = int(f.readline())
x = {'Emperor Penguin': 0, 'Macaroni Penguin': 0, 'Little Penguin': 0}
for i in range(n):
    x[f.readline()[:-1]] += 1

mx = -1
ans = ''
for y in x:
    if x[y] > mx:
        mx = x[y]
        ans = y

open("output.txt", "w").write(ans)
