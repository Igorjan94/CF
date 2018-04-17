import re

def trimSpaces(ss):
    return re.sub('^\s*(.*?)\s*$', r'\1', ss)

def filterEmpty(l):
    return list(filter(lambda x: len(x) != 0, l))

text = input()
q = int(input())

sequences = re.sub(r'\.(\s*?[A-Z0-9.!?])', r'.#\1', text);
sequences = re.sub(r'\.(\s*?[A-Z0-9.!?])', r'.#\1', sequences);
# print(sequences)
sequences = re.sub('([!?])', r'\1#', sequences)
sequences = sequences.split('#')
sequences = filterEmpty(sequences)
sequencesLower = list(map(lambda x: filterEmpty(re.split('[.!? ]', x.lower())), sequences))
# print(sequences)



def connn(what):
    ret = []
    for i in range(len(sequencesLower)):
        ok = True
        for j in range(len(what)):
            #print('SEARCHING %s in %s %s' % (what[j], sequences[i], sequences[i].find(what[j])))
            if not what[j] in sequencesLower[i]:
                ok = False
                break
        if ok:
            ret.append(sequences[i])
    return ret

for i in range(q):
    ss = input()
    search = filterEmpty(re.split('\s', ss.lower()))
    results = connn(search)

    print('Search results for "%s":' % ss)
    if len(results):
        print("- %s" % "\n- ".join(map(lambda x: '"%s"' % (trimSpaces(x)), results)))
