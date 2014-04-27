from random import *
from itertools import *

seed('ololo')
MAXN = 200000
testnum = 0

def out(tests):
    global testnum
    testnum += 1
    out = open("../tests/%02d"%testnum, "w")
    assert(sum(len(test) for test in tests) <= MAXN)
    assert(all('?' in test for test in tests))
    print (len(tests), file=out)
    for test in tests:
        print (test, file=out)

def filt(tests):
	return [t for t in tests if '?' in t]
	
	
def random_test(n, k):
	result = []
	for i in range(n):
		result.append("".join(choice('ab?') for _ in range(randint(1, k // 2) * 2)))
	return filt(result)

def all_str(n):
	return filt([''.join(s) for s in product('ab?', repeat=n)])

def one():
	s = "".join(choice('ab') for _ in range(MAXN // 2))
	ch_ind = randint(0, len(s))
	return [s + s[:ch_ind] + '?' + s[ch_ind + 1:]]

sample = ["ab?b", "baa?", "abb???"]
small = all_str(4)
middle = all_str(6)
big = all_str(8)
quest = ['?' * MAXN]
rnd = random_test(20000, 10)
half_quest = ["".join(choice('ab') for _ in range(MAXN // 2)) + '?' * (MAXN // 2)]
one_quest = one()

for t in sample, small, middle, rnd, quest, big, half_quest, one_quest:
	out(t)
