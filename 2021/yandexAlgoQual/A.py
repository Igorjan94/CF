def convert(x):
    return int(x.replace('one', '1').replace('zero', '0'), 2)


a = convert(input())
b = convert(input())

if a == b:
    print('=')
elif a < b:
    print('<')
else:
    print('>')

