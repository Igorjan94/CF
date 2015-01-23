import sys

for q in range(int(input())):
    [n, k] = list(map(int, input().split()))
    x = True
    for i in range(100):
        if (k ** i) % n == 0:
            print(i)
            x = False
            break
    if x:
        print(-1)
