import requests
from html.parser import HTMLParser
import re

roundId = 35

def entity2char(x):
    if x.startswith('&#x'):
        return chr(int(x[3:-1],16))
    elif x.startswith('&#'):
        return chr(int(x[2:-1]))
    else:
        if x == 'x2264':
            return '<='
        if x == 'xab' or x == 'xbb':
            return '"'
        return 'FAIL ' + x + ' FAIL'

class RCCParser(HTMLParser):

    def __init__(self):
        HTMLParser.__init__(self)
        self.parsing = -1
        self.problem = ''
        self.su = False

    def handle_starttag(self, tag, attrs):
        if tag == 'div':
            if self.parsing > 0:
                self.parsing += 1
            try:
                (x, y) = attrs[0]
                if x == 'class' and y == 'container prog-task-detail':
                    self.parsing = 1
            except:
                42
        elif tag == 'p':
            self.problem += '\n'
        elif tag == 'sub':
            if self.parsing > 0:
                self.problem += '_'
                self.su = True
        elif tag == 'sup':
            if self.parsing > 0:
                self.problem += '^'
                self.su = True
    def handle_endtag(self, tag):
        if tag == 'div':
            if self.parsing > 0:
                self.parsing -= 1

    def handle_data(self, data):
        if self.parsing > 0:
            if self.su and ('-' in data or '+' in data or '*' in data or '/' in data):
                data = '(' + data + ')'
            self.su = False
            self.problem += data

    def handle_entityref(self, name):
        if self.parsing > 0:
            self.problem += self.unescape(('&%s;' % name))

    def handle_charref(self, name):
        if self.parsing > 0:
            self.problem += entity2char(name)

indexes = ['A', 'B', 'C', 'D', 'E']

for index in indexes:
    url = 'http://www.russiancodecup.ru/championship/round/{}/problem/{}'.format(roundId, index)
    x = RCCParser()
    x.feed(requests.post(url).text)
    p = x.problem
    p = re.sub(r' +', ' ', p)
    p = re.sub(r'\n\s+', '\n', p)
    p = re.sub(r'^\n*', '', p)
    splited = 2
    if index != indexes[0] and index != indexes[-1]:
        splited = 3
    p = p.rsplit('\n', splited)[0]
    open(index + '.problem', 'w').write(p + '\n')
