t = int(input())
for tt in range(t):
    n = int(input())
    a = sorted(map(int, input().split()))
    print (sum(a[n//2:]) - sum(a[:n//2]))
    
