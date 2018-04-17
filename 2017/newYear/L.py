s = list(input())
carry = True
l = len(s)
for i in range(l):
    if s[l - i - 1] != '0':
        s[l - i - 1] = '0'
    else:
        s[l - i - 1] = '1'
        carry = False
        break

if carry:
    s = ['1'] + s
print(''.join(s))
