#!/usr/bin/python3

import os
import requests
import sys
import itertools
import time
from time import sleep

# Edit these four variables according to your needs:
x_user          =  '''
d00ef4d59145a678537c71c8a14b63cd4e4d86f10e4a6b1c1bb926d6159a696bfae78d577e719e40
'''[1:-1]
csrf_token      =  '''
936df2b684e1514a5a82a0c0bfdbfa77
'''[1:-1]
cf_domain       =  'com'
username        =  'igorajn'
user_agent      =  'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.89 Safari/537.36'
weird_name      =  '39ce7'
weird_val       =  'CFdhiqLe'
jsession        =  'CEB1FBBB3256E0B89739343AC12C26D1-n1'

#{{{
updateInterval  =  2 #in seconds
countOfSubmits  =  3 #count of previous submits, shown after done submission. If count == 1, nothing happens.
ext_id          =  {
    "cpp":   "42",
    "hs":    "12",
    "java":  "36",
    "py":    "41",
}
#}}}

#{{{
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
#}}}

#{{{
#if len(sys.argv) > 2:
    #countOfSubmits = int(sys.argv[2])
    #getSubmissions()
    #sys.exit()

#if len(sys.argv) < 2:
    #print("Solution filename not specified")
    #sys.exit()

#if not os.path.exists(sys.argv[1]):
    #print("Solution file does not exist or not enough rights to read it")
    #sys.exit()

#filename = os.path.basename(sys.argv[1])

#contest_id = ''.join(itertools.takewhile(lambda c: c.isdigit(), filename))
#problem_index = ''.join(itertools.takewhile(lambda c: c != '.', filename[len(contest_id):])).upper()
#extension = filename[len(contest_id) + len(problem_index) + 1:].lower()

#if (len(contest_id) == 0) or (len(problem_index) == 0):
    #contest_id = os.path.dirname(os.path.realpath(sys.argv[1])).split(os.sep)[-1]
    #temp = filename.split('.')
    #problem_index = temp[0].upper()
    #extension = temp[-1].lower()
    #if (not contest_id.isdigit() or (len(problem_index) > 2)):
        #print("Incorrect filename format. Example: 123A.cpp or 123/A.cpp")
        #sys.exit()

#if not extension in ext_id:
    #print("Unknown extension. Please check 'ext_id' variable")
    #sys.exit()

#}}}

#parts = {
        #"csrf_token":            csrf_token,
        #"action":                "submitSolutionFormSubmitted",
        #"submittedProblemIndex": problem_index,
        #"source":                open(sys.argv[1], "rb"),
        #"programTypeId":         ext_id[extension],
        #"sourceFile":            "",
        #"_tta":                  "222"
#}

url = "http://codeforces.com/api/contest.status?contestId=522&from=1&count=3"
#url = "http://codeforces." + cf_domain + "/contest/" + contest_id + "/problem/" + problem_index,
#print("you' ve submitted " + contest_id + problem_index + extension)
r = requests.post(url,
    params = {
        "csrf_token" : csrf_token
    },
#    files = parts,
    headers = {
        "User-Agent" : user_agent,
    },
    cookies = {
        "X-User": x_user,
        "JSESSIONID": jsession,
        weird_name: weird_val,
        "70a7c28f3de" : "d5gpvi9c2ugfd2t9yg"
    }
)
print(r.text)
if r.status_code == requests.codes.ok:
    print("Solution is successfully sent. Current time is " + time.strftime("%H:%M:%S"))

getSubmissions()

