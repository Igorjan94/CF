t = int(input())
for i in range(t):
    x = sum(map(int, input().split())) + 1
    print(1 if x > 50 else x)
