f = open("postfixlogic.out", "w")
f.write("2\n")
f.write("S 0 _ -> S _ > 0 >\n")
f.write("S 1 _ -> S _ > 1 >\n")
f.write("S o _ -> S o ^ _ <\n")
f.write("S a _ -> S a ^ _ <\n")
f.write("S o 0 -> S _ > _ ^\n")
f.write("S a 1 -> S _ > _ ^\n")
f.write("S a 0 -> and a ^ _ <\n")
f.write("S o 1 -> or o ^ _ <\n")
f.write("or o 0 -> S _ > 1 >\n")
f.write("or o 1 -> S _ > 1 >\n")
f.write("and a 0 -> S _ > 0 >\n")
f.write("and a 1 -> S _ > 0 >\n")
f.write("S _ _ -> S _ ^ _ <\n")
f.write("S _ 0 -> AC 0 ^ _ ^\n")
f.write("S _ 1 -> AC 1 ^ _ ^\n")
