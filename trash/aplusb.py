f = open("aplusb.in", "r")
t = open("aplusb.out", "w")
a, b = [float(x) for x in f.readline().split()]
t.write("%.11f\n" % (a + b))
array = [long(x) for x in f.readline().split()]
array.reverse()
t.writelines(["%s " % i for i in array])
