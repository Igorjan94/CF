a = input().split()
for i in range(int(input())):
    print("Unlucky" if sum([1 if x in a else 0 for x in input().split()]) < 3 else "Lucky")
