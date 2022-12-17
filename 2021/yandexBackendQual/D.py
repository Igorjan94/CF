import requests
from xml.etree import ElementTree

contest = input()
server = 'http://127.0.0.1:7777/'

def get(url):
    response = requests.get(url)
    tree = ElementTree.fromstring(response.content)
    return tree

def participants():
    return get(server + f'view/participants?contest={contest}')

def submissions(login):
    return get(server + f'view/submissions?contest={contest}&login={login}')


class participant:
    def __init__(self, name, submissions):
        self.name = name
        self.ok = 0
        self.t = 0
        problems = set()
        s = {}
        cur = []
        for submit in submissions:
            cur.append([int(submit.get('timestamp')), submit.get('problem'), submit.get('verdict')])
        cur.sort(key = lambda submit: submit[0])
        for submit in cur:
            if submit[1] in problems:
                continue
            if submit[2] == 'CE':
                continue
            if submit[2] == 'OK':
                self.ok += 1
                self.t += submit[0] + s.get(submit[1], 0) * 20
                problems.add(submit[1])
            else:
                s[submit[1]] = s.get(submit[1], 0) + 1


    def __str__(self):
        return f'{self.name}, {self.ok}, {self.t}'


a = []
pars = participants()
for p in pars:
    login = p.get('login')
    subms = submissions(login)
    a.append(participant(login, subms))

a.sort(key = lambda p: [-p.ok, p.t])
winners = []
for i in range(len(a)):
    if a[i].ok == a[0].ok and a[i].t == a[0].t:
        winners.append(a[i].name)

winners.sort()
print(len(winners))
print(*winners, sep = '\n')
