m = 30000
n = 256
v = 0
a = [0] * m
i = 0
s = input()
r = ""
t = 0
def prev(i):
    return (i + m - 1) % m
def next(i):
    return (i + 1) % m
d = {
    '>' : 'i = next(i)',
    '<' : 'i = prev(i)',
    '|' : 'i = 0',
    ',' : 'a[i] = int(input()) % n',
    '.' : 'print(a[i])',
    '=' : 'a[i] = a[prev(i)]',
    '0' : 'a[i] = 0',
    '!' : 'v = a[i]',
    '?' : 'a[i] = v % n',
    '*' : 'a[i] = (a[i] * a[prev(i)]) % n',
    '/' : 'a[i] = (a[i] // a[prev(i)]) % n',
    '+' : 'a[i] = (a[i] + 1) % n',
    '-' : 'a[i] = max(a[i] - 1, 0)',
    '[' : 'while a[i] != 0:',
    ']' : '',
    '(' : 'if a[i] != 0:',
    ')' : '',
    '^' : 'print(v)',
    '$' : 'v = i'
    }
for c in s:
    r += ' ' * t + d[c] + '\n'
    if c == '(' or c == '[':
        t += 4
    if c == ')' or c == ']':
        t -= 4
exec(r)
