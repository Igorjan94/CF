import math

a, b = map(float, input().split())
if b < a:
    t = a
    a = b
    b = t
f = 'abs(' + input().replace('^', '**').replace('sin', 'math.sin').replace('cos', 'math.cos').replace('sqrt', 'math.sqrt') + ')'
def integrant(x):
    return eval(f)
def simps(xi, xi1):
    return (xi1 - xi) * (integrant(xi) + 4 * integrant((xi + xi1) / 2) + integrant(xi1)) / 6

answer = 0
n = 4229
d = max((b - a) / n, 0.001)
x = a
if a != b:
    while x < b:
        answer += simps(x, x + d)
        x = min(b, x + d)
print('%.20f' % (answer))
