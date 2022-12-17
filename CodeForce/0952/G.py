y='..\nX.\n..\n'
print(''.join(y*(255-ord(x))+'X.\n'*2+y*ord(x)for x in input()))

