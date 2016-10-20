task = 'elephants'
f = open(task + '.in', 'r')
g = open(task + '.out', 'w')
g.write("SHALYTO"[int(f.readline()) - 1])
g.close()
f.close()

