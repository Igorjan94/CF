#!/usr/bin/python3

import os
import requests
import sys
import itertools
import time
from time import sleep

# Edit these four variables according to your needs:
x_user          =  '''
02fe1afec55722d5cff82dbe3e7f105636bdd737bdcf7737c4cf1e2730af1e46b3c1f225e120de2c
'''[1:-1]
csrf_token      =  '''
C363C50288B310C45669A1A17F711C00
'''[1:-1]
cf_domain       =  "ru" #"com" if you prefer codeforces.com
username        =  "igorjan94"
updateInterval  =  2 #in seconds
countOfSubmits  =  3 #count of previous submits, shown after done submission. If count == 1, nothing happens.
ext_id          =  {
    "cpp":   "16",
    "hs":    "12",
    "java":  "36",
    "py":    "41",
}

# programTypeId - Language
# 10 - GNU C 4
# 1  - GNU C++ 4.7
# 16 - GNU C++0x 4
# 2  - Microsoft Visual C++ 2010
# 9  - C# Mono 2.10
# 29 - MS C# .NET 4
# 28 - D DMD32 Compiler v2
# 32 - Go 1.2
# 12 - Haskell GHC 7.6
# 5  - Java 6
# 23 - Java 7
# 36 - Java 8
# 19 - OCaml 4
# 3  - Delphi 7
# 4  - Free Pascal 2
# 13 - Perl 5.12
# 6  - PHP 5.3
# 7  - Python 2.7
# 31 - Python 3.4
# 40 - PyPy 2.5
# 41 - PyPy 3.2
# 8  - Ruby 2
# 20 - Scala 2.11
# 34 - JavaScript V8 3

def getSubmissions():
    while True:
        try:
            data = requests.get("http://codeforces.ru/api/user.status?handle=" + username + "&from=1&count=" + str(countOfSubmits)).json()['result']
        except:
            sleep(updateInterval)
            continue
        if countOfSubmits > 1:
            print("last submits")
            for s in reversed(data[1:]):
                try:
                    print(str(s['problem']['contestId']) + s['problem']['index'] + " " + \
                        '{:>20}'.format(s['verdict'] + "(" + str(s['passedTestCount'] + 1) + ") ") + str(s['timeConsumedMillis']) + " ms")
                except:
                    print()
            sys.stdout.flush()
        s = data[0]
        try:
            print(str(s['problem']['contestId']) + s['problem']['index'] + " " + \
                '{:>20}'.format(s['verdict'] + "(" + str(s['passedTestCount'] + 1) + ") ") + str(s['timeConsumedMillis']) + " ms")
            if s['verdict'] != 'TESTING':
                break
        except:
            print()
        sleep(updateInterval)

if len(sys.argv) > 2:
    countOfSubmits = int(sys.argv[2])
    getSubmissions()
    sys.exit()

if len(sys.argv) < 2:
    print("Solution filename not specified")
    sys.exit()

if not os.path.exists(sys.argv[1]):
    print("Solution file does not exist or not enough rights to read it")
    sys.exit()

filename = os.path.basename(sys.argv[1])

contest_id = ''.join(itertools.takewhile(lambda c: c.isdigit(), filename))
problem_index = ''.join(itertools.takewhile(lambda c: c != '.', filename[len(contest_id):])).upper()
extension = filename[len(contest_id) + len(problem_index) + 1:].lower()

if (len(contest_id) == 0) or (len(problem_index) == 0):
    contest_id = os.path.dirname(os.path.realpath(sys.argv[1])).split(os.sep)[-1]
    temp = filename.split('.')
    problem_index = temp[0].upper()
    extension = temp[-1].lower()
    if (not contest_id.isdigit() or (len(problem_index) > 2)):
        print("Incorrect filename format. Example: 123A.cpp or 123/A.cpp")
        sys.exit()

if not extension in ext_id:
    print("Unknown extension. Please check 'ext_id' variable")
    sys.exit()


parts = {
        "csrf_token":            csrf_token,
        "action":                "submitSolutionFormSubmitted",
        "submittedProblemIndex": problem_index,
        "source":                open(sys.argv[1], "rb"),
        "programTypeId":         ext_id[extension],
        "sourceFile":            "",
        "_tta":                  "222"
}

print("you' ve submitted " + contest_id + problem_index + extension)
r = requests.post("http://codeforces." + cf_domain + "/contest/" + contest_id + "/problem/" + problem_index,
              params = {"csrf_token": csrf_token},
              files = parts,
              cookies = {"X-User": x_user})
print(r)
if r.status_code == requests.codes.ok:
    print("Solution is successfully sent. Current time is " + time.strftime("%H:%M:%S"))

getSubmissions()

