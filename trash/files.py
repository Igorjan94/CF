f = open('in', 'r')
g = open('out', 'w')
w = [int(x) for x in f.readline().split()]
w.reverse()
for x in w:
    g.write(str(x) + ' ')
#g.write(str(x) for x in w)
