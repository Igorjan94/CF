n = int(input())
n2 = n // 2
n12 = (n + 1) // 2
alleven = n2 * (n2 - 1) * (n2 - 2) // 6
evennoteven = n2 * n12 * (n12 - 1) // 2
print(alleven + evennoteven)
