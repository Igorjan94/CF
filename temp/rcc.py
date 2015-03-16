import requests
from html.parser import HTMLParser
import re


roundId = 34
'''
csrftoken = 'DMy8z06JC3ixYG07AtcVDfieO186Xx8B'
fullPath = '/home/igorjan/206round/2015/RCCWU/B.cpp'
userId = '8068fee5f49946b3a8f85b1007cd40bb'
Authorized = 'igorjan94'
RegisteredOnChamp = 'true'
sessionId = '".eJxNjDkOgCAQAP-ytYEYG0OnL_AHBGGNxAOzy4bC-HcpLCwnmZkbrJO8WmEkOzu_4RnAgE-E6kM1OeaSKOzIPFR5_LTm38aadX3bNrBQOqxQrJs158toXUpRJMzRnT4F9HJV1PC8TSAtXA:1YSu8g:QYsP_htL32aJs5bHb0y231UfYVI"'


parts = {
        'csrftoken':             csrftoken,
        'action':                '/send_solution/',
        'filesolution':          fullPath,
#        'source':                open(fullPath, 'rb'),
        'id_language':           '7'
}
r = requests.post('http://www.russiancodecup.ru/championship/round/{}/problem{}/'.format(roundId, index),
    params  = {'csrftoken': csrftoken},
    files   = parts,
    cookies = {'sessionId' : sessionId})
print(r.text)
if r.status_code == requests.codes.ok:
    print('Solution is successfully sent. Current time is ' + time.strftime('%H:%M:%S'))
'''

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
