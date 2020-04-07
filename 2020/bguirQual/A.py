n = int(input())
print('Yes' if len(bin(n).replace('0', '')) == 2 and n > 1 else 'No')
